//
//  AnimatedModel.hpp
//  Pac-Sphere
//
//  Created by Gabriel Brown on 11/19/18.
//
//  \brief An alternate implementation of basicgraphics::AnimatedModel, which is composed of a series of AnimatedMesh objects
//  and allows access to them

#ifndef AnimatedModel_h
#define AnimatedModel_h

#include <iostream>
#include <iomanip>
#include <memory>
#include <string>
#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/DefaultLogger.hpp>
#include <assimp/LogStream.hpp>
#include <assimp/ProgressHandler.hpp>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <mutex>
#include "Mesh.h"
#include "GLSLProgram.h"

#include "AnimatedMesh.h"

namespace pacsphere {
    
    typedef std::shared_ptr<class Importer> ImporterRef;
    
    class ProgressReporter : public Assimp::ProgressHandler
    {
    public:
        ProgressReporter();
        ~ProgressReporter();
        bool Update(float percentage = -1.f);
        void reset();
    private:
        bool _firstUpdate;
    };
    
    
    /**
     * Essentially the same as a BasicGraphics model, but with the option to set different
     * material colors for each mesh in the model.
     */
    class AnimatedModel : public std::enable_shared_from_this<AnimatedModel>
    {
    public:
        
        /*!
         * Tries to load a AnimatedModel from disk. Scale can be used to scale the vertex locations of the AnimatedModel. If the AnimatedModel contains textures than materialColor will be ignored.
         */
        AnimatedModel(const std::string &filename, const double scale, glm::vec4 materialColor = glm::vec4(1.0));
        
        /*!
         * Given a string in nff format, this will try to load a AnimatedModel
         */
        AnimatedModel(const std::string &fileContents, glm::vec4 materialColor = glm::vec4(1.0));
        virtual ~AnimatedModel();
        
        virtual void draw(basicgraphics::GLSLProgram &shader);
        
        /*!
         * Sets every mesh in the model to be a uniform color
         */
        void setMaterialColor(const glm::vec4 &color);
        
        /*!
         * Given a list of colors that's the same size as the number of meshes in the model, sets each mesh to be the corresponding color
         */
        void setMaterialColors(const std::vector<glm::vec4> &colors);
        
        
    private:
        
        glm::vec4 _materialColor;
        
        static std::mutex _mutex;
        
        static thread_local Assimp::Importer _importer;
        std::unique_ptr<ProgressReporter> _reporter;
        std::vector< std::shared_ptr<AnimatedMesh> > _meshes;
        std::vector< std::shared_ptr<basicgraphics::Texture> > _textures;
        
        void importMesh(const std::string &filename, int &numIndices, const double scale);
        void importMeshFromString(const std::string &fileContents);
        void processNode(aiNode* node, const aiScene* scene, const glm::mat4 scaleMat);
        std::shared_ptr<AnimatedMesh> processMesh(aiMesh* mesh, const aiScene* scene, const glm::mat4 scaleMat);
        std::vector<std::shared_ptr<basicgraphics::Texture> > loadMaterialTextures(aiMaterial* mat, aiTextureType type);
        
    };
    
}

#endif /* AnimatedModel_h */
