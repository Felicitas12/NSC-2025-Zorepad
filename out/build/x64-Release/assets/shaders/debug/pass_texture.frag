#version 420
in vec2 TexCoord;out vec4 FragColor;layout(binding=0)uniform sampler2D texture1;void main(){FragColor=texture(texture1,TexCoord);if(FragColor.w<.1)discard;}