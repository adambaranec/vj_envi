#version 460

precision mediump float;
in vec2 fragCoord;
uniform float time, aspect;
out vec4 fragColor;

vec4 hsv2rgba(float hue, float saturation, float value)
{
    vec3 c = vec3(hue, saturation, value);
    vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
    vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
    vec3 result = c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
    return vec4(vec3(result),1.);
}

void main(){
vec2 st = fragCoord.xy/vec2(1920.,1080.);
st.x += time*.7;
fragColor = hsv2rgba(0.,0.,.6*(sin(st.x*2)*.5+.5));
}
