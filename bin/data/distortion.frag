#ifdef GL_ES
precision mediump float;
precision mediump int;
#endif

#define AMPLITUDE 0.2
#define SPEED 0.05

varying vec2 tc;
varying vec4 color;

uniform sampler2D srcTex;
uniform sampler2D noiseTex;
uniform vec2 u_resolution;
uniform float u_time;
varying vec4 vertTexCoord;

vec4 rgbShift( in vec2 p , in vec4 shift) {
    shift *= 2.0*shift.w - 1.0;
    vec2 rs = vec2(shift.x,-shift.y);
    vec2 gs = vec2(shift.y,-shift.z);
    vec2 bs = vec2(shift.z,-shift.x);
    
    float r = texture2D(srcTex, p+rs, 0.0).x;
    float g = texture2D(srcTex, p+gs, 0.0).y;
    float b = texture2D(srcTex, p+bs, 0.0).z;
    
    return vec4(r,g,b,1.0);
}

vec4 vec4pow( in vec4 v, in float p ) {
    // Don't touch alpha (w), we use it to choose the direction of the shift
    // and we don't want it to go in one direction more often than the other
    return vec4(pow(v.x,p),pow(v.y,p),pow(v.z,p),v.w); 
}

vec4 noise( in vec2 p ) {
    return texture2D(noiseTex, p, 0.0);
}


void main()
{
     vec2 p = gl_FragCoord.xy / u_resolution;
     // Can use tc in place of p here
     vec4 tex = texture2D(srcTex, tc);
     vec4 c = vec4(0.0,0.0,0.0,1.0);

     // Elevating shift values to some high power (between 8 and 16 looks good)
     // helps make the stuttering look more sudden
     vec4 shift = vec4pow(noise(vec2(SPEED*u_time,2.0*SPEED*u_time/25.0 )),6.0)
               *vec4(AMPLITUDE,AMPLITUDE,AMPLITUDE,1.0);

     c += rgbShift(p, shift);

     gl_FragColor = c;
}