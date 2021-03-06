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
    
    /**
     * The class representing the yellow puck himself. Essentially a Sphere object that's always yellow,
     * has three animation joints (center, left lip, right lip), and can move those joints at variable
     * speed and angle to mimic the opening and closing of his mouth.
     */
    class Pacman {
    public:
        
        /*!
         * Creates the sphere representing pacman at the given position, in addition
         * to setting up joints and color. 
         */
        Pacman(glm::vec3 position);
        
        void draw(basicgraphics::GLSLProgram &shader, const glm::mat4 &modelMatrix);
        
        /*!
         *  Moves Pacmans joints based on the time difference since the last frame
         * currentFrameTime: current frame time, in milliseconds
         */
        void animate(float currentFrameTime);
        
        std::unique_ptr<Sphere> _mesh;
        
    private:

        static constexpr float PAC_RADIUS = 1.0f;
        static constexpr int ANIMATION_LENGTH = 1000;           // time it should take for one full animation loop, in milliseconds
        static constexpr float MAX_ANGLE_DIFFERENCE = M_PI/2;   // the largest angle pacman's lips can move away from resting position
        
        
        glm::vec4 PAC_COLOR = glm::vec4(1, 1, 0, 1);   // Pacman yellow
        
        glm::vec3 _position;

    };
}

#endif /* Pacman_hpp */
