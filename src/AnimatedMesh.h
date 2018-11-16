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


namespace pacsphere {
    
    /**
     * Similar to a basicgraphics Mesh, but allows access to vertex data and includes a series of joints
     *
     */
    class AnimatedMesh : public basicgraphics::Mesh {
        
    public:
        
        AnimatedMesh(std::vector<std::shared_ptr<basicgraphics::Texture> > textures, GLenum primitiveType, GLenum usage, int allocateVertexByteSize, int allocateIndexByteSize, int vertexOffset, const std::vector<basicgraphics::Mesh::Vertex> &data, int numIndices = 0, int indexByteSize = 0, int* index = nullptr);
        
        /**
         * Normally I'd have joints be passed into the constructor, but the constructor is already so messy that
         * I'm allowing joints to be set for readability
         */
        void defineJoints(std::vector<std::shared_ptr<Joint>> newJoints) { _joints = newJoints; };
        
        std::vector<std::shared_ptr<Joint>> getJoints() { return _joints; };
        std::vector<basicgraphics::Mesh::Vertex> getVertexData() { return _vertexData; };
        
    private:
        
        std::vector<std::shared_ptr<Joint>> _joints;
        std::vector<basicgraphics::Mesh::Vertex> _vertexData;
    };
}

#endif /* AnimatedMesh_h */
