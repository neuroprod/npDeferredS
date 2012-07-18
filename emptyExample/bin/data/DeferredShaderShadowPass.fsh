//
//  Shader.fsh
//  displaylist
//
//  Created by Kris Temmerman on 16/09/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//
#version 120

const float strength = 0.09;
const float offsetAO = 30.0;
const float falloff = 0.00001;
const float rad = 0.01;



uniform sampler2D normalTexture; 
uniform sampler2D depthTexture; 
uniform sampler2D AONoiseTexture;


uniform sampler2D shadowTexture1;
uniform sampler2D shadowTexture2;
uniform sampler2D shadowTexture3;

uniform mat4 perspectiveInvMatrix ;

uniform mat4 light1Matrix ;
uniform mat4 light2Matrix ;
uniform mat4 light3Matrix ;

varying vec2 uv_var;



void main()
{

	float depthScreen = texture2D(depthTexture, uv_var).x;
		
	 if (depthScreen==1.0)
	 {  
		 gl_FragColor =vec4(1.0,1.0,1.0,1.0);
	 }
	 else
	 {
		vec3 normal = texture2D(normalTexture, uv_var).xyz*2.0 -1.0;


		float depth = depthScreen*2.0-1.0;
		vec3 pos =vec3(0.0,0.0,0.0);
		pos.xy = uv_var *2.0 -1.0;
		pos.z=depth;
		vec4 worldPos = perspectiveInvMatrix* vec4(pos,1.0);
		//worldPos.xyz/=worldPos.w;
	
	
		//DROPSHADOW
		float shadowTerm =1.0;
		//MAP 1
		if (depth<0.93)
		{
	
			vec4 lightWorld =light1Matrix* worldPos;
	
			lightWorld.xyz/=lightWorld.w;
	
			lightWorld /=2.0;
			lightWorld +=0.5;
			float zLight =lightWorld.z;
			vec2 offset =vec2(0.000244,0.000244);
		
			for(float x=-1.0; x < 2.0; x+=1.0) 
			{
					for(float y=-1.0; y < 2.0; y+=2.0) 
					{
						float lightDepth = texture2D( shadowTexture1,lightWorld.xy+vec2(offset.x *x,offset.y *y)).x;
						if (zLight >lightDepth)
						{
							shadowTerm-=0.10;
					
						}
					}
	
	
			}

		}




		//MAP 2
		else if (depth<0.985)
		{
	
			vec4 lightWorld =light2Matrix* worldPos;
	
			lightWorld.xyz/=lightWorld.w;
	
			lightWorld /=2.0;
			lightWorld +=0.5;
			float zLight =lightWorld.z;
			vec2 offset =vec2(0.000244,0.000244);
		for(float x=-1.0; x < 2.0; x+=1.0) 
			{
					for(float y=-1.0; y < 2.0; y+=2.0) 
					{
						float lightDepth = texture2D( shadowTexture2,lightWorld.xy+vec2(offset.x *x,offset.y *y)).x;
						if (zLight >lightDepth)
						{
							shadowTerm-=0.10;
					
						}
					}
	
	
			}

		}else
		{
		
		vec4 lightWorld =light3Matrix* worldPos;
	
			lightWorld.xyz/=lightWorld.w;
	
			lightWorld /=2.0;
			lightWorld +=0.5;
			float zLight =lightWorld.z;
			vec2 offset =vec2(0.000244,0.000244);
		
			for(float x=-1.0; x < 2.0; x+=1.0) 
			{
					for(float y=-1.0; y < 2.0; y+=2.0) 
					{
						float lightDepth = texture2D( shadowTexture3,lightWorld.xy+vec2(offset.x *x,offset.y *y)).x;
						if (zLight >lightDepth)
						{
							shadowTerm-=0.10;
					
						}
					}
	
	
			}
		}





















		vec3 pSphere[10] = vec3[](vec3(-0.010735935, 0.01647018, 0.0062425877),vec3(-0.06533369, 0.3647007, -0.13746321),vec3(-0.6539235, -0.016726388, -0.53000957),vec3(0.40958285, 0.0052428036, -0.5591124),vec3(-0.1465366, 0.09899267, 0.15571679),vec3(-0.44122112, -0.5458797, 0.04912532),vec3(0.03755566, -0.10961345, -0.33040273),vec3(0.019100213, 0.29652783, 0.066237666),vec3(0.8765323, 0.011236004, 0.28265962),vec3(0.29264435, -0.40794238, 0.15964167));
 
		vec3 fres = normalize(texture2D(AONoiseTexture,uv_var*offsetAO).xyz);
		float occluderDepth, depthDifference;
		vec4 occluderNormal;
		vec3 ray;
		vec2 uv_Sample;
		float radD = rad*depthScreen;

		float bl = 0.0;
		for(int i=0; i<10;++i)
		{
      // get a vector (randomized inside of a sphere with radius 1.0) from a texture and reflect it
			ray =radD * reflect(pSphere[i],fres);
 
			uv_Sample  =uv_var + (sign(dot(ray,normal.xyz) ))*ray.xy;
			occluderDepth = texture2D(depthTexture,uv_Sample).r;
			occluderNormal = texture2D(normalTexture,uv_Sample);
			depthDifference = depthScreen-occluderDepth;
 
 
			bl += step(falloff,depthDifference)*(1.0-dot(occluderNormal.xyz,normal))*(1.0-smoothstep(falloff,strength,depthDifference));
		}
		



		 shadowTerm*=clamp(1-(bl/10.0),0.0,1.0);









		gl_FragColor  =vec4(shadowTerm,shadowTerm,shadowTerm,1.0);
	 }// end background if


		//gl_FragColor =vec4(texture2D(shadowTexture1, uv_var).xyz ,1.0);
}