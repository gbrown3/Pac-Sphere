#version 330

// You must specify what type of primitive is passed in
layout(triangles) in;
uniform sampler2D mazeTexture;

// ... and what type of primitive you are outputing and how many vertices. The geometry shader is run once
// for each primitive so we will output three lines (6 vertices), one for each normal.
layout(triangle_strip, max_vertices = 13) out;

uniform float mazeHeight;

uniform mat4 projection_mat, view_mat, model_mat;


// Example of a geometry shader custom input
in vec3 normal[3];
in vec2 texture_coord[3];

// Example of a geometry shader custom output
out vec4 color;

vec3 getNormal(vec4 pos1, vec4 pos2, vec3 norm)
{
   vec3 a = vec3(pos1) - vec3(pos2);
   return normalize(cross(a, norm));
}

vec3 GetNormal()
{
   vec3 a = vec3(gl_in[0].gl_Position) - vec3(gl_in[1].gl_Position);
   vec3 b = vec3(gl_in[2].gl_Position) - vec3(gl_in[1].gl_Position);
   return normalize(cross(a, b));
}


void main() {

    float primRadius = 0.25;

    vec3 norm = GetNormal();
    vec3 hVector = getNormal(gl_in[1].gl_Position, gl_in[2].gl_Position, norm);
    vec3 vVector = getNormal(gl_in[0].gl_Position, gl_in[2].gl_Position, norm);

    texture(mazeTexture, texture_coord[0]);
    color = texture(mazeTexture, texture_coord[0]);

    if ((model_mat * gl_in[0].gl_Position).z > 4 && abs(dot(hVector, vVector)) < 0.1 && color == vec4(0.0, 0.0, 0.0, 1.0)) {

        gl_Position = projection_mat*view_mat*model_mat * (gl_in[0].gl_Position + vec4(primRadius * (-hVector - vVector), 0.0));
        EmitVertex();
        gl_Position = projection_mat*view_mat*model_mat * (gl_in[0].gl_Position + vec4(primRadius * (-hVector - vVector), 0.0) + vec4(mazeHeight * normal[0], 0.0));
        EmitVertex();
        gl_Position = projection_mat*view_mat*model_mat * (gl_in[0].gl_Position + vec4(primRadius * (hVector - vVector), 0.0));
        EmitVertex();
        gl_Position = projection_mat*view_mat*model_mat * (gl_in[0].gl_Position + vec4(primRadius * (hVector - vVector), 0.0) + vec4(mazeHeight * normal[0], 0.0));
        EmitVertex();
        gl_Position = projection_mat*view_mat*model_mat * (gl_in[0].gl_Position + vec4(primRadius * (hVector + vVector), 0.0));
        EmitVertex();
        gl_Position = projection_mat*view_mat*model_mat * (gl_in[0].gl_Position + vec4(primRadius * (hVector + vVector), 0.0) + vec4(mazeHeight * normal[0], 0.0));
        EmitVertex();
        gl_Position = projection_mat*view_mat*model_mat * (gl_in[0].gl_Position + vec4(primRadius * (-hVector + vVector), 0.0));
        EmitVertex();
        gl_Position = projection_mat*view_mat*model_mat * (gl_in[0].gl_Position + vec4(primRadius * (-hVector + vVector), 0.0) + vec4(mazeHeight * normal[0], 0.0));
        EmitVertex();
        gl_Position = projection_mat*view_mat*model_mat * (gl_in[0].gl_Position + vec4(primRadius * (-hVector - vVector), 0.0));
        EmitVertex();
        gl_Position = projection_mat*view_mat*model_mat * (gl_in[0].gl_Position + vec4(primRadius * (-hVector - vVector), 0.0) + vec4(mazeHeight * normal[0], 0.0));
        EmitVertex();

        gl_Position = projection_mat*view_mat*model_mat * (gl_in[0].gl_Position + vec4(primRadius * (hVector - vVector), 0.0) + vec4(mazeHeight * normal[0], 0.0));
        EmitVertex();
        gl_Position = projection_mat*view_mat*model_mat * (gl_in[0].gl_Position + vec4(primRadius * (- hVector + vVector), 0.0) + vec4(mazeHeight * normal[0], 0.0));
        EmitVertex();
        gl_Position = projection_mat*view_mat*model_mat * (gl_in[0].gl_Position + vec4(primRadius * (hVector + vVector), 0.0) + vec4(mazeHeight * normal[0], 0.0));
        EmitVertex();

        EndPrimitive();
    }
}





