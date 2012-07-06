
varying vec2 uv_var;

varying vec3 color_var;
uniform sampler2D textureNoise;
void main()
{
	vec3 noise =  texture2D(textureNoise,uv_var*2.0).xyz-0.5;
   gl_FragColor =vec4(noise+color_var,1.0) ;
}