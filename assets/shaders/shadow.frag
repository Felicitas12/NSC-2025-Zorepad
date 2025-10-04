#version 420 core
in vec2 TexCord;layout(binding=0)uniform sampler2D Mask;void main(){if(texture(Mask,TexCord).w<.5)discard;}