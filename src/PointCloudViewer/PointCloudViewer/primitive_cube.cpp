//
//  primitive_cube.cpp
//  PointCloudViewer
//
//  Created by Marcel Ochsendorf on 17.08.17.
//  Copyright © 2017 Marcel Ochsendorf. All rights reserved.
//

#include "primitive_cube.hpp"



primitive_cube::primitive_cube(){
    position = sf::Vector3f(0.0f,0.0,0.0f);
    scale = sf::Vector3f(1.0f,1.0f,1.0f);
    roation = sf::Vector3f(0.0f,0.0f,0.0f);
    color = sf::Vector3f(1.0f,0.0f,1.0f);
    init();
}



primitive_cube::~primitive_cube(){

}


void primitive_cube::init(){


}

void primitive_cube::draw(){
        glPushMatrix();
    
    glTranslatef(position.x, position.y, position.z);
    
    //Change the color of the cube to OpenGL RGB (goes from [0,1])
    glColor3f(color.x, color.y, color.z);
    
    //Draw a cube using the position of the cube as the center.
    glBegin(GL_QUADS);
    float render_size = scale.x; //TODO REMOVE
    glVertex3f(-(render_size/2.0f), -(render_size/2.0f), -(render_size/2.0f));
    glVertex3f(-(render_size/2.0f), (render_size/2.0f), -(render_size/2.0f));
    glVertex3f((render_size/2.0f), (render_size/2.0f), -(render_size/2.0f));
    glVertex3f((render_size/2.0f), -(render_size/2.0f), -(render_size/2.0f));
    
    glVertex3f(-(render_size/2.0f), -(render_size/2.0f), (render_size/2.0f));
    glVertex3f(-(render_size/2.0f), (render_size/2.0f), (render_size/2.0f));
    glVertex3f((render_size/2.0f), (render_size/2.0f), (render_size/2.0f));
    glVertex3f((render_size/2.0f), -(render_size/2.0f), (render_size/2.0f));
    
    glVertex3f(-(render_size/2.0f), -(render_size/2.0f), -(render_size/2.0f));
    glVertex3f(-(render_size/2.0f), (render_size/2.0f), -(render_size/2.0f));
    glVertex3f(-(render_size/2.0f), (render_size/2.0f), (render_size/2.0f));
    glVertex3f(-(render_size/2.0f), -(render_size/2.0f), (render_size/2.0f));
    
    glVertex3f((render_size/2.0f), -(render_size/2.0f), -(render_size/2.0f));
    glVertex3f((render_size/2.0f), (render_size/2.0f), -(render_size/2.0f));
    glVertex3f((render_size/2.0f), (render_size/2.0f), (render_size/2.0f));
    glVertex3f((render_size/2.0f), -(render_size/2.0f), (render_size/2.0f));
    
    glVertex3f(-(render_size/2.0f), -(render_size/2.0f), (render_size/2.0f));
    glVertex3f(-(render_size/2.0f), -(render_size/2.0f), -(render_size/2.0f));
    glVertex3f((render_size/2.0f), -(render_size/2.0f), -(render_size/2.0f));
    glVertex3f((render_size/2.0f), -(render_size/2.0f), (render_size/2.0f));
    
    glVertex3f(-(render_size/2.0f), (render_size/2.0f), (render_size/2.0f));
    glVertex3f(-(render_size/2.0f), (render_size/2.0f), -(render_size/2.0f));
    glVertex3f((render_size/2.0f), (render_size/2.0f), -(render_size/2.0f));
    glVertex3f((render_size/2.0f), (render_size/2.0f), (render_size/2.0f));
    glEnd();
    glPopMatrix();
}


void primitive_cube::update(const float _delta){

}


