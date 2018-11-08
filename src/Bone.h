//
//  Bone.hpp
//  Pac-Sphere
//
//  Created by Gabriel Brown on 11/8/18.
//

#ifndef Bone_hpp
#define Bone_hpp

#include <stdio.h>
#include <glm/glm.hpp>
#include <BasicGraphics.h>

namespace pacsphere {
    
    /**
     * Represents a bone to be used for rigging, including access to it's start and end points,
     * a vector between the two, and an option to draw a graphical representation.
     */
    class Bone {
        
    public:
        
        static constexpr float BODY_RADIUS = 1.0f;
        static constexpr float JOINT_RADIUS = 1.0f;
        
        Bone(glm::vec3 localStartPos, glm::vec3 localEndPos, glm::mat4 parentTransform);
        
        /**
         * Draws a cylinder to represent the body, as well as a green sphere
         * for the start point and a red sphere for the end point.
         */
        void draw(basicgraphics::GLSLProgram &shader);
        
        glm::vec3 getLocalStartPos() { return _localStartPos; };
        glm::vec3 getLocalEndPos() { return _localEndPos; };
        glm::vec3 getWorldStartPos() { return _worldStartPos; };
        glm::vec3 getWorldEndPos() { return _worldEndPos; };
        
        
        // NOTE: NOT normalized
        glm::vec3 getStartToEndVec() { return _localEndPos - _localStartPos; };
        
        
    private:
        
        glm::vec3 _localStartPos;
        glm::vec3 _localEndPos;
        
        glm::vec3 _worldStartPos;
        glm::vec3 _worldEndPos;
        
        glm::mat4 _parentTransform;
        
        std::unique_ptr<basicgraphics::Cylinder> _boneBody;
        std::unique_ptr<basicgraphics::Sphere> _startJoint;
        std::unique_ptr<basicgraphics::Sphere> _endJoint;
    };
}

#endif /* Bone_hpp */
