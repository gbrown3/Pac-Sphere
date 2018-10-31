//
// Created by garri1105 on 10/29/18.
//

#ifndef PAC_SPHERE_SPHERE_H
#define PAC_SPHERE_SPHERE_H

#include <stdio.h>
#include <BasicGraphics.h>

using namespace basicgraphics;

namespace pacsphere {
    class Sphere {
    public:
        Sphere(const glm::vec3 &position, float radius, const glm::vec4 &color, const std::shared_ptr<Texture> texture = nullptr);
        ~Sphere(){};
        void setupSphereMesh();
        void draw(basicgraphics::GLSLProgram &shader, const glm::mat4 &modelMatrix);

    protected:
        const glm::vec3 _position;
        const float _radius;
        const glm::vec4 _color;
        const std::shared_ptr<Texture> _texture;
        std::unique_ptr<basicgraphics::Mesh> _mesh;
    };
}

#endif //PAC_SPHERE_SPHERE_H
