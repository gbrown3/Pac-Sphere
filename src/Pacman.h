//
//  Pacman.hpp
//  Pac-Sphere
//
//  Created by Gabriel Brown on 10/22/18.
//

#ifndef Pacman_hpp
#define Pacman_hpp

#include <stdio.h>
#include <BasicGraphics.h>
#include "Sphere.h"

namespace pacsphere {
    
    class Pacman {
        
    public:
        
        Pacman(glm::vec3 position);
        
        void draw(basicgraphics::GLSLProgram &shader, const glm::mat4 &modelMatrix);
        
    private:

        static constexpr float PAC_RADIUS = 1.0f;
        
        // TODO: figure out how to make this a static constant
        glm::vec4 PAC_COLOR = glm::vec4(1, 1, 0, 1);   // Pacman yellow
        
        glm::vec3 _position;
        
        std::unique_ptr<Sphere> _mesh;

    };
}

#endif /* Pacman_hpp */
