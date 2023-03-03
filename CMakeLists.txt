cmake_minimum_required(VERSION 3.21)
project(ParticleSimulator)

set(CMAKE_CXX_STANDARD 14)

# Setup the locations that the SDL libraries can be found on disk
set(SDL2_INCLUDE_DIR C:/libs/SDL/include) # set(VAR_NAME path)
set(SDL2_LIB_DIR C:/libs/SDL/lib/x64) # set(VAR_NAME path)

include_directories(${SDL2_INCLUDE_DIR}) # include_directories(${VAR_NAME}) *used for include files*
link_directories(${SDL2_LIB_DIR}) # link_directories(${VAR_NAME}) *used for dll/binary/lib files*

add_executable(ParticleSimulator main.cpp Framework.cpp Framework.h Colour.cpp Colour.h Particle.cpp Particle.h Vector2.cpp Vector2.h VectorMath.h DeltaTime.h VectorMath.cpp ColourRandomizer.cpp ColourRandomizer.h Random.cpp Random.h ParticleGenerator.cpp ParticleGenerator.h Vector4.cpp Vector4.h Enumerators.cpp Enumerators.h MapSort.cpp MapSort.h)

target_link_libraries(${PROJECT_NAME} SDL2main SDL2) # Link the libraries to the project
