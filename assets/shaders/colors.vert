#version 330 core
layout(location=0)in vec3 position;layout(location=1)in vec3 color_in;uniform mat4 PVM;out vec4 fragColor;void main(){gl_Position=PVM*vec4(position,1);fragColor=vec4(color_in,1);}