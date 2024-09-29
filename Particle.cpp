#include "Particle.h"
#include <math.h>
#include <stdlib.h>

namespace galaxy {

Particle::Particle() :
		m_x(0), m_y(0) {

	init();
}

/* 
 * init() resets the particle's state by setting its speed and direction.
 * - m_x and m_y are reset to 0, placing the particle at the origin.
 * - m_direction is randomly assigned an angle between 0 and 2π (in radians), determining its movement direction.
 * - m_speed is also randomized, and it’s squared to reduce the likelihood of high speeds.
 */
void Particle::init() {
	m_x = 0;
	m_y = 0;
	m_direction = (2 * M_PI * rand()) / RAND_MAX;
	m_speed = (0.04 * rand()) / RAND_MAX;

	m_speed *= m_speed;
}

Particle::~Particle() {
	// 
}

/* 
 * update() advances the particle's position based on its speed, direction, and the time interval.
 * - interval: Time passed since the last update (used to scale movement).
 * - The position is updated using the velocity components derived from the speed and direction.
 */
void Particle::update(int interval) {

	m_direction += interval * 0.0003;

	double xspeed = m_speed * cos(m_direction);
	double yspeed = m_speed * sin(m_direction);

	m_x += xspeed * interval;
	m_y += yspeed * interval;

	if (m_x < -1 || m_x > 1 || m_y < -1 || m_y > 1) {
		init();
	}

	if(rand() < RAND_MAX/100) {
		init();
	}
}

}  