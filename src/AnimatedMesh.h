//
//  AnimatedMesh.hpp
//  Pac-Sphere
//
//  Created by Gabriel Brown on 11/16/18.
//

#ifndef AnimatedMesh_h
#define AnimatedMesh_h

#include <stdio.h>
#include <BasicGraphics.h>
#include "Texture.h"
#include "Mesh.h"
#include "Joint.h"
#include "glm/ext.hpp"


namespace pacsphere {
    
    typedef std::shared_ptr<class AnimatedMesh> AnimatedMeshRef;
    
    /**
     * Similar to a basicgraphics Mesh, but allows access to vertex data and includes a series of joints
     *
     */
    class AnimatedMesh : public std::enable_shared_from_this<AnimatedMesh>{
        
    public:
        
        // Altered to include 3 joint weights
        struct Vertex {
            glm::vec3 position;
            glm::vec3 normal;
            glm::vec2 texCoord0;
            glm::vec3 jointWeights; // NOTE: this only works for pacman
        };
        
        // Constructor inputs are same as basicgraphics Mesh, implementation slightly different
        AnimatedMesh(std::vector<std::shared_ptr<basicgraphics::Texture> > textures, GLenum primitiveType, GLenum usage, int allocateVertexByteSize, int allocateIndexByteSize, int vertexOffset, const std::vector<pacsphere::AnimatedMesh::Vertex> &data, int numIndices = 0, int indexByteSize = 0, int* index = nullptr);
        
        virtual ~AnimatedMesh();
        
        
        virtual void draw(basicgraphics::GLSLProgram &shader);
        
        
        void setMaterialColor(const glm::vec4 &color);
        
        
        // Returns the number of bytes allocated in the vertexVBO
        int getAllocatedVertexByteSize() const;
        int getAllocatedIndexByteSize() const;
        // Returns the number of bytes actually filled with data in the vertexVBO
        int getFilledVertexByteSize() const;
        int getFilledIndexByteSize() const;
        int getNumIndices() const;
        
        GLuint getVAOID() const;
        
        // Update the vbos. startByteOffset+dataByteSize must be <= allocatedByteSize
        void updateVertexData(int startByteOffset, int vertexOffset, const std::vector<Vertex> &data);
        void updateIndexData(int totalNumIndices, int startByteOffset, int indexByteSize, int* index);
        
        
        
        
        // BELOW: public methods unique to AnimatedMesh
        
        std::vector<pacsphere::AnimatedMesh::Vertex> getVertexData() { return _vertexData; };
        
    private:
        
        // Variables from original mesh class
        GLuint _vaoID;
        GLuint _vertexVBO;
        GLuint _indexVBO;
        GLenum _primitiveType;
        
        int _allocatedVertexByteSize;
        int _allocatedIndexByteSize;
        int _filledVertexByteSize;
        int _filledIndexByteSize;
        int _numIndices;
        
        glm::vec4 _materialColor;
        
        std::vector<std::shared_ptr<basicgraphics::Texture> > _textures;
        
        // Unique to AnimatedMesh
        std::vector<pacsphere::AnimatedMesh::Vertex> _vertexData;
    };
}

#endif /* AnimatedMesh_h */
