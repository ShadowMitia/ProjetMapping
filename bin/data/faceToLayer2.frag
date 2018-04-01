#version 120

varying vec2 posLayer;
varying vec2 posFace;
varying vec4 vColor;

//uniform values
uniform sampler2DRect u_texture;
uniform sampler2DRect u_texture_src;

uniform int mode;
uniform vec3 posAng;
uniform int X;
uniform float Y;

//alpha threshold for our occlusion map
float mod40(float x){
    return x - floor(x * (1.0 / 160.0)) * 160.0;
}

void main(void) {
    float contrast = 0.70;
    vec4 shadow = texture2DRect(u_texture,posFace.xy);

    vec4 src  =  texture2DRect(u_texture_src,posLayer.xy);
    
    if (mode == 0) {
        gl_FragColor = shadow;
        
    }
    if (mode == 1) {
        if (shadow.a != 0.0) {
            if (src.a != 0) {
                //shadow = vec4(vec3(0.0,0.0,0.0), min(min(shadow.a,src.a),0.9));
                shadow = vec4(max(shadow.r,src.r),max(shadow.g,src.g), max(shadow.b,src.b),min(min(shadow.a,src.a),contrast));

            }
            else{
                //shadow = vec4(vec3(0.0,0.0,0.0), min(shadow.a,0.9));
                shadow = vec4(shadow.rgb, min(shadow.a,contrast));

            }
        }
        else{
            //gl_FragColor = vec4(src);
            shadow = vec4(src);
        }
        
        if (shadow.a == 0.0) {
            shadow = vec4(vec3(0.0,0.0,0.0),contrast);
        }
        if (shadow.a == contrast) {
            shadow = vec4(vec3(0.0,0.0,0.0),contrast);
        }
        //gl_FragColor = vec4(src.rgb, min(shadow.a,src.a));
        gl_FragColor = shadow;
    }
    if (mode == 2) {
        if (shadow == vec4(1.0,1.0,1.0,1.0)) {
            gl_FragColor = vec4(0.0,1.0,1.0,1.0);
        }
        else{
            gl_FragColor = vec4(0.0,1.0,1.0,0.0);
        }
    }
    
    //gl_FragColor = vec4(0.0,0.0,1.0,1.0);
    //gl_FragColor = shadow;
    //gl_FragColor = vColor;

}
