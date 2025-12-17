#version 460

uniform sampler2DRect scene1;
uniform sampler2DRect scene2;
uniform float fade;
in vec2 fragCoord;
out vec4 fragColor;

void main(){
fragColor = mix(scene1, scene2, fade);
}