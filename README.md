# Particle-Simulator
Particle Simulator programmed in C++. Ability to change between different particle sorting algorithms to optimize collision physics.

## Brute
Brute force attempt at collision detection. Every Particle checks all other particles positions and checks for collision.

![Bubble Sort Gif](src/Assets/BubbleSortGif.gif)

## Sweep and Prune
Sweep and Prune looks for overlapping intervals along the X-Axis. If any particles have overlapping intervals then these particles will check for collisions with one another.

![Selection Sort Gif](src/Assets/SelectionSortGif.gif)

## Uniform Grid Space Partitioning
Uniform Grid Space Partitioning splits the screen into grid partitions all of which track the particles contained. All particles from within a partition check for collisions with one another.

![Insertion Sort Gif](src/Assets/InsertionSortGif.gif)
