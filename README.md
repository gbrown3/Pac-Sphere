# Pac-Sphere

Gabe Brown, Juan David Garrido

![Screenshot](pacsphere-normal.gif)

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

In CMake, configure the files, generate, and open up the project in whatever whatever code editor you decide to use.

Once in the project file, go to `Config.h`. We had difficulties getting the texture files to load in with relative paths,
so we'd recommend you get the absolute path to the `resources` folder, then set `DATA_DIR` equal to that. Make sure to comment out the other declaration of `DATA_DIR` too!

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
To create Pac-Sphere there were a lot of different decisions to be made due to the amount of details that the game must have. The first big decision we made was to modify the Sphere class we created in the Earthquakes HW in order to tesselate the sphere with any maze. The amount of stacks and slices was a big question that at first we chose randomly based on how good it looked and how efficiently it performed. Later on, when displacement mapping was implemented, we found that if there were too few slices or stacks then some of the vertices would skip over a wall in the texture and they would not be taken into account by the displacement mapping geometry shader. 250 stacks and 350 slices was a perfect balance of efficiency and aesthetics while correctly drawing every single piece of the maze.

When implementing the maze we decided that there we would be no real need to implement a fragment shader due to the walls being black and because all they really do is demark the limits for Pacman's and the ghosts' movements. 

We decided to use the modeling software Blender to make the ghost models, because we thought it would be too challenging to try and make them programmatically and Blender is free to use. We also decided to import the ghost models as Collada files (.dae) rather than Wavefront files (.obj), because Wavefront files didn't include enough information to allow us to assign different colors to different parts of the mesh, thereby preventing us from making the eyes white and the rest of the body a different color.

## Project Structure

### Config.h
As mentioned above, this is where you need to replace whatever path is there with your absolute path to the `resources` folder.
**If you don't do this, you won't be able to run the application.**

### App.h and App.cpp
These files contain the outermost structure of the app, based on the example in the MinVR [README](https://github.com/mac-comp465-f18/MinVR/blob/master/README.md). This is where the Pac-man and Maze objects are instantiated, the scene and camera are established, meshes get drawn, and user interaction is handled.

### Pacman.h and Pacman.cpp
Pacman is created based on our Sphere implementation. It consists of a Sphere with three joints. Two for the mouth and one for the center of Pacman. The other key feaure of Pacman is the `animate()` method, which moves the joints in a way that mimics the lips of Pacman's mouth opening and closing.

### Sphere.h and Sphere.cpp
Creates the sphere where all the meshes sit. This sphere is based on the Earthquakes HW where we learned how to tesselate a sphere. Our `Sphere` implementation adds to the Earthquake Sphere by accessing and holding on to the texture image bytes, as well as handling and updating joints. 

### Ghost.h and Ghost.cpp
Loads in the custom ghost model we made and sets the color of each mesh appropriately (based on which of the four pacman ghosts it's supposed to represent). The actual model is not loaded as a BasicGraphics model, but our custom `AnimatedModel` class. Unfortunately, we didn't get around to animating the ghosts, but this class would allow further customization should we choose to do so. 

### AnimatedModel.h and AnimatedModel.cpp
Our custom model class. Essentially the same as the Basicgraphics `Model` class, but with easier access to the different meshes loaded in with ASSIMP and the ability to store and change Joints.

### AnimatedMesh.h and AnimatedMesh.cpp
Our custom mesh class. Similar to `AnimatedModel`, it is essentially the same as the Basicgraphics `Mesh` class but allows easier access to certain parts of the mesh data. Additionally, the vertices have been modified to be able to include weights for 3 different joints, to be used for animation skinning.
