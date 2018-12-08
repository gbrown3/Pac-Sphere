//
// Created by garri1105 on 10/29/18.
//

#define M_PI       3.14159265358979323846   // pi

#include <SOIL.h>
#include "Sphere.h"

using namespace std;
using namespace basicgraphics;

namespace pacsphere {
    Sphere::Sphere(const glm::vec3 &position, const float radius, const glm::vec4 &color, const string texture, std::vector<std::shared_ptr<Joint>> joints) :
    _position(position), _radius(radius), _color(color), _texturePath(texture), _joints(joints) {
        setupSphereMesh();
    }

    void Sphere::setupSphereMesh() {
        const int STACKS = 500;
        const int SLICES = 500;
        vector<AnimatedMesh::Vertex> cpuVertexArray = vector<AnimatedMesh::Vertex>();
        vector<int> cpuIndexArray = vector<int>();

        vector<shared_ptr<Texture>> textures = vector<shared_ptr<Texture>>();

        if (_texturePath != "") {
            shared_ptr<Texture> texture = Texture::create2DTextureFromFile(_texturePath);

            int width, height, channels;
            _image = SOIL_load_image(_texturePath.c_str(), &width, &height, &channels, SOIL_LOAD_AUTO);

            if (texture) {
                textures.push_back(texture);
            }
        }

        float stackAngle = M_PI/STACKS;
        AnimatedMesh::Vertex currentVertex;


        for (int i = 0; i < STACKS; i++) {

            float angle, xCoord, zCoord;

            float topStack = _radius * (1 - 2*i/float(STACKS));
            float bottomStack = _radius * (1 - 2*(i+1)/float(STACKS));
            float topStackLength = sqrt(abs(sin(i*stackAngle)));
            float bottomStackLength = sqrt(abs(sin((i+1)*stackAngle)));
            int totalVertices = i*(SLICES + 1)*2;

            for (int j = 0; j < SLICES + 1; j++) {

                angle = j*M_PI*2.0/SLICES;

                // Top vertex
                xCoord = _radius*cos(angle)*topStackLength;
                zCoord = _radius*sin(angle)*topStackLength;
                vec3 vertexPos = vec3(xCoord, topStack, zCoord);
                // Add in joint weights, if any were passed in (otherwise they can just be 0, doesn't matter)
                vec3 weights = vec3(0);

                if (_joints.size() > 0) {
                    vec3 centerJointPos = _joints[0]->_localPosition;
                    vec3 rightJointPos = _joints[1]->_localPosition;
                    vec3 leftJointPos = _joints[2]->_localPosition;

                    // Joint should have more of an effect, and therefore a higher weight the closer it is
                    // Weight values: 0-1
                    float centerWeight = 1 - distance(centerJointPos, vertexPos)/(_radius * 2);
                    float rightWeight = 1 - distance(rightJointPos, vertexPos)/(_radius * 2);
                    float leftWeight = 1 - distance(leftJointPos, vertexPos)/(_radius * 2);

                    // Average out weights so they all add to 1
                    float totalWeight = centerWeight + rightWeight + leftWeight;

                    centerWeight = centerWeight/totalWeight;
                    rightWeight = rightWeight/totalWeight;
                    leftWeight = leftWeight/totalWeight;

                    weights = vec3(centerWeight, rightWeight, leftWeight);
                    //cout << "Weights(center, right, left): " << to_string(weights);
                }
                vec2 texturePos = vec2(-j/float(SLICES) + 0.5, i/float(STACKS));
                currentVertex = { vertexPos, normalize(vertexPos), texturePos};
                cpuVertexArray.push_back(currentVertex);
//                vertexMap[vertexPos] = texturePos;

                // Bottom vertex
                xCoord = _radius*cos(angle)*bottomStackLength;
                zCoord = _radius*sin(angle)*bottomStackLength;
                vertexPos = vec3(xCoord, bottomStack, zCoord);
                // Add in joint weights, if any were passed in (otherwise they can just be 0, doesn't matter)
                weights = vec3(0);

                if (_joints.size() > 0) {
                    vec3 centerJointPos = _joints[0]->_localPosition;
                    vec3 rightJointPos = _joints[1]->_localPosition;
                    vec3 leftJointPos = _joints[2]->_localPosition;

                    // Joint should have more of an effect, and therefore a higher weight the closer it is
                    // Weight values: 0-1
                    float centerWeight = 1 - distance(centerJointPos, vertexPos)/(_radius * 2);
                    float rightWeight = 1 - distance(rightJointPos, vertexPos)/(_radius * 2);
                    float leftWeight = 1 - distance(leftJointPos, vertexPos)/(_radius * 2);

                    // Average out weights so they all add to 1
                    float totalWeight = centerWeight + rightWeight + leftWeight;

                    centerWeight = centerWeight/totalWeight;
                    rightWeight = rightWeight/totalWeight;
                    leftWeight = leftWeight/totalWeight;

                    weights = vec3(centerWeight, rightWeight, leftWeight);
                    //cout << "Weights(center, right, left): " << to_string(weights);
                }
                texturePos = vec2(-j/float(SLICES) + 0.5, (i+1)/float(STACKS));
                currentVertex = { vertexPos, normalize(vertexPos), texturePos};
                cpuVertexArray.push_back(currentVertex);
//                vertexMap[vertexPos] = texturePos;
            }

            for (int j = totalVertices; j < totalVertices + SLICES*2 + 1; j+=2 ) {
                cpuIndexArray.push_back(j + 1); // bottom
                cpuIndexArray.push_back(j);  // top
            }
        }

        const int numVertices = cpuVertexArray.size();
        const int cpuVertexByteSize = sizeof(AnimatedMesh::Vertex) * numVertices;
        const int cpuIndexByteSize = sizeof(int) * cpuIndexArray.size();

        _mesh.reset(new AnimatedMesh(textures, GL_TRIANGLE_STRIP, GL_STATIC_DRAW,
                             cpuVertexByteSize, cpuIndexByteSize, 0, cpuVertexArray,
                             cpuIndexArray.size(), cpuIndexByteSize, &cpuIndexArray[0]));
    }

    vec2 Sphere::getTexturePosition(vec3 vertexPos) {
//        return vertexMap[vertexPos];
    }

    void Sphere::draw(GLSLProgram &shader, const glm::mat4 &modelMatrix) {

        glm::mat4 translate = glm::translate(glm::mat4(1.0), _position);
        glm::mat4 model = modelMatrix * translate;
        shader.setUniform("model_mat", model);
        shader.setUniform("normal_mat", mat3(transpose(inverse(model))));
        _mesh->setMaterialColor(_color);
        _mesh->draw(shader);
        shader.setUniform("model_mat", modelMatrix);
        shader.setUniform("normal_mat", mat3(transpose(inverse(modelMatrix))));
    }


    void Sphere::updateJoints(vector<shared_ptr<Joint>> newJoints) {

        for (int i = 0; i < _joints.size(); i++) {

            _joints[i]->_localPosition = newJoints[i]->_localPosition;
        }


    }

    void Sphere::drawJoints(basicgraphics::GLSLProgram &shader, const glm::mat4 &modelMatrix) {

        for (shared_ptr<Joint> joint : _joints) {

            joint->draw(shader, modelMatrix);
        }
    }

}
