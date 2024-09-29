#include <iostream>
#include <math.h>
#include "Screen.h"
#include <stdlib.h>
#include <time.h>
#include "Swarm.h"
using namespace std;
#include "src/include/SDL2/SDL.h"
using namespace galaxy;

        //buffer[i] = 0xFF0000FF;//RED
        //buffer[i] = 0xFF00FFFF; //PINK
        //buffer[i] = 0x000000FF; //BLACK
        //buffer[i] = 0x00FF00FF;//GREEN
        //buffer[i] = 0xFFFF00FF; //YELLOW
        //buffer[i] = 0xFFFFFFFF; //WHITE
        //buffer[i] = 0X00FFFFFF; //TIRQUISE
        //buffer[i] = 0x00FF80FF; //LGHT GREEN

int SDL_main(int argc, char* argv[]) {

	srand(time(NULL));

	Screen screen;

	if (screen.init() == false) {
		cout << "Error initialising SDL." << endl;
	}

	Swarm swarm;

	while (true) {

		int elapsed = SDL_GetTicks();

		swarm.update(elapsed);

		unsigned char green =
				(unsigned char) ((1 + sin(elapsed * 0.0001)) * 128);
		unsigned char red = (unsigned char) ((1 + sin(elapsed * 0.0002)) * 128);
		unsigned char blue = (unsigned char) ((1 + sin(elapsed * 0.0003)) * 128);

		const Particle * const pParticles = swarm.getParticles();

		for (int i = 0; i < Swarm::NPARTICLES; i++) {
			Particle particle = pParticles[i];

			int x = (particle.m_x + 1) * Screen::SCREEN_WIDTH / 2;
			int y = particle.m_y * Screen::SCREEN_WIDTH / 2 + Screen::SCREEN_HEIGHT/2;

			screen.setPixel(x, y, red, green, blue);
		}

		screen.boxBlur();
		screen.update();

		if (screen.processEvents() == false) {
			break;
		}
	}

	screen.close();

	return 0;

}