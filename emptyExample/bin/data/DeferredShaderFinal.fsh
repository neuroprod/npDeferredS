//
//  Shader.fsh
//  displaylist
//
//  Created by Kris Temmerman on 16/09/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//
#version 120

const float strength = 0.90;

const float falloff = 0.0002;
const float rad = 0.01;
//#define SAMPLES 10 // 10 is good
const float invSamples = -1.38/10.0;


uniform sampler2D lambertTexture; 
uniform sampler2D pointLightTexture; 
uniform sampler2D colorTexture; 
uniform sampler2D normalTexture; 
uniform sampler2D depthTexture; 
uniform sampler2D shadowTexture;


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
		vec3 normal =normalize( texture2D(normalTexture, uv_var).xyz*2.0 -1.0);
		vec3 pLight = texture2D(pointLightTexture, uv_var).xyz;
		//float shadow = texture2D( shadowTexture,uv_var).x;
		float shadow =0;
		for(float x=-2; x < 3.0; x++) 
		{
					for(float y=-2; y < 3.0; y++) 
					{
						
							 shadow+= texture2D( shadowTexture,uv_var +vec2(x*0.00082, y*0.00138)).x;
					
						
					}
		}
		shadow/=25.0;
		vec3 pos =vec3(0.0,0.0,0.0);
		pos.xy = uv_var *2.0 -1.0;
		pos.z=depth;
		vec4 worldPos = perspectiveInvMatrix* vec4(pos,1.0);
		worldPos.xyz/=worldPos.w;
	
	
	 
	
	
		vec3 lightDir =normalize(lightDir_var);
		float lambert =  dot(normal,-lightDir)*0.5+0.5  ;
		vec3 globalLight = texture2D(lambertTexture,vec2(lambert *shadow ,time*0.9)).xyz;


		vec3 reflectVec = normalize(reflect( lightDir,normal));
		vec3 eyeVecNormal = normalize(- worldPos.xyz);
		float specular = pow(max(dot(eyeVecNormal,reflectVec),0.0),8.0)*0.1 ;
		col *=globalLight+(pLight*time);


		//fogFactor = (end - z) / (end - start) 
		float fogFactor =pow(1.0- clamp((1.0 - depthScreen) / 0.001,0.0,1.0),2.0);


	   gl_FragColor  =vec4(col+specular,1.0)*(1.0-fogFactor) +(fogFactor)*vec4(0.8,0.8,1.0,1.0)*(1.0-time*0.8 );

		//gl_FragColor =vec4(texture2D(shadowTexture, uv_var).xyz ,1.0);
		//gl_FragColor =vec4(shadow*lambert,shadow*lambert,shadow*lambert,1.0);
		//gl_FragColor =vec4(col ,1.0);
	// gl_FragColor  *=0.9;
	//gl_FragColor +=vec4(texture2D(colorTexture, uv_var).xyz,1.0)*0.1;
		//gl_FragColor =vec4( lightWorld.xy,0.0,1.0);
		//gl_FragColor  =vec4(pLight ,1.0);
		//gl_FragColor  = vec4(normal*0.5+0.5,1.0);
		//gl_FragColor  = vec4(normal,1.0);
		//gl_FragColor  = vec4( pos,1.0);}


		//gl_FragColor =vec4(bl,bl,bl,1.0);
		// gl_FragColor =vec4(fres,1.0);
 

	 }
}