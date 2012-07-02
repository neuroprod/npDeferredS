//
//  Shader.fsh
//  displaylist
//
//  Created by Kris Temmerman on 16/09/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//




uniform sampler2D lambertTexture; 
uniform sampler2D pointLightTexture; 
uniform sampler2D colorTexture; 
uniform sampler2D normalTexture; 
uniform sampler2D depthTexture; 
uniform sampler2D shadowTexture1;

uniform mat4 perspectiveInvMatrix ;
uniform mat4 light1Matrix ;

varying vec2 uv_var;
varying vec3 lightDir_var;


void main()
{



    vec3 col = texture2D(colorTexture, uv_var).xyz;
    vec3 normal = texture2D(normalTexture, uv_var).xyz*2.0 -1.0;
    float depth = texture2D(depthTexture, uv_var).x;
   vec3 pLight = texture2D(pointLightTexture, uv_var).xyz;
	
	vec3 pos =vec3(0.0,0.0,0.0);
	pos.xy = uv_var *2.0 -1.0;
	pos.z=depth;
    vec4 worldPos = perspectiveInvMatrix* vec4(pos,1.0);
  vec4 worldTest = worldPos;
 
	 worldPos.xyz/=worldPos.w;

	// dropSchadow 
	vec4 lightWorld =light1Matrix*worldTest;
	lightWorld.xyz/=lightWorld.w;
	lightWorld *=0.5;
	lightWorld +=0.5;
	//lightWorld.y  =1.0 - lightWorld.y;
	//lightWorld.x  =1.0 - lightWorld.x;
		float lightDepth = texture2D( shadowTexture1,lightWorld.xy).x;

	float zLight =lightWorld.z;
	float lambert = dot(normal,-lightDir_var)*0.5+0.5;
	if(lightDepth> zLight)
	
	{
	//lambert *=0.5;
	
	}
	

	





	//float lambert = dot(normal,-lightDir_var)*0.5+0.5;
	vec3 globalLight = texture2D(lambertTexture,vec2( lambert,0.1)).xyz;


	vec3 reflectVec = normalize(reflect( lightDir_var,normal));
	vec3 eyeVecNormal = normalize(- worldPos.xyz);
	float specular =pow(max(dot(eyeVecNormal,reflectVec),0.0),8.0)*0.15;

	col *=globalLight+pLight;

   gl_FragColor  =vec4(col+specular,1.0);

	//gl_FragColor =vec4(lightDepth ,zLight,zLight ,1.0);
	
	

	//gl_FragColor *=vec4( texture2D(shadowTexture1, uv_var).xyz,1.0)*0.5+0.5;
	//gl_FragColor  =vec4(pLight ,1.0);
	//gl_FragColor  = vec4(normal*0.5+0.5,1.0);
	//gl_FragColor  = vec4(normal,1.0);
	//gl_FragColor  = vec4( pos,1.0);
}