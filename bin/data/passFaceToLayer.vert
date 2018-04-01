#version 120

varying vec2 posLayer;
varying vec2 posFace;
varying vec4 vColor;
uniform sampler2DRect u_texture;

//uniform float var;

uniform int mode;
uniform vec3 posAng;
uniform int X;
uniform float Y;


void main(void)
{
    //pos = gl_Vertex.xyz;
    //gl_Position = ftransform();
    
    vec4 pos = gl_ModelViewProjectionMatrix * gl_Vertex ;
    if (posAng.z == 0.0) {
        posFace =  vec2(gl_Vertex.x + 320.0*X, gl_Vertex.y + 320.0*Y );//gl_Vertex.xy;
        //vColor = vec4(0.0,0.0,1.0,1.0);
    }
    if (posAng.z == 90.0) {
        posFace =  vec2(gl_Vertex.y + 320.0*X, 320 - gl_Vertex.x + 320.0*Y );//gl_Vertex.xy;
        //vColor = vec4(0.0,1.0,1.0,1.0);
    }
    if (posAng.z == 180.0) {
        posFace =  vec2(320 - gl_Vertex.x + 320.0*X, 320 - gl_Vertex.y + 320.0*Y );//gl_Vertex.xy;
        //vColor = vec4(0.0,1.0,1.0,1.0);
    }
    if (posAng.z == 270.0) {
        posFace =  vec2( 320 - gl_Vertex.y + 320.0*X, gl_Vertex.x + 320.0*Y );//gl_Vertex.xy;
        //vColor = vec4(0.0,1.0,1.0,1.0);
    }
    
    posLayer = gl_Vertex.xy + vec2(posAng.x,posAng.y);


    //gl_Position = vec4(posLayer.xy,pos.zw);
    gl_Position = gl_ModelViewProjectionMatrix * vec4(posLayer,gl_Vertex.zw) ;

}