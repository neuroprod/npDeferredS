//
//  Shader.vsh
//  displaylist
//
//  Created by Kris Temmerman on 16/09/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

attribute vec4 position;
attribute vec2 uv;

uniform vec3 lightDir;

varying vec2 uv_var;
varying vec3 lightDir_var;
uniform mat4 worldMatrix ;

void main()
{
    
    gl_Position =position;
    uv_var=uv;
  
    lightDir_var =(worldMatrix*vec4( lightDir.xyz,1.0)).xyz;
     
    
}
