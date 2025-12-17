#version 460

uniform sampler2DRect tex;
in vec2 fragCoord;
out vec4 fragColor;
uniform int columns;
uniform int rows;

vec2 repeat(vec2 _st, float repeatX, float repeatY) {
   vec2 st = _st * vec2(repeatX, repeatY);
   st.x += step(1., mod(st.y,2.0));
   st.y += step(1., mod(st.x,2.0));
   return fract(st);
}

void main(){
vec2 st = fragCoord.xy/vec2(1920.,1080.);
st = repeat(st,columns,rows);
st *= vec2(1920,1080);
fragColor = texture(tex, st);
}