#version 330

// Vertex shader

layout (location = 0) in vec3 vertex_position;
layout (location = 1) in vec3 vertex_normal;
layout (location = 2) in vec2 vertex_texture_coord;

// Normal of the current point on the surface
out vec3 normal;
out vec2 texture_coord;


void main(void)
{
	// Simple pass through shader. Keeps the normals and vertices in object space
	gl_Position = vec4(vertex_position, 1.0);
    normal = vertex_normal;
    texture_coord = vertex_texture_coord;
}
