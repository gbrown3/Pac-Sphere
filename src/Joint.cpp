//
//  Joint.cpp
//  Pac-Sphere
//
//  Created by Gabriel Brown on 11/15/18.
//

#include "Joint.h"
#include "glm/ext.hpp"

using namespace basicgraphics;
using namespace std;
using namespace glm;

namespace pacsphere {
    
    // Root joint
    Joint::Joint(vec3 localPosition, vec4 testColor) {
        
        _localPosition = localPosition;
        _childJoints = vector<shared_ptr<Joint>>();
        _jointSphere.reset(new Sphere(vec3(0, 0, 0), SPHERE_RADIUS, testColor));
    }
    
    // Normal Joint
    Joint::Joint(std::shared_ptr<Joint> parentJoint, glm::vec3 localPosition) {
        
        _parentJoint = parentJoint;
        _localPosition = localPosition;
        _childJoints = vector<shared_ptr<Joint>>();
        _jointSphere.reset(new Sphere(localPosition, SPHERE_RADIUS, vec4(1, 0, 0, 1)));
        
        _parentJoint->addChild(shared_from_this());
        
    }
    
    
    void Joint::addChild(std::shared_ptr<Joint> childJoint) {
        
        _childJoints.push_back(childJoint);
    }
    
    
    void Joint::draw(GLSLProgram &shader, const mat4 &modelMatrix) {
        
        //cout << "Joint pos at draw time: " << to_string(_localPosition) << endl;
        
        mat4 translateToLocalPos = glm::translate(mat4(1), _localPosition);
        _jointSphere->draw(shader, modelMatrix * translateToLocalPos);
    }
}
