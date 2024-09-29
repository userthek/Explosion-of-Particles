#ifndef SWARM_H_ 
#define SWARM_H_

#include "Particle.h" 

namespace galaxy { 

/* 
 * The Swarm class is responsible for managing a collection of Particle objects.
 * It keeps track of a dynamically allocated array of particles and provides functionality 
 * to update their positions based on time progression.
 */
class Swarm {
public:
    /* 
     * NPARTICLES defines the number of particles in the swarm.
     * This is a constant value shared across all instances of the Swarm class.
     * Having a large number of particles (5000 in this case) allows for detailed swarm simulation, you can change it if you like.
     */
    const static int NPARTICLES = 5000;

private:
    Particle * m_pParticles;
    int lastTime;

public:
    Swarm();
    virtual ~Swarm();
    void update(int elapsed);
    const Particle * const getParticles() { return m_pParticles; };
};

} 

#endif 
