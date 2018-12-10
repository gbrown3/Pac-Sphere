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
To create Pac-Sphere there were a lot of different decisions to be made due to the amount of details that the game must have. The first big decision we made was to recycle the Sphere class we created in the Earthquakes HW in order to tesselate the sphere with any maze. The amount of stacks and slices was a big question that at first we chose randomly based on how good it looked and how efficiently it performed. Later on, when displacement mapping was implemented, we found that if there were too few slices or stacks then some of the vertices would skip over a wall in the texture and they would not be taken into account by the displacement mapping geometry shader. 250 stacks and 350 slices was a perfect balance of efficiency and aesthetics while correctly drawing every single piece of the maze.

When implementing the maze we decided that there we would be no real need to implement a fragment shader due to the walls being black and because all they really do is demark the limits for Pacman's and the ghosts' movements. 

## Project Structure

### App.h and App.cpp
These files contain the outermost structure of the app, based on the example in the MinVR [README](https://github.com/mac-comp465-f18/MinVR/blob/master/README.md). This is where the Pac-man and Maze objects are instantiated, the scene and camera are established, meshes get drawn, and user interaction is handled.

TODO: add more to this
