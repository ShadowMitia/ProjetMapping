varying vec2 vTexCoord0;
varying vec2 vTexCoord1;
varying vec4 vColor;

uniform mat3 matrixX;
uniform mat3 matrixY;
uniform mat3 matrixR;

float mod40(float x){
    return x - floor(x * (1.0 / 160.0)) * 160.0;
}

void main(void) {
    
    float i = mod40(gl_Vertex.x);
    float j = mod40(gl_Vertex.y);
    if (matrixR[i][j]== 0.0) {
        break;
    }
    
    vColor = gl_Color;
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
    vTexCoord0 = gl_MultiTexCoord0.st;
    vTexCoord1 = gl_MultiTexCoord0.st;
}