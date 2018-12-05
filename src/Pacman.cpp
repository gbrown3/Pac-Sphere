//
//  Pacman.cpp
//  Pac-Sphere
//
//  Created by Gabriel Brown on 10/22/18.
//

#include "Pacman.h"
#include "Sphere.h"
#include "glm/ext.hpp"

using namespace std;
using namespace basicgraphics;

namespace pacsphere {
    
    Pacman::Pacman(vec3 position) {
        
        _mesh.reset(new Sphere(position, PAC_RADIUS, PAC_COLOR));
    }
    
    void Pacman::draw(basicgraphics::GLSLProgram &shader, const glm::mat4 &modelMatrix) {
        _mesh->draw(shader, modelMatrix);
    }
    
    void Pacman::animate(float currentFrameTime) {
        
        vector<shared_ptr<Joint>> joints = _mesh->_mesh->getJoints();
        
        float overeallAnimationProgress = ((float)((int)currentFrameTime % ANIMATION_LENGTH))/ANIMATION_LENGTH;
        
        float leftLipAngle;
        float rightLipAngle;
        
        // If opening mouth
        if (overeallAnimationProgress < 0.5) {
            
            float angleDifference = MAX_ANGLE_DIFFERENCE * overeallAnimationProgress*2;
            
            leftLipAngle = M_PI/2 + angleDifference;
            rightLipAngle = M_PI/2 - angleDifference;
            
        }
        // If closing mouth
        else {
            
            float angleDifference = MAX_ANGLE_DIFFERENCE * (overeallAnimationProgress - 0.5)*2;
            
            leftLipAngle = (M_PI/2 + MAX_ANGLE_DIFFERENCE) - angleDifference;
            rightLipAngle = (M_PI/2 - MAX_ANGLE_DIFFERENCE) + angleDifference;
            
        }
    
        // Set new positions using these angles
        vec3 newLeftLipPos = vec3(cos(leftLipAngle), sin(leftLipAngle), 0);
        vec3 newRightLipPos = vec3(cos(rightLipAngle), sin(rightLipAngle), 0);
        
        // Assume rightLip is index 1, left is index 2
        joints[1]->_localPosition = newRightLipPos;
        joints[2]->_localPosition = newLeftLipPos;
        
        _mesh->_mesh->defineJoints(joints);
    }
}
