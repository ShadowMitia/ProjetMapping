#version 120

varying vec3 posLayer;
varying vec2 V;
varying vec2 div;
varying vec2 posFace;

uniform sampler2DRect u_texture;

//uniform float var;

uniform int mode;
uniform mat3 matrixX;
uniform mat3 matrixY;
uniform mat3 matrixR;



float mod40(float x){
    return x - floor(x * (1.0 / 160.0)) * 160.0;
}

void main(void)
{
    //pos = gl_Vertex.xyz;
    //gl_Position = ftransform();
    
    vec4 pos = gl_ModelViewProjectionMatrix * gl_Vertex ;
    posFace = gl_Vertex.xy;
    div = vec2(gl_Vertex.x/160.0,gl_Vertex.y/160.0);
    int iV = int(floor(div.x)) ;
    int jV = int(floor(div.y)) ;
    vec2 v = vec2(iV, jV);
    float  x = matrixX[iV][jV] + mod40(gl_Vertex.x);
    float  y = matrixY[iV][jV];// + mod40(gl_Vertex.y);
    x = gl_Vertex.x;
    posLayer = vec3(x,y,0.0);
    //posLayer = vec3(10.0,10.0,0.0);
    //gl_Position = gl_ModelViewProjectionMatrix * vec4(posLayer.xy,0.0,0.0);

    //gl_Position = vec4(posLayer.xy,pos.zw);
    gl_Position = gl_ModelViewProjectionMatrix * vec4(gl_Vertex.xy + vec2(x,0),gl_Vertex.zw) ;

}