



attribute vec4 position;



uniform mat4 objectMatrix ;

uniform mat4 lightProjectionMatrix ;





void main()
{

    vec4 localSpace = objectMatrix * position;
	//vec4 worldSpace   = worldMatrix*localSpace;
    gl_Position = lightProjectionMatrix *localSpace;

    






}