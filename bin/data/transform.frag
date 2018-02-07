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

    vec2 div;
    div = vec2(pos.x/160.0,pos.y/160.0);
    int i = int(floor(div.x)) ;
    int j = int(floor(div.y)) ;
    vec4 tot = texture2DRect(u_texture,vec2(matrixX[i][j] + mod40(pos.x),matrixY[i][j] + mod40(pos.y)));
    gl_FragColor = tot;
}