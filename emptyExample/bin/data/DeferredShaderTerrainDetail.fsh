
varying vec4 normal_var;
varying vec2 uv_var;



void main()
{
	vec3 normal =normalize(normal_var.xyz) ;
	
    gl_FragData[0] = vec4(uv_var,0.0,1.0); // texture2D(vegMapTexture,uv_var);
	
	gl_FragData[1]  = vec4(normal.x*0.5+0.5,normal.y*0.5+0.5,normal.z*0.5+0.5,1.0);
   
}