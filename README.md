# Snake

C++ replica of the classic Snake game to get knowledge in basic game development. This implementation uses anax (entity-component-system) and SFML. Because the focus was on learning how to use an ECS, some of the design decisions are not great and simply exist to get it up and running.

![Snake](https://github.com/sgodwincs/snake/blob/master/snake.png)

# Build

Premake5 must be used to construct project files for whatever build system you want to use. It is assumed that all dependencies (SFML and anax) reside in `../dependencies/` relative to the repository. Example of using premake5 with Visual Studio would be:

```
premake5 vs2015
```

or for makefile

```
premake5 gmake
```

Also, it is assumed the debug versions of the libraries are linked, but this can easily be changed in the `premake5.lua` file by removing the `_d` and `-d` extensions from anax and SFML respectively. To run the executable, the working directory needs to be `projects/game`, and this is automatically set within the Visual Studio debug environment via Premake5.
