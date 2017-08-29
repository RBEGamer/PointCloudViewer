//
//  shader.hpp
//  PointCloudViewer
//
//  Created by Marcel Ochsendorf on 29.08.17.
//  Copyright © 2017 Marcel Ochsendorf. All rights reserved.
//

#ifndef shader_hpp
#define shader_hpp

#include <stdio.h>


#include <string>
#include <iostream>

#include <fstream>



#if __cplusplus > 201402L
#include <filesystem> //USING C++17 filesystem
#else
#include <sys/types.h>
#include <dirent.h>
#endif




#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>

#include <map>
#include <vector>


#define OGL_SHADER_FILE_EXTENTION_GEOMETRY "geom"
#define OGL_SHADER_FILE_EXTENTION_VERTEX "vert"
#define OGL_SHADER_FILE_EXTENTION_FRAGMENT "frag"
#define OGL_SHADER_FILE_EXTENTION_COMPUTE "comp"

class shader{


public:
    
    enum SHADER_TYPE{
        OGL_VERTEX_FRAGMENT,
        OGL_VERTEX_FRAGMENT_GEOMETRY,
        OGL_COMPUTE,
        OGL_INVALID,
    };
    
    enum SHADER_LAYOUT_TYPE{
        OGL_LAYOUT_TYPE_VEC3,
        OGL_LAYOUT_TYPE_VEC4,
        OGL_LAYOUT_TYPE_TEXT2D,
        OGL_LAYOUT_TYPE_MAT4,
        OGL_LAYOUT_TYPE_MAT3
    };
    
    struct SHADER_INFO{
        SHADER_TYPE type;
        GLint program_id;
        std::vector<SHADER_LAYOUT_TYPE> layout;
    };

    
    
    static std::map<std::string, SHADER_INFO> loaded_shaders;
    
    
    shader();
    shader(const std::string& _program_to_use_name);
    ~shader();
    
    void use_shader();
    
    /*
     load all shader in folders
     
     
     FIST LOAD THE DIRECTORIES IN THE SHADER FOLDER
     STRUCTURE OF THE FOLDER:
     
     _dir-> shader1name ->   bla.vert
     ->   blat.frag
     
     -> shader2name ->    bla.vert
     ->    bla_frag
     */
    bool load_shaders_from_dir(const std::string _dir);
    
    
    //returns a shader info for to use
    SHADER_INFO get_shader(const std::string _name);
    
    
    

    
    
  private:

    
    //compiles a vetex fagment shader with code an sets the gint int the shader info
    bool compile_shader_ogl_vert_fragment(SHADER_INFO* _info, std::string& _vertex_string, std::string& _fragment_string);
    //loads the content of a file to a string
    bool load_file_content(const char* _file, std::string& _string);

    bool shader_set = false;
    std::string shader_set_name = "";
    
    static bool shader_loaded;
};
#endif /* shader_hpp */
