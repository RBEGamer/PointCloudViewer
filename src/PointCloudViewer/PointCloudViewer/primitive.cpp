//
//  primitive.cpp
//  PointCloudViewer
//
//  Created by Marcel Ochsendorf on 17.08.17.
//  Copyright © 2017 Marcel Ochsendorf. All rights reserved.
//

#include "primitive.hpp"



primitive::primitive(){
    position = sf::Vector3f(0.0f,0.0,0.0f);
    scale = sf::Vector3f(1.0f,1.0f,1.0f);
    roation = sf::Vector3f(0.0f,0.0f,0.0f);
    enabled = true;
    init();
}

primitive::~primitive(){
}

void primitive::init(){
}

void primitive::update(const float _delta){
}

void primitive::draw(){
}

void primitive::print_info(){
    std::cout << "primitive " << " pos=" << position.x << "," << position.y << "," << position.z << "" << std::endl;
}
