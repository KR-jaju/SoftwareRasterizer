#include <cstdint>
#include <functional>
#include <array>
#include <iostream>

/*
VSOut must have these members:
{
	float x, y, z, w; (clip space position)
	T attrib (attribute, (operator+, operator* must be implemented))
}
*/
template <typename VSIn, typename VSOut, typename PSOut>
class Rasterizer
{
public:
	using VertexShader = std::function<VSOut(VSIn const&)>;
	using PixelShader = std::function<PSOut(VSOut const&)>;
	//IA
	void 	setVertexBuffer(VSIn const* vertex_buffer);
	void	setIndexBuffer(uint32_t const* index_buffer);
	//VS
	void	setVertexShader(VertexShader const& vertex_shader);
	//RS
	void	setViewport(uint32_t x, uint32_t y, uint32_t w, uint32_t h);
	void	setDepthRange(float near, float far);
	//PS
	void	setPixelShader(PixelShader const& pixel_shader);
	//OM
	void	setRenderTarget(PSOut* render_target);

	void	clear(PSOut const& value);
	void	draw(uint32_t offset, uint32_t count);
private:
	VSIn const*	vertex_buffer;
	uint32_t const* index_buffer;
	uint32_t x;
	uint32_t y;
	uint32_t w;
	uint32_t h;
	float	near;
	float	far;

	PSOut*	render_target;
	VertexShader vertex_shader;
	PixelShader	pixel_shader;
	std::vector<std::pair<VSOut, uint32_t>> post_transform_cache;
	uint32_t cache_generation;

	template <typename Pred>
	uint32_t clip(std::array<VSOut, 8> const& input, std::array<VSOut, 8>& output, uint32_t inCount, Pred const& inside);
	uint32_t clipTriangle(VSOut const& v0, VSOut const& v1, VSOut const& v2, std::array<VSOut, 8>& out);
	void	drawTriangle(VSOut const& v0, VSOut const& v1, VSOut const& v2);
};

template <typename VSIn, typename VSOut, typename PSOut>
void	Rasterizer<VSIn, VSOut, PSOut>::setVertexBuffer(VSIn const* vertex_buffer)
{
	this->vertex_buffer = vertex_buffer;
}

template <typename VSIn, typename VSOut, typename PSOut>
void	Rasterizer<VSIn, VSOut, PSOut>::setIndexBuffer(uint32_t const* index_buffer)
{
	this->index_buffer = index_buffer;
}

template <typename VSIn, typename VSOut, typename PSOut>
void Rasterizer<VSIn, VSOut, PSOut>::setVertexShader(VertexShader const& vertex_shader)
{
	this->vertex_shader = vertex_shader;
}

template <typename VSIn, typename VSOut, typename PSOut>
void Rasterizer<VSIn, VSOut, PSOut>::setViewport(uint32_t x, uint32_t y, uint32_t w, uint32_t h)
{
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
}

template <typename VSIn, typename VSOut, typename PSOut>
void Rasterizer<VSIn, VSOut, PSOut>::setDepthRange(float near, float far)
{
	this->near = near;
	this->far = far;
}

template <typename VSIn, typename VSOut, typename PSOut>
void Rasterizer<VSIn, VSOut, PSOut>::setPixelShader(PixelShader const& pixel_shader)
{
	this->pixel_shader = pixel_shader;
}

template <typename VSIn, typename VSOut, typename PSOut>
void	Rasterizer<VSIn, VSOut, PSOut>::setRenderTarget(PSOut* render_target)
{
	this->render_target = render_target;
}

template <typename VSIn, typename VSOut, typename PSOut>
void	Rasterizer<VSIn, VSOut, PSOut>::clear(PSOut const& value)
{
	std::fill_n(this->render_target, this->w * this->h, value);
}

