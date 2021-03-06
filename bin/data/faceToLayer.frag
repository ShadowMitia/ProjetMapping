#version 120
varying vec3 pos;

//uniform values
uniform sampler2DRect u_texture;
uniform sampler2DRect u_texture_src;

uniform int mode;
uniform mat3 matrixX;
uniform mat3 matrixY;
uniform mat3 matrixR;

//alpha threshold for our occlusion map

float mod40(float x){
    return x - floor(x * (1.0 / 320.0)) * 320.0;
}

void main(void) {
    float contrast = 0.70;
    vec4 shadow = vec4(0.0,0.0,0.0,0.0);
    for (int i = 0; i<3; ++i) {
        for (int j = 0 ; j<3; ++j) {
            if (pos.x > matrixX[i][j] && pos.x < matrixX[i][j] + 320.0 && pos.y > matrixY[i][j] && pos.y < matrixY[i][j] + 320.0) {
                
                if (matrixR[i][j]== 0.0) {
                    float x = matrixX[i][j] - pos.x;
                    float y = matrixY[i][j] - pos.y;
                    x = mod40(x);
                    y = mod40(y);
                    shadow = texture2DRect(u_texture,vec2(320.0*(i+1) - x,320.0*(j+1) - y));
                    //shadow = vec4(1.0,1.0,0.0,1.0);
                    break;
                }
                if (matrixR[i][j]== 90.0) {
                    float x = matrixX[i][j] - pos.x;
                    float y = matrixY[i][j] - pos.y;
                    x = mod40(x);
                    y = mod40(y);
                    shadow = texture2DRect(u_texture,vec2(320.0*(i+1) - y,320.0*j+ x));
                    //shadow = vec4(1.0,0.0,0.0,1.0);

                    break;
                }
                if (matrixR[i][j]== 180.0) {
                    float x = matrixX[i][j] - pos.x;
                    float y = matrixY[i][j] - pos.y;
                    x = mod40(x);
                    y = mod40(y);
                    shadow = texture2DRect(u_texture,vec2(320.0*(i+1) - x,320.0*(j+1) - y));
                    //shadow = vec4(1.0,1.0,0.0,1.0);

                    break;
                }
                if (matrixR[i][j]== 270.0) {
                    float x = matrixX[i][j] - pos.x;
                    float y = matrixY[i][j] - pos.y;
                    x = mod40(x);
                    y = mod40(y);
                    shadow = texture2DRect(u_texture,vec2(320.0*i + y,320.0*(j+1) - x));
                    //shadow = vec4(0.0,0.0,1.0,1.0);
                    break;
                }
                
                break;
            }
        }
    }
    
    //gl_FragColor = shadow;
    vec4 src  =  texture2DRect(u_texture_src,pos.xy);
    
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
    

}
