

uniform sampler2D textureDiffuse;
varying vec2 uv_var;
void main()
{
	 gl_FragColor = texture2D(textureDiffuse,uv_var);
}