template <typename VSIn, typename VSOut, typename PSOut>
void	Rasterizer<VSIn, VSOut, PSOut>::draw(uint32_t offset, uint32_t count)
{
	this->cache_generation += 1;
	for (int v_id = 0; v_id + 3 <= count; v_id += 3)
	{
		uint32_t const v0_idx = this->index_buffer[offset + v_id];
		uint32_t const v1_idx = this->index_buffer[offset + v_id + 1];
		uint32_t const v2_idx = this->index_buffer[offset + v_id + 2];
		uint32_t const vertex_limit = std::max(v0_idx, std::max(v1_idx, v2_idx));
		
		if (this->post_transform_cache.size() <= vertex_limit)
			this->post_transform_cache.resize(vertex_limit + 1, std::make_pair(VSOut(), this->cache_generation - 1));
		std::pair<VSOut, uint32_t>& v0 = this->post_transform_cache[v0_idx];
		std::pair<VSOut, uint32_t>& v1 = this->post_transform_cache[v1_idx];
		std::pair<VSOut, uint32_t>& v2 = this->post_transform_cache[v2_idx];

		if (v0.second != this->cache_generation)
			v0 = std::make_pair(this->vertex_shader(this->vertex_buffer[v0_idx]), this->cache_generation);
		if (v1.second != this->cache_generation)
			v1 = std::make_pair(this->vertex_shader(this->vertex_buffer[v1_idx]), this->cache_generation);
		if (v2.second != this->cache_generation)
			v2 = std::make_pair(this->vertex_shader(this->vertex_buffer[v2_idx]), this->cache_generation);
		std::array<VSOut, 8> clip_result;
		int const count = this->clipTriangle(v0.first, v1.first, v2.first, clip_result);

		for (int idx = 2; idx < count; ++idx)
			this->drawTriangle(clip_result[0], clip_result[idx - 1], clip_result[idx]);
	}
}

template <typename VSIn, typename VSOut, typename PSOut>
void	Rasterizer<VSIn, VSOut, PSOut>::drawTriangle(VSOut const& v0, VSOut const& v1, VSOut const& v2)
{
	VSOut screen_v0 = v0;
	VSOut screen_v1 = v1;
	VSOut screen_v2 = v2;

	screen_v0.x = (screen_v0.x / screen_v0.w * 0.5f + 0.5f) * this->w + this->x; // -1 -> 0, 1 -> width
	screen_v0.y = (screen_v0.y / screen_v0.w * -0.5f + 0.5f) * this->h + this->y;
	screen_v0.z = (screen_v0.z / screen_v0.w) * (this->far - this->near) + this->near;
	screen_v1.x = (screen_v1.x / screen_v1.w * 0.5f + 0.5f) * this->w + this->x;
	screen_v1.y = (screen_v1.y / screen_v1.w * -0.5f + 0.5f) * this->h + this->y;
	screen_v1.z = (screen_v1.z / screen_v1.w) * (this->far - this->near) + this->near;
	screen_v2.x = (screen_v2.x / screen_v2.w * 0.5f + 0.5f) * this->w + this->x;
	screen_v2.y = (screen_v2.y / screen_v2.w * -0.5f + 0.5f) * this->h + this->y;
	screen_v2.z = (screen_v2.z / screen_v2.w) * (this->far - this->near) + this->near;
	int x_min = std::round(std::min(screen_v0.x, std::min(screen_v1.x, screen_v2.x)));
	int x_max = std::round(std::max(screen_v0.x, std::max(screen_v1.x, screen_v2.x)));
	int y_min = std::round(std::min(screen_v0.y, std::min(screen_v1.y, screen_v2.y)));
	int y_max = std::round(std::max(screen_v0.y, std::max(screen_v1.y, screen_v2.y)));
	float area = (screen_v1.x - screen_v0.x) * (screen_v2.y - screen_v0.y) -
				 (screen_v1.y - screen_v0.y) * (screen_v2.x - screen_v0.x);
	if (area <= 0.0f)
		return;
	float inv_area = 1.0f / area;

	for (int y = y_min; y <= y_max; ++y)
	{
		for (int x = x_min; x <= x_max; ++x)
		{	
			float const px = x + 0.5f;
			float const py = y + 0.5f;
			float u = ((screen_v2.x - screen_v1.x) * (py - screen_v1.y) -
						(screen_v2.y - screen_v1.y) * (px - screen_v1.x)) * inv_area;
			float v = ((screen_v0.x - screen_v2.x) * (py - screen_v2.y) -
						(screen_v0.y - screen_v2.y) * (px - screen_v2.x)) * inv_area;
			float w = 1.0f - u - v;
			
			if (u < 0 || v < 0 || w < 0)
				continue;
			float const pu = u / screen_v0.w;
			float const pv = v / screen_v1.w;
			float const pw = w / screen_v2.w;
			float const factor = 1.0f / (pu + pv + pw);
			VSOut input = {
				screen_v0.x * (u) + screen_v1.x * (v) + screen_v2.x * (w),
				screen_v0.y * (u) + screen_v1.y * (v) + screen_v2.y * (w),
				screen_v0.z * (u) + screen_v1.z * (v) + screen_v2.z * (w),
				0.0f, // w is not used
				screen_v0.attrib * (pu * factor) + screen_v1.attrib * (pv * factor) + screen_v2.attrib * (pw * factor)
			};
			this->render_target[x + y * this->w] = this->pixel_shader(input);
		}
	}
}

