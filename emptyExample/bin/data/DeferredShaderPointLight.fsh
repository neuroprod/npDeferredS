

uniform sampler2D normalTexture; 
uniform sampler2D depthTexture; 
uniform mat4 perspectiveInvMatrix ;



varying vec3 center_var;
varying vec3 color_var;
varying vec4 persPos_var;
varying vec4 worldPos_var;
varying vec3 normal_var;

varying float lightSize_var;

void main()
{

        vec3 pos  = persPos_var.xyz /persPos_var.w;
        vec2 uv =  pos.xy *0.5+0.5 ;
  
    
    
        float depth  = texture2D(depthTexture, uv).x *2.0-1.0 ;
		vec3 N   =texture2D(normalTexture, uv).xyz *2.0-1.0 ;
	

		pos.z =depth;
        vec4 worldPosSurf = perspectiveInvMatrix* vec4(pos,1.0);
        worldPosSurf.xyz/=worldPosSurf.w;
        
    
    
        vec3 dir = worldPosSurf.xyz-center_var;
   
        float l = length( dir);
        
        float dist =1.0-pow((clamp (l ,0.0,lightSize_var)/lightSize_var),2.0);
  
    
        float lambert  =clamp(dot(normalize(dir) , -N ),0.0,1.0);
   
	

        gl_FragColor = vec4(color_var *dist * lambert   ,1.0);

   
  
}