#include "Screen.h"

namespace galaxy {

Screen::Screen() :
		m_window(NULL), m_renderer(NULL), m_texture(NULL), m_buffer1(NULL), m_buffer2(NULL) {
}

/* 
 * init() initializes the SDL library and creates the necessary components for the screen.
 * It sets up the SDL window, renderer, texture, and frame buffers for drawing particles.
 */
bool Screen::init() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		return false;
	}

	m_window = SDL_CreateWindow("Particle Fire Explosion",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
		SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	if (m_window == NULL) {
		SDL_Quit();
		return false;
	}

	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_PRESENTVSYNC);

	m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA8888,
			SDL_TEXTUREACCESS_STATIC, SCREEN_WIDTH, SCREEN_HEIGHT);

	if (m_renderer == NULL) {
		SDL_DestroyWindow(m_window);
		SDL_Quit();
		return false;
	}

	if (m_texture == NULL) {
		SDL_DestroyRenderer(m_renderer);
		SDL_DestroyWindow(m_window);
		SDL_Quit();
		return false;
	}

	m_buffer1 = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];
	m_buffer2 = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];

	memset(m_buffer1, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));
	memset(m_buffer2, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));

	return true;
}

/* 
 * boxBlur() applies a simple blur effect by averaging the colors of neighboring pixels.
 * This is done by swapping the buffers and calculating the average RGB values of the surrounding pixels.
 */
void Screen::boxBlur() {
	Uint32 *temp = m_buffer1;
	m_buffer1 = m_buffer2;
	m_buffer2 = temp;

	for (int y = 0; y < SCREEN_HEIGHT; y++) {
		for (int x = 0; x < SCREEN_WIDTH; x++) {

			int redTotal = 0;
			int greenTotal = 0;
			int blueTotal = 0;

			for (int row = -1; row <= 1; row++) {
				for (int col = -1; col <= 1; col++) {
					int currentX = x + col;
					int currentY = y + row;

					if (currentX >= 0 && currentX < SCREEN_WIDTH && currentY >= 0 && currentY < SCREEN_HEIGHT) {

						Uint32 color = m_buffer2[currentY * SCREEN_WIDTH + currentX];
						Uint8 red = color >> 24;
						Uint8 green = color >> 16;
						Uint8 blue = color >> 8;

						redTotal += red;
						greenTotal += green;
						blueTotal += blue;
					}
				}
			}

			/*Compute the average RGB values by dividing the total by 9 (for the 3x3 grid)*/ 
			Uint8 red = redTotal / 9;
			Uint8 green = greenTotal / 9;
			Uint8 blue = blueTotal / 9;
			setPixel(x, y, red, green, blue);
		}
	}
}

/* 
 * setPixel() sets the pixel color at position (x, y) in m_buffer1.
 * The RGB values are combined into a single 32-bit integer representing an RGBA color.
 */
void Screen::setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue) {
	// Ensure the pixel coordinates are within the screen bounds
	if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT) {
		return;
	}

	Uint32 color = 0;

	color += red;        /*Set the red component*/ 
	color <<= 8;         /*Shift left to make room for the green component*/ 
	color += green;      /*Set the green component*/ 
	color <<= 8;         /*Shift left to make room for the blue component*/ 
	color += blue;       /*Set the blue component*/ 
	color <<= 8;         /*Set the alpha component to 255 (fully opaque)*/ 
	color += 0xFF;

	m_buffer1[(y * SCREEN_WIDTH) + x] = color;
}

/* 
 * update() updates the texture with the pixel data and renders it on the screen.
 * The texture is updated with the contents of m_buffer1 and then rendered using SDL.
 */
void Screen::update() {
	SDL_UpdateTexture(m_texture, NULL, m_buffer1, SCREEN_WIDTH * sizeof(Uint32));
	SDL_RenderClear(m_renderer);
	SDL_RenderCopy(m_renderer, m_texture, NULL, NULL);
	SDL_RenderPresent(m_renderer);
}

/* 
 * processEvents() handles events such as window closing.
 * It polls for events like SDL_QUIT to determine whether the application should close.
 */
bool Screen::processEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			return false;
		}
	}

	return true;
}

/* 
 * close() cleans up resources by freeing allocated memory and destroying SDL components.
 * It deallocates the buffers and destroys the window, renderer, and texture.
 */
void Screen::close() {
	delete[] m_buffer1;
	delete[] m_buffer2;

	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyTexture(m_texture);
	SDL_DestroyWindow(m_window);

	SDL_Quit();
}

} 
