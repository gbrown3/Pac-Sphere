//
// Created by garri1105 on 10/29/18.
//

#define M_PI       3.14159265358979323846   // pi

#include "Sphere.h"

using namespace std;
using namespace basicgraphics;

namespace pacsphere {
    Sphere::Sphere(const glm::vec3 &position, const float radius, const glm::vec4 &color, const shared_ptr<Texture> texture) :
    _position(position), _radius(radius), _color(color), _texture(texture) {
        setupSphereMesh();
    }

    void Sphere::setupSphereMesh() {
        const int STACKS = 500;
        const int SLICES = 500;
        vector<AnimatedMesh::Vertex> cpuVertexArray = vector<AnimatedMesh::Vertex>();
        vector<int> cpuIndexArray = vector<int>();

        vector<shared_ptr<Texture>> textures = vector<shared_ptr<Texture>>();
        if (_texture) {
            textures.push_back(_texture);
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
                
                // TODO: add in joint weights
                currentVertex = { vertexPos, normalize(vertexPos), vec2(-j/float(SLICES) + 0.5, i/float(STACKS)) };
                
                cpuVertexArray.push_back(currentVertex);

                // Bottom vertex
                xCoord = _radius*cos(angle)*bottomStackLength;
                zCoord = _radius*sin(angle)*bottomStackLength;
                vertexPos = vec3(xCoord, bottomStack, zCoord);
                
                // TODO: add in joint weights
                currentVertex = { vertexPos, normalize(vertexPos), vec2(-j/float(SLICES) + 0.5, (i+1)/float(STACKS)) };
                
                cpuVertexArray.push_back(currentVertex);
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

}