template <typename VSIn, typename VSOut, typename PSOut>
uint32_t Rasterizer<VSIn, VSOut, PSOut>::clipTriangle(VSOut const& v0, VSOut const& v1, VSOut const& v2, std::array<VSOut, 8>& out)
{
	std::array<VSOut, 8> clip_buffer;
	uint32_t count;

	out[0] = v0;
	out[1] = v1;
	out[2] = v2;
	count = this->clip(out, clip_buffer, 3, [](VSOut const& v) { return (v.x + v.w) >= 0.0f; });
	count = this->clip(out, clip_buffer, count, [](VSOut const& v) { return (v.w - v.x) >= 0.0f; });
	count = this->clip(out, clip_buffer, count, [](VSOut const& v) { return (v.w - v.y) >= 0.0f; });
	count = this->clip(out, clip_buffer, count, [](VSOut const& v) { return (v.y + v.w) >= 0.0f; });
	count = this->clip(out, clip_buffer, count, [](VSOut const& v) { return (v.z + v.w) >= 0.0f; });
	count = this->clip(out, clip_buffer, count, [](VSOut const& v) { return (v.w - v.z) >= 0.0f; });
	return (count);
}

template <typename VSIn, typename VSOut, typename PSOut>
template <typename Pred>
uint32_t Rasterizer<VSIn, VSOut, PSOut>::clip(
	std::array<VSOut, 8> const& input,
	std::array<VSOut, 8>& output,
	uint32_t inCount, Pred const& inside)
{
	auto intersect = [](VSOut const& v0, VSOut const& v1) {
		float p0 = (v0.x + v0.w);
		float p1 = (v1.x + v1.w);
		float t  = p0 / (p0 - p1);  // Sutherland–Hodgman 표준 공식
		return VSOut {
			v0.x * (1.0f - t) + v1.x * t,
			v0.y * (1.0f - t) + v1.y * t,
			v0.z * (1.0f - t) + v1.z * t,
			v0.w * (1.0f - t) + v1.w * t,
			v0.attrib * (1.0f - t) + v1.attrib * t,
		};
	};

	uint32_t outCount = 0;
	for (uint32_t i = 0; i < inCount; ++i)
	{
		auto const& cur = input[i];
		auto const& nxt = input[(i + 1) % inCount];
		bool cIn = inside(cur);
		bool nIn = inside(nxt);

		if (cIn && nIn)
		{
			output[outCount] = nxt;
			outCount += 1;
		}
		else if (cIn && !nIn)
		{
			output[outCount] = intersect(cur, nxt);
			outCount += 1;
		}
		else if (!cIn && nIn)
		{
			output[outCount] = intersect(cur, nxt);
			outCount += 1;
			output[outCount] = nxt;
			outCount += 1;
		}
	}
	return outCount;
}
