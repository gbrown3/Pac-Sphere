//
//  GroundPlane.hpp
//  
//
//  Created by Bret Jackson on 2/15/17.
//
//

#ifndef GroundPlane_hpp
#define GroundPlane_hpp

#include <stdio.h>

#include "Mesh.h"
#include "GLSLProgram.h"
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_access.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

namespace basicgraphics {
    
    class GroundPlane {
    public:
        
        /*!
         * Creates a plane with the specified normal with running through the point
         */
        GroundPlane(const glm::vec3 &point, const glm::vec3 &normal);
        virtual ~GroundPlane();
        
        virtual void draw(GLSLProgram &shader, const glm::mat4 &modelMatrix);

        
    protected:
        std::unique_ptr<Mesh> _mesh;
        const glm::vec3 _point;
        glm::vec3 _normal;
    };
    
}

#endif /* GroundPlane_hpp */
