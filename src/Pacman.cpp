//
//  Pacman.cpp
//  Pac-Sphere
//
//  Created by Gabriel Brown on 10/22/18.
//

#include "Pacman.hpp"

Pacman::Pacman(float mazeRadius) {
    
    _mesh.reset(new basicgraphics::Sphere(vec3(0), PAC_RADIUS, vec4(1,1,0,1)));
}
