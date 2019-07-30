#version 400

layout(location=0) in vec4 in_Position;
layout(location=1) in vec3 in_Normal;
layout(location=2) in vec2 in_texCoord;

out vec2 ex_texCoord;
out vec3 ex_Normal;
out vec3 eyeSpaceLightPosV;
out vec3 eyeSpaceVertPosV;
uniform mat4 projMat; 
uniform mat4 viewMat; 
uniform mat4 modelMat; 
uniform vec4 worldSpaceLightPos = { 1,0.0,1,1 };
void main(void)
{
 gl_Position = projMat * viewMat * modelMat * in_Position;
 ex_texCoord = in_texCoord;
 ex_Normal = mat3(viewMat * modelMat) * in_Normal; 
 eyeSpaceVertPosV = vec3(viewMat * modelMat * in_Position); 
 eyeSpaceLightPosV = vec3(viewMat * worldSpaceLightPos); 
}