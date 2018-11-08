//
//  Bone.cpp
//  Pac-Sphere
//
//  Created by Gabriel Brown on 11/8/18.
//

#include "Bone.h"

using namespace basicgraphics;
using namespace std;
using namespace glm;

namespace pacsphere {
    
    Bone::Bone(glm::vec3 localStartPos, glm::vec3 localEndPos, glm::mat4 parentTransform) {
        
        _localStartPos = localStartPos;
        _localEndPos = localEndPos;
        _parentTransform = parentTransform;
        
        _worldStartPos = parentTransform * vec4(localStartPos, 1);
        _worldEndPos = parentTransform * vec4(localEndPos, 1);
        
        // Initialize visual representation in local coords, parent transform will be applied in draw()
        _boneBody.reset(new Cylinder(localStartPos, localEndPos, BODY_RADIUS, vec4(0, 0, 1, 1)));
        _startJoint.reset(new basicgraphics::Sphere(localStartPos, JOINT_RADIUS, vec4(0, 1, 0, 1)));
        _endJoint.reset(new basicgraphics::Sphere(localEndPos, JOINT_RADIUS, vec4(1, 0, 0, 1)));
    }
    
    
    void Bone::draw(GLSLProgram &shader) {
        
        _boneBody->draw(shader, _parentTransform);
        _startJoint->draw(shader, _parentTransform);
        _endJoint->draw(shader, _parentTransform);
    }
    
}
