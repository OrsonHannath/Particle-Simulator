# Particle-Simulator
Particle Simulator programmed in C++. Ability to change between different particle sorting algorithms to optimize collision physics.

## Particle Sorting Algorithms
### Brute
Brute force attempt at collision detection. Every Particle checks all other particles positions and checks for collision.

### Sweep and Prune
Sweep and Prune looks for overlapping intervals along the X-Axis. If any particles have overlapping intervals then these particles will check for collisions with one another.

### Uniform Grid Space Partitioning
Uniform Grid Space Partitioning splits the screen into grid partitions all of which track the particles contained. All particles from within a partition check for collisions with one another.

## Particle Simulation Examples
All examples have their simulation settings saved within the simulator_settings folder.
### Bouncy100 - Large Particles

### Bouncy500 - Random Particles

### Fountain500 - Tiny Particles

### Fountain500 - Medium Particles

### Fountain750 - Medium Particles

### Fountain1000 - Medium Particles
