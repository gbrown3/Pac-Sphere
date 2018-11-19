//
//  Ghost.hpp
//  Pac-Sphere
//
//  Created by Gabriel Brown on 10/28/18.
//

#ifndef Ghost_hpp
#define Ghost_hpp

#include <stdio.h>
#include <BasicGraphics.h>
#include "Model.h"
#include "GLSLProgram.h"
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_access.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "AnimatedModel.h"

namespace pacsphere {
    
    enum Ghost_Type {
        INKY,
        PINKY,
        BLINKY,
        CLYDE
    };
    
    /**
     * Loads the .obj model of a ghost and sets its color based on which ghost it's supposed to represent.
     * Strongly based on various objects in BasicGraphics, with some slight modifications to suit our needs.
     */
    class Ghost {
        
    public:
        
        /*!
         * Create ghost of a particular type centered at the specified position
         */
        Ghost(const glm::vec3 &position, Ghost_Type ghost);
        //virtual ~Ghost();
        
        virtual void draw(basicgraphics::GLSLProgram &shader, const glm::mat4 &modelMatrix);
        
    private:
        
        std::shared_ptr<AnimatedModel> _model;
        
        std::shared_ptr<AnimatedModel> getModelInstance(string fileName);
        
        const glm::vec3 _position;
        
        glm::vec4 _ghostColor;
        std::vector<glm::vec4> _meshColors;
    };
    
}

#endif /* Ghost_hpp */
