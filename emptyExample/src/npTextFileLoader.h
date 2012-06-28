//
//  npTextFileLoader.h
//  displaylist
//
//  Created by Kris Temmerman on 01/10/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef displaylist_npTextFileLoader_h
#define displaylist_npTextFileLoader_h





#include "npIncludes.h"



using namespace std;
class npTextFileLoader
{

public:
    static string  load(string file, string type )
    {
        string path  = ofToDataPath(file+"."+type );
        char *patName =(char*)   path.data();
        char *source = NULL;
        source = loadText(patName);
        
        string s  =source;
        return s;    
    
    
    }
    static const char * loadChar(string file, string type )
    {
        string path  = ofToDataPath(file+"."+type  );
        char *patName =(char*)   path.data();
        char *source = NULL;
        source = loadText(patName);
        
        
        return source;
        
        
        
    }
    
    static  char * loadText(const char *fileName)
    {
        GLchar *shaderText = NULL;
        GLint shaderLength = 0;
        FILE *fp;
        
        fp = fopen(fileName, "r");
        
        if (fp != NULL)
        {
            while (fgetc(fp) != EOF)
            {
                shaderLength++;
            }
            rewind(fp);
            shaderText = (GLchar *)malloc(shaderLength+1);
            if (shaderText != NULL)
            {
                fread(shaderText, 1, shaderLength, fp);
            }
            shaderText[shaderLength] = '\0';
            fclose(fp);
        }
        
        return shaderText;
    }

};


#endif
