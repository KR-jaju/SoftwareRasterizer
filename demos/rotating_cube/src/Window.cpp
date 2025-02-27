#include "Window.h"
#include <string>

Window::Window(std::string const& title, uint32_t width, uint32_t height)
	: sdl_window(nullptr, nullptr), sdl_renderer(nullptr, nullptr), sdl_texture(nullptr, nullptr),
	pixels(width * height, 0),
	width(width), height(height)
{
	this->sdl_window = std::move(SDLWindow(SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN), SDL_DestroyWindow));
	if (this->sdl_window == nullptr)
		throw std::runtime_error("Fail to create SDL Window");
	this->sdl_renderer = std::move(SDLRenderer(SDL_CreateRenderer(this->sdl_window.get(), -1, SDL_RENDERER_ACCELERATED), SDL_DestroyRenderer));
	if (this->sdl_renderer == nullptr)
		throw std::runtime_error("Fail to create SDL Renderer");
	this->sdl_texture = std::move(SDLTexture(SDL_CreateTexture(this->sdl_renderer.get(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, width, height), SDL_DestroyTexture));
	if (this->sdl_texture == nullptr)
		throw std::runtime_error("Fail to create SDL Texture");
}


uint32_t	Window::getPixel(uint32_t x, uint32_t y) const
{
	return (this->pixels[x + y * this->width]);
}

void	Window::setPixel(uint32_t x, uint32_t y, uint32_t color)
{
	this->pixels[x + y * this->width] = color;
}

uint32_t*	Window::getPixelBuffer()
{
	return (this->pixels.data());
}
uint32_t const*	Window::getPixelBuffer() const
{
	return (this->pixels.data());
}

void	Window::update()
{
	SDL_UpdateTexture(this->sdl_texture.get(), nullptr, this->pixels.data(), this->width * sizeof(uint32_t));
	SDL_RenderClear(this->sdl_renderer.get());
	SDL_RenderCopy(this->sdl_renderer.get(), this->sdl_texture.get(), nullptr, nullptr);
	SDL_RenderPresent(this->sdl_renderer.get());
}