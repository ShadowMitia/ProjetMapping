#version 120
varying vec3 pos;

//uniform values
uniform sampler2DRect u_texture;

uniform int mode;
uniform mat3 matrixX;
uniform mat3 matrixY;
uniform mat3 matrixR;

//alpha threshold for our occlusion map

float mod40(float x){
    return x - floor(x * (1.0 / 160.0)) * 160.0;
}

void main(void) {

    vec4 tot = vec4(0.0,0.0,0.0,0.0);
    for (int i = 0; i<3; ++i) {
        for (int j = 0 ; j<3; ++j) {
            if (pos.x > matrixX[i][j] && pos.x < matrixX[i][j] + 160.0 && pos.y > matrixY[i][j] && pos.y < matrixY[i][j] + 160.0) {
                
                if (matrixR[i][j]== 0.0) {
                    float x = matrixX[i][j] - pos.x;
                    float y = matrixY[i][j] - pos.y;
                    x = mod40(x);
                    y = mod40(y);
                    tot = texture2DRect(u_texture,vec2(160.0*(i+1) - x,160.0*(j+1) - y));
                    //tot = vec4(1.0,1.0,0.0,1.0);
                    break;
                }
                if (matrixR[i][j]== 90.0) {
                    float x = matrixX[i][j] - pos.x;
                    float y = matrixY[i][j] - pos.y;
                    x = mod40(x);
                    y = mod40(y);
                    tot = texture2DRect(u_texture,vec2(160.0*(i+1) - y,160.0*j+ x));
                    //tot = vec4(1.0,0.0,0.0,1.0);

                    break;
                }
                if (matrixR[i][j]== 180.0) {
                    float x = matrixX[i][j] - pos.x;
                    float y = matrixY[i][j] - pos.y;
                    x = mod40(x);
                    y = mod40(y);
                    tot = texture2DRect(u_texture,vec2(160.0*(i+1) - x,160.0*(j+1) - y));
                    //tot = vec4(1.0,1.0,0.0,1.0);

                    break;
                }
                if (matrixR[i][j]== 270.0) {
                    float x = matrixX[i][j] - pos.x;
                    float y = matrixY[i][j] - pos.y;
                    x = mod40(x);
                    y = mod40(y);
                    tot = texture2DRect(u_texture,vec2(160.0*i + y,160.0*j + x));
                    //tot = vec4(0.0,0.0,1.0,1.0);
                    break;
                }
                
                break;
            }
        }
    }
    
    gl_FragColor = tot;

    if (mode == 1) {
        gl_FragColor = vec4(max(tot.rgb + gl_Color.rgb,1.0),min(tot.a,gl_Color.a));
    }else{
       gl_FragColor = tot;
    }
    
    /*if (mode == 0) {
        gl_FragColor = tot;
    }
    else if (mode == 1) {
        gl_FragColor = vec4(max(tot.rgb + gl_Color.rgb,1.0),min(tot.a,gl_Color.a));
        //gl_FragColor = tot;
    }
    else{
        gl_FragColor = tot
    };*/
}
