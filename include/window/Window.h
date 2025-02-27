#pragma once

#include <cstdint>
#include <SDL.h>
#include <memory>
#include <vector>

class Window
{
public:
	Window(std::string const& title, uint32_t width, uint32_t height);

	uint32_t	getPixel(uint32_t x, uint32_t y) const;
	void	setPixel(uint32_t x, uint32_t y, uint32_t pixels);

	uint32_t*	getPixelBuffer();
	uint32_t const*	getPixelBuffer() const;

	void	update();

private:
	using SDLWindow = std::unique_ptr<SDL_Window, void(*)(SDL_Window*)>;
	using SDLRenderer = std::unique_ptr<SDL_Renderer, void(*)(SDL_Renderer*)>;
	using SDLTexture = std::unique_ptr<SDL_Texture, void(*)(SDL_Texture*)>;

	SDLWindow sdl_window;
	SDLRenderer sdl_renderer;
	SDLTexture sdl_texture;

	std::vector<uint32_t> pixels;
	
	uint32_t	width;
	uint32_t	height;
};