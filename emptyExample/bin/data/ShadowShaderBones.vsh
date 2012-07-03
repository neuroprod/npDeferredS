


attribute vec4 position;

attribute vec2 ids;
attribute vec2 weights;




uniform mat4 objectMatrix ;
uniform mat4 worldMatrix ;
uniform mat4 lightProjectionMatrix ;

uniform mat4 boneMatrixList[22];
uniform mat4 boneNormalMatrixList[22];





void main()
{




	 vec4 boneSpace =  (boneMatrixList[int(ids.x)] * position *weights.x) +(boneMatrixList[int(ids.y)] * position *weights.y)  ;

    vec4 localSpace = objectMatrix * boneSpace;
    vec4 worldSpace = worldMatrix *localSpace;
    gl_Position = lightProjectionMatrix  *worldSpace;

    





}