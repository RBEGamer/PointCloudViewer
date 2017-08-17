//
//  depth_device_kinect_v2.cpp
//  PointCloudViewer
//
//  Created by Marcel Ochsendorf on 17.08.17.
//  Copyright © 2017 Marcel Ochsendorf. All rights reserved.
//

#include "depth_device_kinect_v2.hpp"


/*
 
 if(freenect2.enumerateDevices() == 0)
 {
 std::cout << "no device connected!" << std::endl;
 return -1;
 }
 */

depth_device_kinect_v2::depth_device_kinect_v2(){
}
depth_device_kinect_v2::~depth_device_kinect_v2(){
}



//hardcode kin paramters
//create own thread

bool depth_device_kinect_v2::connect(std::string _serial, CON_MODE _mode){
    
    
    
    return false;
}


std::string depth_device_kinect_v2::get_default_device_serial(){
    return "";
}



depth_device_kinect_v2::RES_POINT depth_device_kinect_v2::get_resolution(){
    RES_POINT p;
    p.x = 498;
    p.y = 512;
    return p;
}

//scan
void depth_device_kinect_v2::update(){
}


bool depth_device_kinect_v2::create_pipeline(){
    
    
    return false;
}

