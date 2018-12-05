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
        
        // Constuctor for root joint, initialized with coordinate in model space (not world)
        Joint(glm::vec3 localPosition);
        
        // Constructor for all other joints
        Joint(std::shared_ptr<Joint> parentJoint, glm::vec3 localPosition);
        
        // Adds joint to list of children
        void addChild(std::shared_ptr<Joint> childJoint);
        
        // Draws basicgraphics sphere to show precisely where the joint is
        void draw(basicgraphics::GLSLProgram &shader, const glm::mat4 &modelMatrix);
        
    private:
        
        glm::vec3 _localPosition;
        std::shared_ptr<pacsphere::Joint> _parentJoint;
        std::vector<std::shared_ptr<Joint>> _childJoints;
        
        std::unique_ptr<basicgraphics::Sphere> _jointSphere;
    };
}

#endif /* Joint_h */
