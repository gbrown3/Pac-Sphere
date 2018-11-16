//
//  AnimatedMesh.cpp
//  Pac-Sphere
//
//  Created by Gabriel Brown on 11/16/18.
//

#include "AnimatedMesh.h"

using namespace basicgraphics;
using namespace std;
using namespace glm;

namespace pacsphere {
    
    AnimatedMesh::AnimatedMesh(vector<shared_ptr<Texture> > textures, GLenum primitiveType, GLenum usage, int allocateVertexByteSize, int allocateIndexByteSize, int vertexOffset, const vector<Mesh::Vertex> &data, int numIndices, int indexByteSize, int* index)
    :
    basicgraphics::Mesh(textures, primitiveType, usage, allocateVertexByteSize, allocateIndexByteSize, vertexOffset, data, numIndices, indexByteSize, index){
        
        _vertexData = data;
    }
    
    
    
    
}
