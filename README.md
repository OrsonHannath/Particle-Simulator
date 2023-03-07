# Particle-Simulator
Particle Simulator programmed in C++. Ability to change between different particle sorting algorithms to optimize collision physics. Ability to render simulation to a series of frames compilable using https://github.com/OrsonHannath/Video-Compiler.

## Particle Sorting Algorithms
### Brute
Brute force attempt at collision detection. Every Particle checks all other particles positions and checks for collision.

### Sweep and Prune
Sweep and Prune looks for overlapping intervals along the X-Axis. If any particles have overlapping intervals then these particles will check for collisions with one another.

### Uniform Grid Space Partitioning
Uniform Grid Space Partitioning splits the screen into grid partitions all of which track the particles contained. All particles from within a partition check for collisions with one another.

## Particle Simulation Examples
All examples have their simulation settings saved within the simulator_settings folder and their renders saved within the example_renders folder.
*note: Previews below may take time to load links to videos also provided.

### Bouncy100 - Large Particles
https://www.youtube.com/watch?v=IkYRuh0KE_c
[![Bouncy500 - Random Particles](example_renders/gifs/Bouncy100_Large.gif)](https://www.youtube.com/watch?v=IkYRuh0KE_c)

### Bouncy500 - Random Particles
https://www.youtube.com/watch?v=8M3sWO2O0oU
[![Bouncy500 - Random Particles](example_renders/gifs/Bouncy500_Random.gif)](https://www.youtube.com/watch?v=8M3sWO2O0oU)

### Fountain500 - Tiny Particles
https://www.youtube.com/watch?v=njlgn0mS9-k
[![Fountain500 - Tiny Particles](example_renders/gifs/Fountain500_Tiny.gif)](https://www.youtube.com/watch?v=njlgn0mS9-k)

### Fountain500 - Medium Particles
https://www.youtube.com/watch?v=wKCKQfwS3ts
[![Fountain500 - Medium Particles](example_renders/gifs/Fountain500_Medium.gif)](https://www.youtube.com/watch?v=wKCKQfwS3ts)

### Fountain750 - Medium Particles
https://www.youtube.com/watch?v=76neepVBK1A
[![Fountain750 - Medium Particles](example_renders/gifs/Fountain750_Medium.gif)](https://www.youtube.com/watch?v=76neepVBK1A)

### Fountain1000 - Medium Particles
https://www.youtube.com/watch?v=JUanK4E5BLk
[![Fountain1000 - Medium Particles](example_renders/gifs/Fountain1000_Medium.gif)](https://www.youtube.com/watch?v=JUanK4E5BLk)
