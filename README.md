# Ball Rolling Activity

In this activity, you will practice using transformations to translate and rotate a ball in response to the mouse input.

## Getting Started

Clone and generate the project files:

```
cd yourCodeDirectory
git clone https://github.com/mac-comp465-f18/ballrollingactivity
cd ballrollingactivity
mkdir build
cd build
cmake-gui ..
```

## To Do

Each frame inside onRenderGraphicsContext() update the sphere’s CoordinateFrame to make the sphere translate in the direction and magnitude specified by the dir vector. (Use the arrow keys to adjust dir interactively.  Use SPACEBAR to reset the sphere.)

Once you have translation working, make the ball rotate so it looks like it is rolling on the table. (Hint: Start by just making the ball rotate around a set axis.  Then, make it rotate around an axis you calculate based on dir.  Then, scale the angle of rotation based on the magnitude of dir.)
