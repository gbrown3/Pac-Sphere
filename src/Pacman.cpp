//
//  Pacman.cpp
//  Pac-Sphere
//
//  Created by Gabriel Brown on 10/22/18.
//

#include "Pacman.h"
#include "Sphere.h"

using namespace std;
using namespace basicgraphics;

namespace pacsphere {
    
    Pacman::Pacman(vec3 position) {
        
        _mesh.reset(new Sphere(position, PAC_RADIUS, PAC_COLOR));
    }
    
    void Pacman::draw(basicgraphics::GLSLProgram &shader, const glm::mat4 &modelMatrix) {
        _mesh->draw(shader, modelMatrix);
    }
}
