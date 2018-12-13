#version 330

layout (location = 0) in vec3 vertex_position;
layout (location = 1) in vec3 vertex_normal;
layout (location = 2) in vec2 vertex_texcoord;
layout (location = 3) in vec3 vertex_joint_weights;

uniform mat4 projection_mat, view_mat, model_mat;
uniform mat3 normal_mat;

// Used to determine new vertex positions when joint has been moved
uniform mat4 centerJointRotation, rightJointRotation, leftJointRotation;

// Stand in for boolean. 1 = use joints, 0 = don't
uniform int useJoints;

out vec3 position_world, normal_world;
out vec2 texture_coordinates;


void main () {
    
    // Ultimate vertex position should be affected by a combination of how each joint has moved.
    // Below are records of a few other attempts at skinning algorithms:
    
    // ATTEMPT 1 (SEA URCHIN, depending on how weights are assigned)
//    mat4 jointRotation =    vertex_joint_weights[0] * centerJointRotation +
//                            vertex_joint_weights[1] * rightJointRotation  +
//                            vertex_joint_weights[2] * leftJointRotation;
    
    // ATTEMPT 2
//    float originalPosWeight = 1.0 - (vertex_joint_weights[1] + vertex_joint_weights[2]);
//    mat4 weightedOriginalTransform = mat4(1.0);
//
//    weightedOriginalTransform[3][0] = vertex_position[0];
//    weightedOriginalTransform[3][1] = vertex_position[1];
//    weightedOriginalTransform[3][2] = vertex_position[2];
//
//    weightedOriginalTransform *= originalPosWeight;
    
    
    // ATTEMPT 3 (Pineapple)
    
    // Disregard center since pacman never actually moves, assume either right or left weight is 0
    // mat4[col][row]
    mat4 jointRotation =    vertex_joint_weights[1] * rightJointRotation    +
                            vertex_joint_weights[2] * leftJointRotation;

    
    // The model space position and normal with joint rotation taken into account
    vec4 newModelPosition = jointRotation * vec4(vertex_position, 1.0);
    vec3 newVertexNormal = vec3(jointRotation * vec4(vertex_normal, 1.0));
    
    // The world space vertex position, both with joint rotation taken into
    // account and ignored. Both are calculated so that skinning animation can
    // easily be turned on or off in main program
    vec3 jointPosition = vec3(model_mat * newModelPosition);
    vec3 standardPosition = vec3 (model_mat * vec4(vertex_position, 1.0));
    
    // The world space vertex position ultimately passed to the fragment shader
    position_world = useJoints * jointPosition + (1-useJoints) * standardPosition;
    
    // The vertex normal both with and without joint rotations taken into account
    vec3 jointNormal = normalize(normal_mat * newVertexNormal);
    vec3 standardNormal = normalize(normal_mat * vertex_normal);
    
    // The normal ultimately passed to the fragment shader
    normal_world = useJoints * jointNormal + (1-useJoints) * standardNormal;
    
    texture_coordinates = vertex_texcoord;
    gl_Position = projection_mat * view_mat * vec4 (position_world, 1.0);
}
