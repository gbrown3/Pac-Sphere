//
//  Ghost.cpp
//  Pac-Sphere
//
//  Created by Gabriel Brown on 10/28/18.
//

#include "Ghost.h"
#include "Config.h"

using namespace std;

namespace pacsphere {
    
    Ghost::Ghost(const glm::vec3 &position, Ghost_Type ghost) : _position(position){
        
        string filePath = DATA_DIR + "ghost";
        
        switch (ghost) {
            case INKY:
                //filePath += "inky";
                _ghostColor = vec4(0.1, 1, 1, 1);   //cyan
                break;
                
            case PINKY:
                //filePath += "pinky";
                _ghostColor = vec4(1, 0.5, 1, 1);   //pink
                break;
                
            case BLINKY:
                //filePath += "blinky";
                _ghostColor = vec4(1, 0, 0, 1); //red
                break;
                
            case CLYDE:
                //filePath += "clyde";
                _ghostColor = vec4(1, 0.5, 0, 1);   //orange
                break;
                
            default:
                break;
        }
        
        // TODO: use collada file instead of .obj, it will have hierarchy that assimp can use
        filePath += ".obj";
        
        _meshColors = vector<vec4>();
        _meshColors.push_back(vec4(1, 1, 1, 1));
        _meshColors.push_back(_ghostColor);
        
        // Note: .obj files should be in resources folder
        _model = getModelInstance(filePath);
    }

    shared_ptr<AnimatedModel> Ghost::getModelInstance(string fileName){
        static shared_ptr<AnimatedModel> model(new AnimatedModel(fileName, 1.0, glm::vec4(1.0)));
        return model;
    }

    void Ghost::draw(basicgraphics::GLSLProgram &shader, const glm::mat4 &modelMatrix) {
        
        _model->setMaterialColor(_ghostColor);
        // TODO: swap to collada file and then use the method below instead
        //_model->setMaterialColors(_meshColors);
        
        glm::mat4 translate = glm::translate(glm::mat4(1.0), _position);
        // NOTE: scale matrix could also be included. Look at Sphere.cpp for example. May need to do this once proper size is determined
        glm::mat4 model = modelMatrix * translate;
        shader.setUniform("model_mat", model);
        shader.setUniform("normal_mat", mat3(transpose(inverse(model))));
        _model->draw(shader);
        shader.setUniform("model_mat", modelMatrix);
        shader.setUniform("normal_mat", mat3(transpose(inverse(modelMatrix))));
    }
    
}
