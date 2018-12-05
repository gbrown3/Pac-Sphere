//
// Created by garri1105 on 10/29/18.
//

#ifndef PAC_SPHERE_SPHERE_H
#define PAC_SPHERE_SPHERE_H

#include <unordered_map>
#include <stdio.h>
#include "AnimatedMesh.h"

using namespace basicgraphics;

namespace pacsphere {
    class Sphere {
    public:
        Sphere(const glm::vec3 &position, float radius, const glm::vec4 &color, const std::shared_ptr<Texture> texture = nullptr);
        ~Sphere(){};
        void setupSphereMesh();
        void draw(basicgraphics::GLSLProgram &shader, const glm::mat4 &modelMatrix);
        vec2 getTexturePosition(vec3 vertexPosition);

    protected:
        const glm::vec3 _position;
        const float _radius;
        const glm::vec4 _color;
        const std::shared_ptr<Texture> _texture;
        std::unique_ptr<AnimatedMesh> _mesh;
        std::unordered_map<vec3, vec2> vertexMap;
    };
}

#endif //PAC_SPHERE_SPHERE_H
