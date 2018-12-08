//
// Created by garri1105 on 10/29/18.
//

#ifndef PAC_SPHERE_SPHERE_H
#define PAC_SPHERE_SPHERE_H

#include <stdio.h>
#include <unordered_map>
#include "AnimatedMesh.h"
#include "Hashtable.h"

using namespace basicgraphics;

namespace pacsphere {
    class Sphere {
    public:
        Sphere(const glm::vec3 &position, float radius, const glm::vec4 &color, const std::string texturePath = "");
        ~Sphere(){};
        void setupSphereMesh();
        void draw(basicgraphics::GLSLProgram &shader, const glm::mat4 &modelMatrix);


        std::unique_ptr<AnimatedMesh> _mesh;
        unsigned char * _image = new unsigned char[100000];
        vec2 getTexturePosition(vec3 vertexPos);

    protected:
        const glm::vec3 _position;
        const float _radius;
        const glm::vec4 _color;
        const string _texturePath;
//        std::array<std::array<vec3>> vertexMap;
    };
}

#endif //PAC_SPHERE_SPHERE_H
