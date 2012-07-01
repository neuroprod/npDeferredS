
varying vec3 normal_var;
varying vec2 uv_var;
uniform sampler2D textureNormal;
uniform sampler2D textureDiffuse;
varying vec3 tangent_var;
varying vec3 bitangent_var;

void main()
{
	vec3 ts_normal= texture2D(textureNormal,uv_var).xyz; 
	vec3 ws_normal = tangent_var * ts_normal.x + bitangent_var* ts_normal.y + normal_var * ts_normal.z;
    gl_FragData[1]  = vec4(ws_normal,1.0);
    gl_FragData[0] = texture2D(textureDiffuse,uv_var); 
}