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

    if(pipeline){
        std::cout << "pipeline open please close the device" << std::endl;
        return false;
    }
    
    
    if(_mode == CON_MODE::CON_MODE_AUTO){
#ifdef __CUDACC__
    if(!pipeline){
        pipeline = new libfreenect2::CudaPacketPipeline(deviceId);
        std::cout << "depth_devive_kinect_v2 - using CUDA" << std::endl;
    }
#endif
    if(!pipeline){
        pipeline = new libfreenect2::OpenGLPacketPipeline();
        std::cout << "depth_devive_kinect_v2 - using OpenGL" << std::endl;
    }
    if(!pipeline){
        pipeline = new libfreenect2::OpenCLPacketPipeline(deviceId);
        std::cout << "depth_devive_kinect_v2 - using OpenCL" << std::endl;
    }
    if(!pipeline){
     pipeline = new libfreenect2::CpuPacketPipeline();
        std::cout << "depth_devive_kinect_v2 - using CPU" << std::endl;
    }
        
    }else{
        
        
        
#ifdef __CUDACC__
        if(!pipeline && _mode == CON_MODE::CON_MODE_CUDA){
            pipeline = new libfreenect2::CudaPacketPipeline(deviceId);
            std::cout << "depth_devive_kinect_v2 - using CUDA" << std::endl;
        }
#endif
        if(!pipeline&& _mode == CON_MODE::CON_MODE_OGL){
            pipeline = new libfreenect2::OpenGLPacketPipeline();
            std::cout << "depth_devive_kinect_v2 - using OpenGL" << std::endl;
        }
        if(!pipeline&& _mode == CON_MODE::CON_MODE_OCL){
            pipeline = new libfreenect2::OpenCLPacketPipeline(deviceId);
            std::cout << "depth_devive_kinect_v2 - using OpenCL" << std::endl;
        }
        if(!pipeline&& _mode == CON_MODE::CON_MODE_CPU){
            pipeline = new libfreenect2::CpuPacketPipeline();
            std::cout << "depth_devive_kinect_v2 - using CPU" << std::endl;
        }
        
        
    }
    
    
    return false;
}


std::string depth_device_kinect_v2::get_default_device_serial(){
    return freenect2.getDefaultDeviceSerialNumber();
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




