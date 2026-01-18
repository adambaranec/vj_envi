#version 460

precision mediump float;
in vec2 fragCoord;
uniform vec2 resolution;
uniform sampler2DRect tex;
uniform float time, aspect, amp;
out vec4 fragColor;

float _luminance(vec3 rgb){
      const vec3 W = vec3(0.2125, 0.7154, 0.0721);
      return dot(rgb, W);
    }

   //	Simplex 3D Noise
    //	by Ian McEwan, Ashima Arts
    vec4 permute(vec4 x){return mod(((x*34.0)+1.0)*x, 289.0);}
  vec4 taylorInvSqrt(vec4 r){return 1.79284291400159 - 0.85373472095314 * r;}

  float _noise(vec3 v){
    const vec2  C = vec2(1.0/6.0, 1.0/3.0) ;
    const vec4  D = vec4(0.0, 0.5, 1.0, 2.0);

  // First corner
    vec3 i  = floor(v + dot(v, C.yyy) );
    vec3 x0 =   v - i + dot(i, C.xxx) ;

  // Other corners
    vec3 g = step(x0.yzx, x0.xyz);
    vec3 l = 1.0 - g;
    vec3 i1 = min( g.xyz, l.zxy );
    vec3 i2 = max( g.xyz, l.zxy );

    //  x0 = x0 - 0. + 0.0 * C
    vec3 x1 = x0 - i1 + 1.0 * C.xxx;
    vec3 x2 = x0 - i2 + 2.0 * C.xxx;
    vec3 x3 = x0 - 1. + 3.0 * C.xxx;

  // Permutations
    i = mod(i, 289.0 );
    vec4 p = permute( permute( permute(
               i.z + vec4(0.0, i1.z, i2.z, 1.0 ))
             + i.y + vec4(0.0, i1.y, i2.y, 1.0 ))
             + i.x + vec4(0.0, i1.x, i2.x, 1.0 ));

  // Gradients
  // ( N*N points uniformly over a square, mapped onto an octahedron.)
    float n_ = 1.0/7.0; // N=7
    vec3  ns = n_ * D.wyz - D.xzx;

    vec4 j = p - 49.0 * floor(p * ns.z *ns.z);  //  mod(p,N*N)

    vec4 x_ = floor(j * ns.z);
    vec4 y_ = floor(j - 7.0 * x_ );    // mod(j,N)

    vec4 x = x_ *ns.x + ns.yyyy;
    vec4 y = y_ *ns.x + ns.yyyy;
    vec4 h = 1.0 - abs(x) - abs(y);

    vec4 b0 = vec4( x.xy, y.xy );
    vec4 b1 = vec4( x.zw, y.zw );

    vec4 s0 = floor(b0)*2.0 + 1.0;
    vec4 s1 = floor(b1)*2.0 + 1.0;
    vec4 sh = -step(h, vec4(0.0));

    vec4 a0 = b0.xzyw + s0.xzyw*sh.xxyy ;
    vec4 a1 = b1.xzyw + s1.xzyw*sh.zzww ;

    vec3 p0 = vec3(a0.xy,h.x);
    vec3 p1 = vec3(a0.zw,h.y);
    vec3 p2 = vec3(a1.xy,h.z);
    vec3 p3 = vec3(a1.zw,h.w);

  //Normalise gradients
    vec4 norm = taylorInvSqrt(vec4(dot(p0,p0), dot(p1,p1), dot(p2, p2), dot(p3,p3)));
    p0 *= norm.x;
    p1 *= norm.y;
    p2 *= norm.z;
    p3 *= norm.w;

  // Mix final noise value
    vec4 m = max(0.6 - vec4(dot(x0,x0), dot(x1,x1), dot(x2,x2), dot(x3,x3)), 0.0);
    m = m * m;
    return 42.0 * dot( m*m, vec4( dot(p0,x0), dot(p1,x1),
                                  dot(p2,x2), dot(p3,x3) ) );
  }

vec4 hsv2rgba(float hue, float saturation, float value)
{
    vec3 c = vec3(hue, saturation, value);
    vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
    vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
    vec3 result = c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
    return vec4(vec3(result),1.);
}

  vec4 noise(vec2 _st, float scale, float offset) {
         return vec4(vec3(_noise(vec3(_st*scale, offset*time))), 1.0);
  }

vec4 blend(vec4 _c0, vec4 _c1, float amount){
return _c0*(1.0-amount)+_c1*amount;
}

vec4 add(vec4 _c0, vec4 _c1, float amount){
return (_c0+_c1)*amount + _c0*(1.0-amount);
}

vec4 mask(vec4 _c0, vec4 _c1) {
         float a = _luminance(_c1.rgb);
  return vec4(_c0.rgb*a, a*_c0.a);
}

vec2 repeat(vec2 _st, float repeatX, float repeatY, float offsetX, float offsetY) {
         vec2 st = _st * vec2(repeatX, repeatY);
   st.x += step(1., mod(st.y,2.0)) * offsetX;
   st.y += step(1., mod(st.x,2.0)) * offsetY;
   return fract(st);
  }

mat2 rot(float angle){
return mat2(cos(angle),-sin(angle),sin(angle),cos(angle));
}

vec2 mid0(vec2 st){
vec2 uv = st* 2 - 1;
uv.x *= aspect;
return uv;
}

