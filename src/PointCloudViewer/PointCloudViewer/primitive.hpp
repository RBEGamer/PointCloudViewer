//
//  primitive.hpp
//  PointCloudViewer
//
//  Created by Marcel Ochsendorf on 17.08.17.
//  Copyright © 2017 Marcel Ochsendorf. All rights reserved.
//

#ifndef primitive_hpp
#define primitive_hpp

#include <stdio.h>



#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>
#include <cmath>

#include <iostream>
class primitive{
    
    
    
public:
    primitive();
    virtual ~primitive();
    
    virtual void draw();
    virtual void update(const float _delta);
    virtual void init();
    
    
    
    bool enabled;
    sf::Vector3f position;
    sf::Vector3f roation;
    sf::Vector3f scale;
    primitive* parent = NULL;
};




#endif /* primitive_hpp */
