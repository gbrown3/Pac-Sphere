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

        // Right lip movement: (0, PAC_RADIUS, 0) -> (cos(M_PI/4), sin(M_PI/4), 0)
        // Left lip movement: (0, PAC_RADIUS, 0) -> (cos(M_PI*3/4), sin(M_PI*3/4), 0)
        
//        cout << "currentFrameTime: " << currentFrameTime << endl;
//        cout << "Animation length: " << ANIMATION_LENGTH << endl << endl;
        
        int mod = (int)currentFrameTime % ANIMATION_LENGTH;
        
//        cout << "currentFrameTime % Animationlength: " << mod << endl << endl;;
        
        float overeallAnimationProgress = ((float)((int)currentFrameTime % ANIMATION_LENGTH))/ANIMATION_LENGTH;
        
//        cout << "Animation progress: " << overeallAnimationProgress << endl;
        
        // 0-0.5*AnimationTime -> opening mouth
        // 0.5*AnimationTime-AnimationTime -> closing mouth
        
        float leftLipAngle;
        float rightLipAngle;
        
        // If opening mouth
        if (overeallAnimationProgress < 0.5) {
            
            float angleDifference = M_PI/4 * overeallAnimationProgress*2;
            
            leftLipAngle = M_PI/2 + angleDifference;
            rightLipAngle = M_PI/2 - angleDifference;
            
        }
        // If closing mouth
        else {
            
            float angleDifference = M_PI/4 * (overeallAnimationProgress - 0.5)*2;
            
            leftLipAngle = M_PI*3/4 - angleDifference;
            rightLipAngle = M_PI/4 + angleDifference;
            
        }
    
        // Set new positions using these angles
        vec3 newLeftLipPos = vec3(cos(leftLipAngle), sin(leftLipAngle), 0);
        vec3 newRightLipPos = vec3(cos(rightLipAngle), sin(rightLipAngle), 0);
        
//        cout << "New left lip pos: " << to_string(newLeftLipPos) << endl;
//        cout << "New right lip pos: " << to_string(newRightLipPos) << endl;
        
        // Assume rightLip is index 1, left is index 2
        joints[1]->_localPosition = newRightLipPos;
        joints[2]->_localPosition = newLeftLipPos;
        
        _mesh->_mesh->defineJoints(joints);
    }
}
