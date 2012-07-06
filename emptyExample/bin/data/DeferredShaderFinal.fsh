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
uniform sampler2D shadowTexture1;
uniform sampler2D AONoiseTexture;

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
	

   ///SSAO
    vec3 pSphere[10] = vec3[](vec3(-0.010735935, 0.01647018, 0.0062425877),vec3(-0.06533369, 0.3647007, -0.13746321),vec3(-0.6539235, -0.016726388, -0.53000957),vec3(0.40958285, 0.0052428036, -0.5591124),vec3(-0.1465366, 0.09899267, 0.15571679),vec3(-0.44122112, -0.5458797, 0.04912532),vec3(0.03755566, -0.10961345, -0.33040273),vec3(0.019100213, 0.29652783, 0.066237666),vec3(0.8765323, 0.011236004, 0.28265962),vec3(0.29264435, -0.40794238, 0.15964167));
   vec3 fres = normalize(texture2D(AONoiseTexture,uv_var*vec2(15,8.4375)).xyz);
     float occluderDepth, depthDifference;
   vec4 occluderFragment;
   vec3 ray;
    float radD = rad/depthScreen;

     float bl = 0.0;
   for(int i=0; i<10;++i)
   {
      // get a vector (randomized inside of a sphere with radius 1.0) from a texture and reflect it
      ray =radD * reflect(pSphere[i],fres);
 
      // get the depth of the occluder fragment
      occluderFragment = texture2D(depthTexture,uv_var + (sign(dot(ray,normal.xyz) ))*ray.xy);
    // if depthDifference is negative = occluder is behind current fragment
      depthDifference = depthScreen-occluderFragment.r;
 
 
      bl += step(falloff,depthDifference);//*(1.0-smoothstep(falloff,strength,depthDifference));//*(1.0-dot(occluderFragment.xyz,normal.zyx))*(1.0-smoothstep(falloff,strength,depthDifference));
   }
   bl/=10.0;
  // bl-=0.5;
//	bl =min(bl,0.0); 
   bl =1.0-bl;

	 ///SSAO



















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
		
		for(float x=-0.5; x < 1.0; x+=0.5) 
		{
				for(float y=-0.5; y < 1.0; y+=0.5) 
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
	float fogFactor =pow(1.0- clamp((1.0 - depthScreen) / 0.001,0.0,1.0),2.0);


   gl_FragColor  =vec4(col+specular,1.0)*(1.0-fogFactor) +(fogFactor)*vec4(0.8,0.8,1.0,1.0) ;

	//gl_FragColor =vec4(lightDepth,0.0, texture2D(shadowTexture1, uv_var).x ,1.0);
	
	//gl_FragColor =vec4(lightDepth,zLight, zLight,1.0);
//gl_FragColor =vec4(texture2D(shadowTexture1, uv_var).xyz,1.0);
	//gl_FragColor =vec4( lightWorld.xy,0.0,1.0);
	//gl_FragColor  =vec4(pLight ,1.0);
	//gl_FragColor  = vec4(normal*0.5+0.5,1.0);
	//gl_FragColor  = vec4(normal,1.0);
	//gl_FragColor  = vec4( pos,1.0);}


   //gl_FragColor =vec4(bl,bl,bl,1.0);
 // gl_FragColor =vec4(fres,1.0);
 

	 }
}