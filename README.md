# A basic 3D Rendering engine

## tools used:
 - C
 - Check: https://libcheck.github.io/check/
 - Opengl
 - GLEW: https://glew.sourceforge.net/
 - SDL: https://www.libsdl.org/

## known issues
 - linux support only (the build system needs changing)
 - unstable on wayland (particularly in hyprland)

## self imposed limtations
 - new tools should be avoided unless its unreasonable to DIY it
 - C is the only language that can be use for the main project (there is exceptions for tasks like building and scripting) 
 - the custom stack allocator should be use in place of malloc unless its unreasonable to do so 

## needed features

### bigger
 - [ ] an object hierarchy
 - [ ] an object editer
 - [ ] a keyboard event handler
 - [x] a framelimter
 - [ ] a new build system (that is cross platform)
 - [ ] Lisp embeding for scripting
 - [ ] state snapshot system
 - [ ] write a how to use guide

### smailler
 - [ ] a min heap for object rendering (distance from camera)
 - [ ] a cache system for commonly used Objects
 - [ ] more sane default uniforms for shaders
 - [ ] a streamlined way to pass a uniform to a shader
