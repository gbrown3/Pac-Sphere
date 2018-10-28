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

// Strongly based on various objects in BasicGraphics, with some slight modifications to suit our needs
class Ghost {
public:
    
    enum Ghost_Type {
        INKY,
        PINKY,
        BLINKY,
        CLYDE
    };
    
    /*!
     * Create ghost of a particular type centered at the specified position
     */
    Ghost(const glm::vec3 &position, Ghost_Type ghost);
    //virtual ~Ghost();
    
    virtual void draw(basicgraphics::GLSLProgram &shader, const glm::mat4 &modelMatrix);
    
private:
    
    std::shared_ptr<basicgraphics::Model> _model;
    
    std::shared_ptr<basicgraphics::Model> getModelInstance(string fileName);
    
    const glm::vec3 _position;
};


#endif /* Ghost_hpp */
