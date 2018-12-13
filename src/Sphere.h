//
// Created by garri1105 on 10/29/18.
//

#ifndef PAC_SPHERE_SPHERE_H
#define PAC_SPHERE_SPHERE_H

#include <stdio.h>
#include "AnimatedMesh.h"

using namespace basicgraphics;

namespace pacsphere {
    
    
    /*!
     * A modified version of the sphere class we made for the Earthquakes homework.
     * Notable additions include: joint data plus methods for drawing and updating them,
     * loading in the texture image as an array of bytes and using that to try and implement hit detection.
     */
    class Sphere {
    public:
        
        // Group 3D positions and their corresponding vertex coord. Used for hit detection.
        struct PositionTexPair {
            glm::vec3 position;
            glm::vec2 texCoord;
        };
        
        /*!
         * Create a sphere mesh at a specific position with the given radius, color, texture and joints
         */
        Sphere(const glm::vec3 &position, float radius, const glm::vec4 &color, const std::string texture = "", std::vector<std::shared_ptr<Joint>> joints = std::vector<std::shared_ptr<Joint>>());
        
        ~Sphere(){};
        
        /*!
         * Build up a series of vertices, along with with their normals, texture coordinates and joint weights,
         * and use all the data to construct an AnimatedMesh that looks like a sphere.
         */
        void setupSphereMesh();
        
        void draw(basicgraphics::GLSLProgram &shader, const glm::mat4 &modelMatrix);


        /*!
         * Go through every joint in the list and draw them
         */
        void drawJoints(basicgraphics::GLSLProgram &shader, const glm::mat4 &modelMatrix);

        /*!
         * Update joints by passing in vector with new vec3 positions
         */
        void updateJoints(std::vector<std::shared_ptr<Joint>> newJointPositions);

        std::vector<std::shared_ptr<Joint>> getJoints() { return _joints; };
        
        /*!
         * Given a 3D position, find the vertex closest to it on the sphere
         * and return the texture coordinate of that 3D vertex.
         */
        vec2 getTexturePosition(vec3 vertexPos);
        
        
        std::unique_ptr<AnimatedMesh> _mesh;
        
        unsigned char * _image = new unsigned char[100000];
        int imageWidth;
        int imageHeight;
        int imageChannels;

    protected:
        const glm::vec3 _position;
        const float _radius;
        const glm::vec4 _color;
        const string _texturePath;
        
        std::vector<std::shared_ptr<Joint>> _joints;    // List of joints to be used in animation
        std::vector<PositionTexPair> vertexMap;         // Master list of the texture coordinate corresponding with each vertex position in the sphere
    };
}

#endif //PAC_SPHERE_SPHERE_H
