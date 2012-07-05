
varying vec3 normal_var;
varying vec2 uv_var;
uniform sampler2D vegMapTexture;


void main()
{

	
    gl_FragData[0] =   texture2D(vegMapTexture,uv_var);
	
	gl_FragData[1]  = vec4(normal_var.x*0.5+0.5,normal_var.y*0.5+0.5,normal_var.z*0.5+0.5,1.0);
   
}