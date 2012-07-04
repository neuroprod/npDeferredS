

uniform sampler2D textureDiffuse;
varying vec2 uv_var;
void main()
{
	 gl_FragData[0]  = texture2D(textureDiffuse,uv_var);
}