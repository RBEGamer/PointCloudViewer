//
//  primitive_cube.hpp
//  PointCloudViewer
//
//  Created by Marcel Ochsendorf on 17.08.17.
//  Copyright © 2017 Marcel Ochsendorf. All rights reserved.
//

#ifndef primitive_cube_hpp
#define primitive_cube_hpp

#include <stdio.h>

#include "primitive.hpp"

#include "shader.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>
#include <cmath>

#include <iostream>
class primitive_cube : public primitive {
    
    
    
public:
    primitive_cube();
    ~primitive_cube();
    void draw();
    void update(const float _delta);
    void init();
    void print_info();
    
    sf::Vector3f color;
    void set_shader(std::string _name);
private:
    shader draw_shader;

    
};





#endif /* primitive_cube_hpp */
