#version 460

uniform sampler2DRect prevBuffer;
uniform sampler2DRect nextBuffer;
uniform int mode;
uniform float time;
in vec2 fragCoord;
out vec4 fragColor;

void main() {
  vec4 prevColor;
  if (mode == 0){
  prevColor = texture(prevBuffer, fragCoord);   
  } 
  else if (mode == 1){
  prevColor = texture(prevBuffer, fragCoord+vec2(5,0));   
  }
  else if (mode == 2){
  prevColor = texture(prevBuffer, fragCoord-vec2(0,3));   
  } 
  else if (mode == 3){
  prevColor = texture(prevBuffer, fragCoord-vec2(10,10));   
  }
  else if (mode == 4){
  vec2 uv = fragCoord.xy/vec2(1920.,1080.);
  vec2 center = vec2(0.5, 0.5);
  uv = (uv - center) / 1.01 + center;
  prevColor = texture(prevBuffer, uv*vec2(1920,1080));
  }
  else if (mode == 5){
  vec2 uv = fragCoord.xy/vec2(1920.,1080.);
  vec2 center = vec2(0.5, 0.5);
  uv = (uv - center) / 1.09 + center;
  prevColor = texture(prevBuffer, uv*vec2(1920,1080));
  }
  else if (mode == 6){
  vec2 uv = gl_FragCoord.xy / vec2(1920,1080);
  vec2 center = vec2(0.5);            
  uv -= center;
  float scale = 1.05;
  uv /= scale;
  float angle = radians(.8);
  mat2 rotation = mat2(
    cos(angle), -sin(angle),
    sin(angle),  cos(angle)
  );
  uv = rotation * uv;
  uv += center;
  prevColor = texture(prevBuffer, uv*vec2(1920,1080));
  }
  
  vec4 currentColor = texture(nextBuffer, fragCoord);

  vec4 result = prevColor * 0.98 + currentColor * 0.2;
  fragColor = clamp(result, 0.0, .95);
}
