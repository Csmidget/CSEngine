#version 400
uniform sampler2D texSampler;
uniform vec3 lightColour = { 0.2,0.2,0.2 }; 
uniform vec3 emissiveColour = { 0,0,0 }; 
uniform vec3 ambientColour = { 0.4f,0.4f,0.4f }; 
uniform vec3 diffuseColour = { 0.3f,0.3f,0.3f }; 
uniform vec3 specularColour = { 0.0f,1.0f,0.0f }; 
uniform float shininess = 1.0f; 
uniform float alpha = 1.0f; 
in vec2 ex_texCoord; 
in vec3 ex_Normal;
in vec3 eyeSpaceLightPosV; 
in vec3 eyeSpaceVertPosV; 
out vec4 out_Color;
void main(void)
{
 vec3 lightDir = normalize(eyeSpaceLightPosV - eyeSpaceVertPosV); 
 float distance = abs(length(eyeSpaceLightPosV - eyeSpaceVertPosV) /3);
 vec3 normal = normalize(ex_Normal); 
 vec3 texColour = diffuseColour + vec3(texture(texSampler, ex_texCoord)); 
 vec3 diffuse = diffuseColour * lightColour * max(dot(ex_Normal, lightDir), 0) / (distance * distance); 
 vec3 specular = vec3(0, 0, 0); 
 out_Color = vec4(emissiveColour + ambientColour*texColour + diffuse + specular, alpha); 
}