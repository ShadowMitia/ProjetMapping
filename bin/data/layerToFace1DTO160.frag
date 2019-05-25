#version 120

varying vec3 pos;

//uniform values
uniform sampler2DRect u_texture;

uniform mat3 matrixX;
uniform mat3 matrixR;




//alpha threshold for our occlusion map
float mod40(float x){
    return x - floor(x * (1.0 / 160.0)) * 160.0;
}

void main(void) {

    vec2 div;
    div = vec2(pos.x/160.0,pos.y/160.0);
    int i = int(floor(div.x)) ;
    int j = int(floor(div.y)) ;
    vec4 tot;
    
    if (matrixR[i][j] == 0.0) {
         tot = texture2DRect(u_texture,vec2(matrixX[i][j]*160 + mod40(pos.x), mod40(pos.y)));
        //tot = vec4(1.0, 0.0 , 0.0, 1.0);
    }
    if (matrixR[i][j]== 90.0) {
        tot = texture2DRect(u_texture,vec2( matrixX[i][j]*160 + 160.0 - mod40(pos.y), mod40(pos.x)));

    }
    if (matrixR[i][j]== 180.0) {
         tot = texture2DRect(u_texture,vec2(matrixX[i][j]*160 + mod40(pos.x), mod40(pos.y)));
    }
    if (matrixR[i][j]== 270.0) {
         tot = texture2DRect(u_texture,vec2(matrixX[i][j]*160 + mod40(pos.y),160.0 - mod40(pos.x)));
    }
    
    gl_FragColor = tot;
}