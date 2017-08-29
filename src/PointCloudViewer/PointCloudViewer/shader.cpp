//
//  shader.cpp
//  PointCloudViewer
//
//  Created by Marcel Ochsendorf on 29.08.17.
//  Copyright © 2017 Marcel Ochsendorf. All rights reserved.
//

#include "shader.hpp"

shader::shader(){
    loaded_shaders.clear();
}


shader::~shader(){

}


shader::shader(const std::string& _program_to_use_name){
    //TOTO SET SHADER TO USE
    shader_set_name =_program_to_use_name;
    shader_set = true;
}


void shader::use_shader(){
    if(shader_set_name != "" && shader::shader_loaded && shader_set){
        
    }else{
        return;
    }
    SHADER_INFO tmp =get_shader(shader_set_name);
    glUseProgram(tmp.program_id);
}


bool shader::load_shaders_from_dir(const std::string _dir){

        std::vector<std::string> _folders;
#if __cplusplus > 201402L
        for (auto & read_dir : std::filesystem::directory_iterator(dir))
            std::cout << "found dir : " << read_dir << std::endl;
            _folders.push_back(read_dir);
        }
        if(_folders.size() <= 0){
             std::cout << "could not open directory" << std::endl;
            return false;
        }
#else
DIR *dp;
struct dirent *ep;

dp = opendir (_dir.c_str());
if (dp != NULL)
{
    while ((ep = readdir (dp))){
        std::cout <<  "found dir : " << ep->d_name << std::endl;
        _folders.push_back(ep->d_name);
    }
    (void) closedir (dp);
}else{
    std::cout << "could not open directory" << std::endl;
    return false;
}
#endif

            
    //NOW CHECK FOR EACH FOLDER THE CONTAINING FILES
    for(int i = 0; i <_folders.size(); i++){
        std::string fin_path = _dir + "/" + _folders.at(i);
        SHADER_INFO tmp_info;
        
        std::vector<std::string> files_in_folder;
        std::string shader_strings[4] = { "" }; //0 = geometry string
                                                //1 = vertex string
                                                //2 = fragemnt string
                                                //3 = compute string
#if __cplusplus > 201402L
        //TODO IMPLEMENT C++2017 way
#else
        DIR *pDIR;
        struct dirent *entry;
        if( (pDIR=opendir(fin_path.c_str())) ){
            while((entry = readdir(pDIR))){
                if( strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0 ){
                    std::cout << entry->d_name << std::endl;
                files_in_folder.push_back(entry->d_name);
                }
            }
            closedir(pDIR);
        }
#endif
        
        
        
        for(int j = 0; i < files_in_folder.size();j++){
            
            //check extention and sort into an array
            std::string tmp = "";
            tmp.append((const char*)files_in_folder.at(j).find_last_of('.'));
            bool read_res = false;
            if(tmp == OGL_SHADER_FILE_EXTENTION_GEOMETRY){
                read_res = load_file_content(files_in_folder.at(j).c_str(),shader_strings[0]);
            }else  if(tmp == OGL_SHADER_FILE_EXTENTION_VERTEX){
                read_res = load_file_content(files_in_folder.at(j).c_str(),shader_strings[1]);
            }else  if(tmp == OGL_SHADER_FILE_EXTENTION_FRAGMENT){
                 read_res = load_file_content(files_in_folder.at(j).c_str(),shader_strings[2]);
            }else  if(tmp == OGL_SHADER_FILE_EXTENTION_COMPUTE){
                read_res = load_file_content(files_in_folder.at(j).c_str(),shader_strings[3]);
            }else{
            std::cout << "this file ext:" << tmp << "is not compatible with a gsls shader, please see file ext name in shader.h file" << std::endl;
            }
            if(!read_res){
                std::cout << "cant read this file it it open ? " << std::endl;
            }
            
            //determent type
            if(shader_strings[0] == "" && shader_strings[1] != "" && shader_strings[2] != "" && shader_strings[3] == ""){
                tmp_info.type = shader::SHADER_TYPE::OGL_VERTEX_FRAGMENT;
            }else  if(shader_strings[0] != "" && shader_strings[1] != "" && shader_strings[2] != "" && shader_strings[3] == ""){
                tmp_info.type = shader::SHADER_TYPE::OGL_VERTEX_FRAGMENT_GEOMETRY;
            }else  if(shader_strings[0] == "" && shader_strings[1] == "" && shader_strings[2] == "" && shader_strings[3] != ""){
                    tmp_info.type = shader::SHADER_TYPE::OGL_COMPUTE;
            }else{
                    tmp_info.type = shader::SHADER_TYPE::OGL_INVALID;
            }
            
            
            //compile
            bool comp_res = false;
            
            if(tmp_info.type == SHADER_TYPE::OGL_VERTEX_FRAGMENT){
                comp_res =  compile_shader_ogl_vert_fragment(&tmp_info, shader_strings[1], shader_strings[2]);
            }else  if(tmp_info.type == SHADER_TYPE::OGL_VERTEX_FRAGMENT_GEOMETRY){
                throw "OGL_VERTEX_FRAGMENT_GEOMETRY not implemented";
            }else  if(tmp_info.type == SHADER_TYPE::OGL_COMPUTE){
                throw "OGL_COMPUTE not implemented";
            }
            
            //CHECK COMPILE RESULT
            if(!comp_res){
                std::cout << "compiling of the shader failed please check your code" << std::endl;
                return false;
            }
            
            
            
            //NOW PARSE LAYOUT PARAMETERS
            
            
            
        }//ende for files
        //parse layout
        
        
        
        //SAFE FINAL LOADED SHADER IN MAP
       shader::loaded_shaders[_folders.at(i)] = tmp_info;
    }//end for dir
            shader::shader_loaded = true;
            return true;
    //get types
    //parse layouts
    //load shaders
    //safe glint as foldername in map
         
}

            
            
