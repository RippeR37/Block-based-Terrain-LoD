Project
=======

Simple implementation of loading heightmaps and generating on-the-fly LoD database to efficiently render terrain with
different level of detail depending on distance to camera.

Simple doesnt mean its slow. Though building might be faster, to render terrain it uses single OpenGL call
```glMultiDrawElements()``` with previously builded data in both VBO and IBO. It also allows for good customization
with easy way to change number of levels, size of blocks and how levels for each block is determined.


Compiling
=========

Compiler and software
---------------------

Tested with Code::Blocks 13.12 with MinGW compiler (GCC) (project file for Code::Blocks is included).
Tested on platforms: Windows (Windows 7 x64).


Dependencies
------------

1. GLEW (tested with version 1.10.0)
2. GLFW3 (tested with version 3.0.4)
3. GLM (tested with 0.9.5.4, headers only)

Builded libs are included in demo example, however headers for them are not.


License
=======

Feel free to do whatever you want with it, though it would be nice to mention me if my code helps you somehow.
