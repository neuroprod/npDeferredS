
varying vec3 normal_var;
varying vec2 uv_var;
uniform sampler2D vegMapTexture;
uniform sampler2D grassTexture;
uniform sampler2D dirtTexture;
uniform sampler2D forestTexture;

void main()
{
	vec3 vegMap = normalize(  texture2D(vegMapTexture,uv_var).xyz);
	vec3 color = texture2D(grassTexture,uv_var *100.0).xyz *vegMap.x;
	color += texture2D(forestTexture,uv_var *100.0).xyz*vegMap.y;
	color += texture2D(dirtTexture,uv_var *100.0).xyz *vegMap.z;


    gl_FragData[0] =  vec4( color,1.0) ;
	
	gl_FragData[1]  = vec4(normal_var.x*0.5+0.5,normal_var.y*0.5+0.5,normal_var.z*0.5+0.5,1.0);
   
}