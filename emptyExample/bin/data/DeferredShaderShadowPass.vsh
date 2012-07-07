//
//  Shader.vsh
//  displaylist
//
//  Created by Kris Temmerman on 16/09/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

attribute vec4 position;
attribute vec2 uv;


varying vec2 uv_var;



void main()
{
    
    gl_Position =position;
    uv_var=uv;
 
     
    
}
