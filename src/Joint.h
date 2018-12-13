//
//  Joint.h
//  Pac-Sphere
//
//  Created by Gabriel Brown on 11/15/18.
//

#ifndef Joint_h
#define Joint_h

#include <stdio.h>
#include <glm/glm.hpp>
#include <BasicGraphics.h>

namespace pacsphere {
    
    /**
     * Represents a joint to be used for rigging, along with its parent Joint,
     * a list of child joints, and a method for drawing a graphical representation
     */
    class Joint : public std::enable_shared_from_this<Joint> {
        
    public:
        
        static constexpr float SPHERE_RADIUS = 0.1f;
        
        glm::vec3 _localPosition;
        
        /*!
         * Constuctor for root joint, initialized with coordinate in model space
         * and color to use for sphere representing its position
         */
        Joint(glm::vec3 localPosition, glm::vec4 testColor);
        
        
        /*!
         * Constructor for all other joints. Unfortunately, this never gets used
         * because when we tried to implement it we always got memory leaks,
         * but I'll leave it here in case we decide to come back to it in the future.
         * For now, there are no relationships between joints
         */
        Joint(std::shared_ptr<Joint> parentJoint, glm::vec3 localPosition);
        
        
        /*!
         * Add a child joint to this joint
         */
        void addChild(std::shared_ptr<Joint> childJoint);
        
        
        /*!
         * Draw a BasicGraphics sphere to show precisely where this joint is
         */
        void draw(basicgraphics::GLSLProgram &shader, const glm::mat4 &modelMatrix);
        
        // The joint's rotation. Should be updated when joint rotates in an animation, and is used for shader vertex skinning calculations
        glm::mat4 _rotation = mat4(1.0);
        
    private:
        
        std::shared_ptr<pacsphere::Joint> _parentJoint;
        std::vector<std::shared_ptr<Joint>> _childJoints;
        
        std::unique_ptr<basicgraphics::Sphere> _jointSphere;
    };
}

#endif /* Joint_h */
