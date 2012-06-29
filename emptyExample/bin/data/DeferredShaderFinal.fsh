//
//  Shader.fsh
//  displaylist
//
//  Created by Kris Temmerman on 16/09/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//


varying vec2 uv_var;

uniform sampler2D pointLightTexture; 
uniform sampler2D colorTexture; 
uniform sampler2D normalTexture; 
uniform sampler2D depthTexture; 

uniform mat4 perspectiveInvMatrix ;

varying vec3 lightDir_var;


void main()
{
    vec3 col = texture2D(colorTexture, uv_var).xyz;
    vec3 normal = texture2D(normalTexture, uv_var).xyz*2.0 -1.0;
    float depth = texture2D(depthTexture, uv_var).x;
    vec3 pLight = texture2D(pointLightTexture, uv_var).xyz;
	
	
	vec3 pos =vec3(0.0,0.0,0.0);
	pos.xy = uv_var *2.0 -1.0;
	pos.z =-depth;
    vec4 worldPos = perspectiveInvMatrix* vec4(pos,1.0);
    worldPos.xyz/=worldPos.w;
	


	float lambert = dot(normal,-lightDir_var)*0.5+0.5;
	vec3 globalLight = vec3(1.0,1.0,1.0)*lambert;


	vec3 reflectVec = normalize(reflect( lightDir_var,normal));
	vec3 eyeVecNormal = normalize(- worldPos.xyz);
	float specular =pow(max(dot(eyeVecNormal,reflectVec),0.0),4.0)*0.1;

	col *=pLight+lambert;

    gl_FragColor  =vec4(col+specular,1.0);
	//gl_FragColor  =vec4(pLight ,1.0);
	//gl_FragColor  = vec4(normal*0.5+0.5,1.0);
	//gl_FragColor  = vec4(normal,1.0);
	//gl_FragColor  = vec4( pos,1.0);
}