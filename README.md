# Pac-Sphere

Gabe Brown, Juan David Garrido

## Getting Started

Clone and generate the project files:

```
cd yourCodeDirectory
git clone https://github.com/gbrown3/Pac-Sphere
cd Pac-Sphere
mkdir build
cd build
cmake-gui ..
```
Make sure you've installed [BasicGraphics](https://github.com/mac-comp465-f18/basicgraphics) and [MinVR](https://github.com/mac-comp465-f18/MinVR) in the same directory where you clone this project. If you're unsure as to how to do that, follow [this](https://docs.google.com/document/d/1eAPJK8-5PVgs30_pSBYFUQDQ6vxPnC1iGEfDeVRvSkw/edit?usp=sharing) guide.

In CMake, you should just need to configure the files once, then generate, and be able to open up the project and run it from there.

## Key Commands

You can toggle and swap between several different features. The key commands and corresponding actions are as follows:

- Arrow keys = move Pacman
- "W" = Toggle rendering the 3D maze walls on and off
- "T" = Render a plain BasicGraphics sphere instead of a sphere with the maze texture
- "M" = Go back to rendering the sphere with the maze texture
- "+" = zoom in
- "-" = zoom out
- "J" = Toggle whether or not the joint positions affect the pacman mesh (skinning) 

## Design Decisions
TODO: fill this in

## Project Structure

### App.h and App.cpp
These files contain the outermost structure of the app, based on the example in the MinVR [README](https://github.com/mac-comp465-f18/MinVR/blob/master/README.md). This is where the Pac-man and Maze objects are instantiated, the scene and camera are established, meshes get drawn, and user interaction is handled.

TODO: add more to this
