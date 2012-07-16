

uniform sampler2D texture;
varying vec2 uv_var;

void main()
{

   // gl_FragData[0]  = vec4(uv_var,1.0,1.0);
    gl_FragData[0] = texture2D(texture,uv_var);
}