bool shader::compile_shader_ogl_vert_fragment(shader::SHADER_INFO* _info, std::string& _vertex_string, std::string& _fragment_string){
    if(_info != nullptr){
        std::cout << __FUNCTION__ << " : info is null" << std::endl;
        return false;
    }
    
    // Create the shaders
    GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    
    
    GLint Result = GL_FALSE;
    int InfoLogLength;
    
    
    // Compile Vertex Shader
    char const * VertexSourcePointer = _vertex_string.c_str();
    glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
    glCompileShader(VertexShaderID);
    
    // Check Vertex Shader
    glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 ){
        std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
        glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
        printf("%s\n", &VertexShaderErrorMessage[0]);
    }
    
    
    
    // Compile Fragment Shader
    char const * FragmentSourcePointer = _fragment_string.c_str();
    glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
    glCompileShader(FragmentShaderID);
    
    // Check Fragment Shader
    glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 ){
        std::vector<char> FragmentShaderErrorMessage(InfoLogLength+1);
        glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
        printf("%s\n", &FragmentShaderErrorMessage[0]);
    }
    
    
    // Link the program
    printf("Linking program\n");
    GLuint ProgramID = glCreateProgram();
    glAttachShader(ProgramID, VertexShaderID);
    glAttachShader(ProgramID, FragmentShaderID);
    glLinkProgram(ProgramID);
    
    // Check the program
    glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
    glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 ){
        std::vector<char> ProgramErrorMessage(InfoLogLength+1);
        glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
        printf("%s\n", &ProgramErrorMessage[0]);
    }
    
    
    glDetachShader(ProgramID, VertexShaderID);
    glDetachShader(ProgramID, FragmentShaderID);
    
    glDeleteShader(VertexShaderID);
    glDeleteShader(FragmentShaderID);
    
   
    
    _info->program_id = ProgramID;
    return ProgramID;
}
            

bool shader::load_file_content(const char* _file, std::string& _string){
_string = "";
    std::ifstream FileLoadStream(_file, std::ios::in);
    if(FileLoadStream.is_open()){
        std::string Line = "";
        while(getline(FileLoadStream, Line)){
            _string += "\n" + Line;
        }
        FileLoadStream.close();
    }
}
       
            
            
shader::SHADER_INFO shader::get_shader(const std::string _name){
    if(shader::loaded_shaders.size() <= 0){
    throw "shaders not loaded or no shaders found";
    }
    if(shader::loaded_shaders.find(_name) == shader::loaded_shaders.end()){
      throw "shader not exists";
    }
    return shader::loaded_shaders[_name];
}

            
