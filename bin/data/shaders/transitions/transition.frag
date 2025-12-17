#version 460

uniform sampler2DRect prevBuffer;
uniform sampler2DRect nextBuffer;
uniform float progress, aspect;
uniform int mode;
in vec2 fragCoord;
out vec4 fragColor;

vec4 square(vec2 st, float width){
vec2 tl = step(vec2(-width),st);
vec2 br = step(vec2(1.-width),1.-st);
float sq = br.x * br.y * tl.x * tl.y;
return vec4(vec3(sq),1.); 
}

void main(){
vec2 st = fragCoord.xy/vec2(1920.,1080.);
vec4 prev = texture(prevBuffer,fragCoord);
vec4 next = texture(nextBuffer,fragCoord);
if (mode == 0){
fragColor = mix(prev,next,progress);
}
else if (mode == 1){
st = st*2.-1.;
st.x *= aspect;
float circle = smoothstep(progress*2.2,progress*2.2+.1,length(st-vec2(.0)));
fragColor = mix(next,prev,circle);
}
else if (mode == 2){
float line = smoothstep(progress,progress+.1,st.x); 
fragColor = mix(next,prev,line);
}
else if (mode == 3){
float line = smoothstep(progress,progress+.1,st.y); 
fragColor = mix(next,prev,line);
}
else if (mode == 4){
st = st*2.-1.;
st.x *= aspect;
float squareDiv = square(st,progress*2.2).r;
fragColor = mix(prev,next,squareDiv);
}
}