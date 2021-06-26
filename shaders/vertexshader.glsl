#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec2 vertexUV;
layout(location = 2) in float lightValue;

// Output data; will be interpolated for each fragment
out vec2 UV;

out float L;

// Values that stay constant for the whole mesh.
uniform mat4 MVP;

void main(){
    // gl_Position is a variable we dont have to define and we must set it to something.
    // The compiler will use it for the position of the vector.

    // Output position of the vertex, in clip space: MVP * position
    gl_Position = MVP * vec4(vertexPosition_modelspace, 1);

    // UV of the vertex, No special space for this one.
    UV = vertexUV;
    L = lightValue;
}