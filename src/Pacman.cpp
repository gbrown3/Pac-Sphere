//
//  Pacman.cpp
//  Pac-Sphere
//
//  Created by Gabriel Brown on 10/22/18.
//

#include "Pacman.h"
#include "Sphere.h"
#include <glm/glm.hpp>
#include "glm/ext.hpp"

using namespace std;
using namespace basicgraphics;
using namespace glm;

namespace pacsphere {
    
    Pacman::Pacman(vec3 position) {
        
        // Setup joints for animation
        vector<shared_ptr<pacsphere::Joint>> newJoints = vector<shared_ptr<pacsphere::Joint>>();

        // NOTE: each joint is in pacman model space, so origin is at center of pacman sphere
        // RED
        Joint* centerJointPtr = new Joint(vec3(0, 0, 0), vec4(1, 0, 0, 1));
        shared_ptr<Joint> centerJoint(centerJointPtr);

        // GREEN
        Joint* rightLipPtr = new Joint(vec3(0, PAC_RADIUS, 0), vec4(0, 1, 0, 1));
        shared_ptr<Joint> rightLip(rightLipPtr);

        // BLUE
        Joint* leftLipPtr = new Joint(vec3(0, PAC_RADIUS, 0), vec4(0, 0, 1, 1));
        shared_ptr<Joint> leftLip(leftLipPtr);

        newJoints.push_back(centerJoint);
        newJoints.push_back(rightLip);
        newJoints.push_back(leftLip);

        // Initialize mesh with joints

        _mesh.reset(new Sphere(position, PAC_RADIUS, PAC_COLOR, nullptr, newJoints));
    }
    
    void Pacman::draw(basicgraphics::GLSLProgram &shader, const glm::mat4 &modelMatrix) {
        _mesh->draw(shader, modelMatrix);
    }
    
    void Pacman::animate(float currentFrameTime) {
        
        vector<shared_ptr<Joint>> joints = _mesh->getJoints();
        
        float overeallAnimationProgress = ((float)((int)currentFrameTime % ANIMATION_LENGTH))/ANIMATION_LENGTH;

        float leftLipAngle;
        float rightLipAngle;
        
        // If opening mouth
        if (overeallAnimationProgress < 0.5) {
            
            float angleDifference = MAX_ANGLE_DIFFERENCE * overeallAnimationProgress*2;

            rightLipAngle = M_PI/2 - angleDifference;
            leftLipAngle = M_PI/2 + angleDifference;

            joints[1]->_rotation = rotate(mat4(1.0), -angleDifference, vec3(0, 0, 1)); //* joints[1]->_rotation;
            joints[2]->_rotation = rotate(mat4(1.0), angleDifference, vec3(0, 0, 1)); //* joints[2]->_rotation;

        }
        // If closing mouth
        else {
            
            float angleDifference = MAX_ANGLE_DIFFERENCE * (overeallAnimationProgress - 0.5)*2;

            rightLipAngle = (M_PI/2 - MAX_ANGLE_DIFFERENCE) + angleDifference;
            leftLipAngle = (M_PI/2 + MAX_ANGLE_DIFFERENCE) - angleDifference;
            
            joints[1]->_rotation = rotate(mat4(1.0), angleDifference, vec3(0, 0, 1)); //* joints[1]->_rotation;
            joints[2]->_rotation = rotate(mat4(1.0), -angleDifference, vec3(0, 0, 1)); //* joints[2]->_rotation;
            
        }
    
        // Update rotations
        //joints[1]->_rotation = rotate(mat4(1.0f), rightLipAngle, vec3(0, 0, 1));
        //joints[2]->_rotation = rotate(mat4(1.0f), leftLipAngle, vec3(0, 0, 1));

        // Set new positions using these angles
        vec3 newRightLipPos = vec3(cos(rightLipAngle), sin(rightLipAngle), 0);
        vec3 newLeftLipPos = vec3(cos(leftLipAngle), sin(leftLipAngle), 0);



//        vec3 newRightLipPos = vec3(0);
//        vec3 newLeftLipPos = vec3(0);

        
        // Assume rightLip is index 1, left is index 2
        joints[1]->_localPosition = newRightLipPos;
        joints[2]->_localPosition = newLeftLipPos;
        

        _mesh->updateJoints(joints);
    }
}
