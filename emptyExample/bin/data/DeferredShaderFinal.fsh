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
//uniform mat4 worldMatrixInv ;
uniform mat4 light1Matrix ;

uniform float time ;

varying vec2 uv_var;
varying vec3 lightDir_var;


void main()
{

	float depthScreen = texture2D(depthTexture, uv_var).x;
	
	 if (depthScreen==1.0)
	 {  
		 gl_FragColor = texture2D(colorTexture, uv_var);
	 }
	 else
	 {
		  float depth = depthScreen*2.0-1.0;

    vec3 col = texture2D(colorTexture, uv_var).xyz;
    vec3 normal = texture2D(normalTexture, uv_var).xyz*2.0 -1.0;
 
   vec3 pLight = texture2D(pointLightTexture, uv_var).xyz;
	
	vec3 pos =vec3(0.0,0.0,0.0);
	pos.xy = uv_var *2.0 -1.0;
	pos.z=depth;
    vec4 worldPos = perspectiveInvMatrix* vec4(pos,1.0);

	vec4 worldTest = worldPos ;
	 worldPos.xyz/=worldPos.w;
	
	
	 //DROPSHADOW
	 float shadowTerm =1.0;
	//MAP 1
	 if (depth<0.965)
	 {
	
		vec4 lightWorld =light1Matrix* worldTest;
	
		lightWorld.xyz/=lightWorld.w;
	
		lightWorld /=2.0;
		lightWorld +=0.5;
		float zLight =lightWorld.z;
		vec2 offset =vec2(0.000488,0.000488);
		
		for(float x=-1.0; x < 2.0; x+=1.0) 
		{
				for(float y=-1.0; y < 2.0; y+=1.0) 
				{
					float lightDepth = texture2D( shadowTexture1,lightWorld.xy+vec2(offset.x *x,offset.y *y)).x;
					if (zLight >lightDepth)
					{
						shadowTerm*=0.95;
					
					}
				}
	
	
		}

	}
	 //MAIN LIGHT





	float lambert = dot(normal,-lightDir_var)*0.5+0.5;
	vec3 globalLight = texture2D(lambertTexture,vec2( lambert *shadowTerm ,time)).xyz;


	vec3 reflectVec = normalize(reflect( lightDir_var,normal));
	vec3 eyeVecNormal = normalize(- worldPos.xyz);
	float specular =pow(max(dot(eyeVecNormal,reflectVec),0.0),8.0)*0.1;

	col *=globalLight+pLight;


		//fogFactor = (end - z) / (end - start) 
	float fogFactor =pow(1.0- clamp((1.0 - depthScreen) / 0.005,0.0,1.0),4.0);


   gl_FragColor  =vec4(col+specular,1.0)*(1.0-fogFactor) +(fogFactor)*vec4(0.8,0.8,1.0,1.0) ;

	//gl_FragColor =vec4(lightDepth,0.0, texture2D(shadowTexture1, uv_var).x ,1.0);
	
	//gl_FragColor =vec4(lightDepth,zLight, zLight,1.0);
	//gl_FragColor =vec4(texture2D(shadowTexture1, uv_var).xyz,1.0);
	//gl_FragColor =vec4( lightWorld.xy,0.0,1.0);
	//gl_FragColor  =vec4(pLight ,1.0);
	//gl_FragColor  = vec4(normal*0.5+0.5,1.0);
	//gl_FragColor  = vec4(normal,1.0);
	//gl_FragColor  = vec4( pos,1.0);}

	 }
}