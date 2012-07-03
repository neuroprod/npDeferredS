
varying vec3 normal_var;
varying vec2 uv_var;
uniform sampler2D textureNormal;
uniform sampler2D textureDiffuse;
varying vec3 tangent_var;
varying vec3 bitangent_var;

void main()
{
	vec4 difColor = texture2D(textureDiffuse,uv_var);
	   gl_FragData[0] =difColor;


	vec3 ts_normal= texture2D(textureNormal,uv_var).xyz*2.0-1.0; 
	vec3 ws_normal = tangent_var * ts_normal.x + bitangent_var* ts_normal.y + normal_var * ts_normal.z;
    gl_FragData[1]  = vec4(ws_normal*0.5+0.5,difColor.a );
 
}