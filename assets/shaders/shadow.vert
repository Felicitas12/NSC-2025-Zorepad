#version 420
layout(location=0)in vec3 aPos;layout(location=2)in vec2 aTexCoords;out vec2 TexCord;uniform mat4 model;void main(){TexCord=aTexCoords;gl_Position=model*vec4(aPos,1);}