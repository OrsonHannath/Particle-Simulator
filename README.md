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
[![Bouncy500 - Random Particles](https://img.youtube.com/vi/IkYRuh0KE_c/0.jpg)](https://www.youtube.com/watch?v=IkYRuh0KE_c)

### Bouncy500 - Random Particles
[![Bouncy500 - Random Particles](https://img.youtube.com/vi/8M3sWO2O0oU/0.jpg)](https://www.youtube.com/watch?v=8M3sWO2O0oU)

### Fountain500 - Tiny Particles
[![Fountain500 - Tiny Particles](https://img.youtube.com/vi/njlgn0mS9-k/0.jpg)](https://www.youtube.com/watch?v=njlgn0mS9-k)

### Fountain500 - Medium Particles
[![Fountain500 - Medium Particles](https://img.youtube.com/vi/wKCKQfwS3ts/0.jpg)](https://www.youtube.com/watch?v=wKCKQfwS3ts)

### Fountain750 - Medium Particles
[![Fountain750 - Medium Particles](https://img.youtube.com/vi/76neepVBK1A/0.jpg)](https://www.youtube.com/watch?v=76neepVBK1A)

### Fountain1000 - Medium Particles
[![Fountain1000 - Medium Particles](https://img.youtube.com/vi/JUanK4E5BLk/0.jpg)](https://www.youtube.com/watch?v=JUanK4E5BLk)
