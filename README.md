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
![Bouncy100 - Large Particles](https://www.youtube.com/watch?v=MASAqbRMnaM)

### Bouncy500 - Random Particles
![Bouncy500 - Random Particles](example_renders/_Bouncy500_Random_render.mp4)

### Fountain500 - Tiny Particles
![Fountain500 - Tiny Particles](example_renders/_Fountain500_render.mp4)

### Fountain500 - Medium Particles
![Fountain500 - Medium Particles](example_renders/_Fountain500_Medium_render.mp4)

### Fountain750 - Medium Particles
![Fountain750 - Medium Particles](example_renders/_Fountain750_Medium_render.mp4)

### Fountain1000 - Medium Particles
![Fountain1000 - Medium Particles](example_renders/_Fountain1000_Medium_render.mp4)
