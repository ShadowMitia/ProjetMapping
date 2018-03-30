#version 120

varying vec3 pos;

//uniform values
uniform sampler2DRect u_texture;




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
         tot = texture2DRect(u_texture,vec2(matrixX[i][j] + mod40(pos.x),matrixY[i][j] + mod40(pos.y)));
        //tot = vec4(1.0, 0.0 , 0.0, 1.0);
    }
    if (matrixR[i][j]== 90.0) {
        tot = texture2DRect(u_texture,vec2( matrixX[i][j] + 160.0 - mod40(pos.y), matrixY[i][j] + mod40(pos.x)));

    }
    if (matrixR[i][j]== 180.0) {
         tot = texture2DRect(u_texture,vec2(matrixX[i][j] + mod40(pos.x),matrixY[i][j] + mod40(pos.y)));
    }
    if (matrixR[i][j]== 270.0) {
         tot = texture2DRect(u_texture,vec2( matrixX[i][j] + mod40(pos.y), matrixY[i][j] + 160.0 - mod40(pos.x)));
    }
    
    /*if (tot.a == 1.0) {
        tot = vec4(1.0, 0.0 , 0.0, 1.0);
    }else{
        tot = vec4(0.0, 1.0 , 0.0, 1.0);
    }*/
    
    gl_FragColor = tot;
}