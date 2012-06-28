


attribute vec4 position;
attribute vec4 normal;
attribute vec2 uv;
attribute vec2 ids;
attribute vec2 weights;




uniform mat4 objectMatrix ;
uniform mat4 normalMatrix ;
uniform mat4 worldMatrix ;
uniform mat4 boneMatrixList[22];
uniform mat4 boneNormalMatrixList[22];
uniform mat4 perspectiveMatrix ;


varying vec3 normal_var;
varying vec2 uv_var;


void main()
{




	 vec4 boneSpace =  (boneMatrixList[int(ids.x)] * position *weights.x) +(boneMatrixList[int(ids.y)] * position *weights.y)  ;

    vec4 localSpace = objectMatrix * boneSpace;
    vec4 worldSpace = worldMatrix *localSpace;
    gl_Position = perspectiveMatrix *worldSpace;

    
  vec4 normalB  =  (boneNormalMatrixList[int(ids.x)] *normal *weights.x) +(boneNormalMatrixList[int(ids.y)] * normal *weights.y)  ;
    vec4 normalL = normalMatrix*normalB ;
    normal_var = normalize(normalL.xyz); // normalWorldMatrix*
    uv_var =uv;





}