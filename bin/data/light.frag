#ifdef GL_ES
#define LOWP lowp
precision mediump float;
#else
#define LOWP
#endif

#define PI 3.14

//inputs from vertex shader
varying vec2 vTexCoord0;
varying vec2 vTexCoord1;
varying LOWP vec4 vColor;

uniform vec2 lightLocation;
uniform vec3 lightColor;
uniform float u_radius;
uniform vec2        resolution;
uniform sampler2D   u_texturePlaform;
uniform sampler2D   u_textureObjet;
uniform sampler2D   u_objects_tex;

// ----------------------------------------------------------
//sample from the 1D distance map
float sample(vec2 coord, float r , sampler2D _texture) {
    return step(r, texture2D(_texture, coord).r);
}

// ----------------------------------------------------------
void main() {
    
    
    //rectangular to polar
    vec2 offset     = vec2(lightLocation.x-resolution.x/2.0, lightLocation.y-resolution.y/2.0);
    vec2 inputCoord = (vec2(gl_FragCoord.x-offset.x, resolution.y - (gl_FragCoord.y-offset.y))) / resolution;
    vec2 norm       = inputCoord * 2.0 - 1.0;
    float theta     = atan(norm.y, norm.x);
    float r         = length(norm);
    float coord     = (theta + PI) / (2.0*PI);
    float ombre;
    
    vec2 tc = vec2(coord, 0.0);
    
    float plaform = sample(tc, r, u_texturePlaform);
    float objet = sample(tc, r, u_textureObjet);
    
    if (plaform == 0.0) {
        ombre = 0.07;//0.7;
    }
    else{
        if (objet == 0.0) {
            ombre = 0.03;//0.3
        }
        else{
            ombre = 0.0;// 1.0
        }

    }
    
    float radius = u_radius;
    float bleed = 0.0;
    float linearizeFactor = 0.9;
    float distance = length(lightLocation - gl_FragCoord.xy);
    float attenuation = (radius - distance) * (bleed / pow(distance, 2.0) + linearizeFactor / radius);
    attenuation = clamp(1.0 - attenuation, 0.0, 1.0);
    
    
    float intensity = (10.0 / distance);
    
    if (attenuation == 1.0) {
        gl_FragColor = vec4(0.0,0.0,0.0,0.0);
    }
    else{
        gl_FragColor = vec4(0.0, 0.0, 0.0, attenuation + ombre);

    }
    



}




