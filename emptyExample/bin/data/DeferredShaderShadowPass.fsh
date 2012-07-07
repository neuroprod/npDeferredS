//
//  Shader.fsh
//  displaylist
//
//  Created by Kris Temmerman on 16/09/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//
#version 120




uniform sampler2D normalTexture; 
uniform sampler2D depthTexture; 
uniform sampler2D AONoiseTexture;


uniform sampler2D shadowTexture1;


uniform mat4 perspectiveInvMatrix ;

uniform mat4 light1Matrix ;



varying vec2 uv_var;



void main()
{

	float depthScreen = texture2D(depthTexture, uv_var).x;
		
	 //if (depthScreen==1.0)
	 //{  
	//	 gl_FragColor =vec4(1.0,1.0,1.0,1.0);
	 //}
	 //else
	 //{
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
		if (depth<0.965)
		{
	
			vec4 lightWorld =light1Matrix* worldPos;
	
			lightWorld.xyz/=lightWorld.w;
	
			lightWorld /=2.0;
			lightWorld +=0.5;
			float zLight =lightWorld.z;
			vec2 offset =vec2(0.000244,0.000244);
		
			for(float x=-0.5; x < 1.0; x+=0.5) 
			{
					for(float y=-0.5; y < 1.0; y+=0.5) 
					{
						float lightDepth = texture2D( shadowTexture1,lightWorld.xy+vec2(offset.x *x,offset.y *y)).x;
						if (zLight >lightDepth)
						{
							shadowTerm-=0.1111;
					
						}
					}
	
	
			}

		}
		gl_FragColor  =vec4(shadowTerm,shadowTerm,shadowTerm,1.0);
	// }// end background if


		//gl_FragColor =vec4(texture2D(shadowTexture1, uv_var).xyz ,1.0);
}