vec2 mid0rot(vec2 st,float speed){
vec2 uv = mid0(st);
return uv * rot(time*-speed);
}

vec2 mid0rep(vec2 st,float x,float y){
st = repeat(st,x,y,0,0);
vec2 uv = mid0(st);
return uv;
}

vec2 mid0rotRep(vec2 st,float speed,float x,float y){
st = repeat(st,x,y,0,0);
vec2 uv = mid0(st);
uv *= rot(time*-speed);
return uv;
}

vec2 mid0scroll(vec2 st,float speedX, float speedY){
st += vec2(time*speedX,time*speedY);
st = fract(st);
vec2 uv = st* 2 - 1;
uv.x *= aspect;
return uv;
}

vec2 mid0scrollRep(vec2 st, float speedX, float speedY, float repX, float repY){
st += vec2(time*speedX,time*speedY);
st = repeat(st,repX,repY,0,0);
vec2 uv = st* 2 - 1;
uv.x *= aspect;
return uv;
}

vec2 mid0trans(vec2 st,float x,float y){
st += vec2(x,y);
return mid0(st);
}

float a_polar(vec2 st){
vec2 uv = mid0(st);
return atan(uv.x,uv.y)+3.1416;
}


vec4 sphere(vec2 _st, float magnitude){
return vec4(vec3( exp(1.-distance(_st,vec2(0.))/.4 / magnitude) ),1.);
}

float circle(vec2 st, float radius, float ampMulti){
return 1.-step(radius+(amp*ampMulti), length(st-vec2(0))  );
}

float square(vec2 st, float width, float ampMulti){
vec2 tl = step(vec2(0)-vec2(width+(amp*ampMulti)),st);
vec2 br = 1.-step(vec2(width+(amp*ampMulti)),st);
return tl.x*tl.y*br.x*br.y;
}

float polygon(vec2 st, int sides, float radius, float ampMulti){
float a = atan(st.x,st.y)+3.1416;
float r = (2.*3.1416)/float(sides);
float d = cos(floor(.5+a/r)*r-a)*length(st);
return 1.-step(radius+(amp*ampMulti),d);
}

float lineY(vec2 st, float centre, float thickness, float ampMulti){
return 1.-step(thickness+(amp*ampMulti),abs(st.x-centre));
}

float lineX(vec2 st, float centre, float thickness, float ampMulti){
return 1.-step(thickness+(amp*ampMulti),abs(st.y-centre));
}

float lineY_s(vec2 st, float centre, float innerThick, float outerThick, float ampMulti){
return 1.-smoothstep(innerThick+(amp*ampMulti),outerThick+(amp*ampMulti),abs(st.x-centre));
}

float lineX_s(vec2 st, float centre, float innerThick, float outerThick, float ampMulti){
return 1.-smoothstep(innerThick+(amp*ampMulti),outerThick+(amp*ampMulti),abs(st.y-centre));
}

float circle_s(vec2 st, float holeRadius, float radius, float ampMulti){
return circle(st,radius,(amp*ampMulti)) - circle(st,holeRadius,(amp*ampMulti));
}

float square_s(vec2 st, float holeRadius, float radius, float ampMulti){
return square(st,radius,(amp*ampMulti)) - square(st,holeRadius,(amp*ampMulti));
}

float polygon_s(vec2 st, int sides, float holeRadius, float radius,float ampMulti){
return polygon(st,sides,radius,(amp*ampMulti)) - polygon(st,sides,holeRadius,(amp*ampMulti));
}

float circle_b(vec2 st, float innerRadius, float outerRadius,float ampMulti){
return 1.-smoothstep(innerRadius+(amp*ampMulti),outerRadius+(amp*ampMulti),length(st-vec2(0)));
}

float noise_f(vec2 st, float scale, float offset){
return _noise(vec3(st*scale, time*offset));
}

vec4 noise_hue(float n, float min, float max, float ampMulti){
return hsv2rgba(mix(min,max,n+(amp*ampMulti)),1,1);
}

vec4 osc(vec2 st,float density, float hue1, float hue2,float speed){
st.x += time*speed;
return hsv2rgba(mix(hue1,hue2,sin(st.x*density)),1,1);
}

vec4 b_w_osc(vec2 st, float density, float v1, float v2, float speed){
st.x += time*speed;
return hsv2rgba(0,0,mix(v1,v2,sin(st.x*density)));
}

vec4 addShape(vec4 fragColor, float hue, float saturation, float shape){
vec4 result = mix(fragColor,hsv2rgba(hue,saturation,shape),shape);
return result;
}

void layer(out vec4 fragColor, vec4 result){
fragColor = result;
}

vec2 circledUv(vec2 st,int which,int totalNumber,float distance,float speed){
return mid0(st)+vec2(sin(6.28/float(totalNumber)*float(which)+time*speed)*distance,cos(6.28/float(totalNumber)*float(which)+time*speed)*distance);
}


void main(){
vec2 st = fragCoord.xy/resolution.xy; 
fragColor = b_w_osc(st,10,.4,.9,.3);
fragColor = addShape(fragColor,.1,.9,square_s(mid0rotRep(st,.9,4,4),.3,.5,0));	
fragColor = addShape(fragColor,.75,1,circle_b(mid0scrollRep(st,.3,.2,6,6),.1,.3,1));
fragColor = addShape(fragColor,0,1,lineY(mid0rot(st,1),.0,.04,0));
}