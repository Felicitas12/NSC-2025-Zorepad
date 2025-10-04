#version 420 core
out vec4 FragColor;in vec3 WorldPos;layout(binding=0)uniform samplerCube environmentMap;void main(){FragColor=vec4(textureLod(environmentMap,WorldPos,0.).xyz,1);gl_FragDepth=1.;}