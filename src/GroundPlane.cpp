//
//  GroundPlane.cpp
//  
//
//  Created by Bret Jackson on 2/15/17.
//
//

#include "GroundPlane.h"


using namespace glm;
using namespace std;

namespace basicgraphics {
    
    GroundPlane::GroundPlane(const glm::vec3 &point, const glm::vec3 &normal) : _point(point), _normal(normal)
    {
        _normal = normalize(_normal);
        
        std::vector<Mesh::Vertex> cpuVertexArray;
        std::vector<int>			 cpuIndexArray;

        
        std::shared_ptr<Texture> texture = Texture::create2DTextureFromFile("felt.png");
        
        texture->setTexParameteri(GL_TEXTURE_WRAP_S, GL_REPEAT);
        texture->setTexParameteri(GL_TEXTURE_WRAP_T, GL_REPEAT);
        texture->setTexParameteri(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        texture->setTexParameteri(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        //texture->setTexParameterf(GL_TEXTURE_MAX_ANISOTROPY_EXT, 16.0);
        
        vector<shared_ptr<Texture>> textures;
        textures.push_back(texture);
        
        vec3 up, right;
        if (abs(dot(_normal, vec3(0,0,1)) - 1.0) < glm::epsilon<float>()){
            up = vec3(0,1,0);
            right = vec3(1,0,0);
        }
        else{
            up = normalize(cross(_normal, vec3(1,0,0)));
            right = normalize(cross(up, _normal));
        }
        
        const float maxExtent = 100;
        
        Mesh::Vertex vert;
        vert.position = _point + maxExtent * right + maxExtent * up;
        vert.normal = _normal;
        vert.texCoord0 = glm::vec2(0, 0);
        cpuVertexArray.push_back(vert);
        cpuIndexArray.push_back(0);
        
        vert.position = _point - maxExtent * right + maxExtent * up;
        vert.normal = _normal;
        vert.texCoord0 = glm::vec2(0, 10);
        cpuVertexArray.push_back(vert);
        cpuIndexArray.push_back(1);
        
        vert.position = _point + maxExtent * right - maxExtent * up;
        vert.normal = _normal;
        vert.texCoord0 = glm::vec2(10, 0);
        cpuVertexArray.push_back(vert);
        cpuIndexArray.push_back(2);
        
        vert.position = _point - maxExtent * right - maxExtent * up;
        vert.normal = _normal;
        vert.texCoord0 = glm::vec2(10, 10);
        cpuVertexArray.push_back(vert);
        cpuIndexArray.push_back(3);
        
        const int numVertices = cpuVertexArray.size();
        const int cpuVertexByteSize = sizeof(Mesh::Vertex) * numVertices;
        const int cpuIndexByteSize = sizeof(int) * cpuIndexArray.size();
        _mesh.reset(new Mesh(textures, GL_TRIANGLE_STRIP, GL_STATIC_DRAW, cpuVertexByteSize, cpuIndexByteSize, 0, cpuVertexArray, cpuIndexArray.size(), cpuIndexByteSize, &cpuIndexArray[0]));
        
    }
    
    GroundPlane::~GroundPlane()
    {
    }
    
    void GroundPlane::draw(GLSLProgram &shader, const glm::mat4 &modelMatrix)
    {
        _mesh->draw(shader);
    }
    
}
