#version 120
varying vec3 pos;

//uniform values
uniform sampler2DRect u_texture;

uniform mat3 matrixX;
uniform mat3 matrixY;


//alpha threshold for our occlusion map

float mod40(float x){
    return x - floor(x * (1.0 / 160.0)) * 160.0;
}

void main(void) {
    vec4 tot = vec4(0.0,0.0,0.0,0.0);
    //int i = 2;
    //int j = 1;
    
    for (int i = 0; i<3; ++i) {
        for (int j = 0 ; j<3; ++j) {
            if (pos.x > matrixX[i][j] && pos.x < matrixX[i][j] + 160.0 && pos.y > matrixY[i][j] && pos.y < matrixY[i][j] + 160.0) {
                float x = matrixX[i][j] - pos.x;
                float y = matrixY[i][j] - pos.y;
                x = mod40(x);
                y = mod40(y);
                tot = texture2DRect(u_texture,vec2(160.0*(i+1) - x,160.0*(j+1) - y));
            }
        }
        
    }
    
    gl_FragColor = tot;
    
}