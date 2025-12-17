#version 460
in vec2 texcoord;
out vec2 vTexCoord;
out vec2 fragCoord;
out vec3 pos;
uniform mat4 modelViewProjectionMatrix;
in vec4 position;

void main(){
    vTexCoord = texcoord;
    fragCoord = position.xy;
    pos = position.xyz;
    gl_Position = modelViewProjectionMatrix * position;
}