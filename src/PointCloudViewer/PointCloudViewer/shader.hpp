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

//ONLY THE LAST . COUNTS AS EXTENTION .abc.def -> .def
#define OGL_SHADER_FILE_EXTENTION_GEOMETRY ".geom"
#define OGL_SHADER_FILE_EXTENTION_VERTEX ".vert"
#define OGL_SHADER_FILE_EXTENTION_FRAGMENT ".frag"
#define OGL_SHADER_FILE_EXTENTION_COMPUTE ".comp"

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
        OGL_LAYOUT_TYPE_MAT3,
        OGL_LAYOuT_TYPE_INVALID
    };
    
    struct SHADER_LAYOUT_ITEM{
        SHADER_LAYOUT_TYPE type;
        std::string uniform_name;
        
        SHADER_LAYOUT_ITEM()
        {
            type = SHADER_LAYOUT_TYPE::OGL_LAYOuT_TYPE_INVALID;
            uniform_name = "invalid";
        }
    };
    
    struct SHADER_INFO{
        SHADER_TYPE type;
        GLint program_id;
        std::vector<SHADER_LAYOUT_ITEM> layout;//TODO MAP
        
        SHADER_INFO()
        {
            type = SHADER_TYPE::OGL_INVALID;
            program_id = 0;
            layout.clear();
        }
    };

    
    struct FILE_CHANGE_INFO{
        std::string filename;
        std::string folder_path;
    };
    
    
    shader();
    shader(const std::string& _program_to_use_name);
    ~shader();
    
    void use_shader();
    void unuse_shader();
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
    
    void set_shader_name(const std::string _name);
    
    
    typedef std::map<std::string, SHADER_INFO> SH_MAP; //list with all loaded shaders

  private:
    
    #define  folder_name_ignore_list_len  3
    const std::string folder_name_ignore_list[folder_name_ignore_list_len] = {".", "..", ".DS_Store"};
    
    
    
    
    
    static SH_MAP loaded_shaders;
    static bool shader_loaded;
    bool shader_set = false;
    std::string shader_set_name = "";
    
    
    //compiles a vetex fagment shader with code an sets the gint int the shader info
    bool compile_shader_ogl_vert_fragment(SHADER_INFO* _info, std::string& _vertex_string, std::string& _fragment_string);
    //loads the content of a file to a string
    bool load_file_content(const char* _file, std::string& _string);
    //small init func for correct static map init
    static SH_MAP init_map() {
        SH_MAP map;
        map["invalid"] = SHADER_INFO();
        return map;
    }
    

};
#endif /* shader_hpp */
