//#version 330
//
//layout (location = 0) in vec3 vertex_position;
//layout (location = 1) in vec3 vertex_normal;
//layout (location = 2) in vec2 vertex_texture_coord;
//layout (location = 3) in vec3 vertex_joint_weights;
//
//uniform mat4 projection_mat, view_mat, model_mat;
//
//out vec3 normal;
//out vec2 texture_coord;
//out vec3 position_world;
//
//uniform mat4 centerJointRotation;
//uniform mat4 rightJointRotation;
//uniform mat4 leftJointRotation;
//
//void main(void)
//{
//    // Ultimate vertex position should be affected by a combination of how each joint has moved
//    vec4 centerJointImpact = vertex_joint_weights[0] * (centerJointRotation * vec4(vertex_position, 1));
//    vec4 rightJointImpact = vertex_joint_weights[1] * (rightJointRotation * vec4(vertex_position, 1));
//    vec4 leftJointImpact = vertex_joint_weights[2] * (leftJointRotation * vec4(vertex_position, 1));
//
//    // TODO: do I need to add something else to this? Maybe the initial position? Or take the average?
//    // TODO: also probs need to change normals
//    vec4 adjustedPosition = centerJointImpact + rightJointImpact + leftJointImpact;
//
//    position_world = vec3(model_mat * adjustedPosition);
//
//    gl_Position = projection_mat * view_mat * model_mat * adjustedPosition;
//    normal = vertex_normal;
//    texture_coord = vertex_texture_coord;
//}
#version 330

layout (location = 0) in vec3 vertex_position;
layout (location = 1) in vec3 vertex_normal;
layout (location = 2) in vec2 vertex_texcoord;
layout (location = 3) in vec3 vertex_joint_weights;

uniform mat4 projection_mat, view_mat, model_mat;
uniform mat3 normal_mat;

// Used to determine new vertex positions when joint has been moved
uniform mat4 centerJointRotation, rightJointRotation, leftJointRotation;

out vec3 position_world, normal_world;
out vec2 texture_coordinates;


void main () {
    
    // Ultimate vertex position should be affected by a combination of how each joint has moved
    vec4 centerJointImpact = vertex_joint_weights[0] * (centerJointRotation * vec4(vertex_position, 1));
    vec4 rightJointImpact = vertex_joint_weights[1] * (rightJointRotation * vec4(vertex_position, 1));
    vec4 leftJointImpact = vertex_joint_weights[2] * (leftJointRotation * vec4(vertex_position, 1));
    
    vec4 newModelPosition = centerJointImpact + rightJointImpact + leftJointImpact;
    
    //position_world = vec3 (model_mat * newModelPosition);
    position_world = vec3 (model_mat * vec4(vertex_position, 1.0));
    
    // TODO: incorporate the joint rotations into the normal too
    normal_world = normalize(normal_mat * vertex_normal);
    
    texture_coordinates = vertex_texcoord;
    gl_Position = projection_mat * view_mat * vec4 (position_world, 1.0);
}
