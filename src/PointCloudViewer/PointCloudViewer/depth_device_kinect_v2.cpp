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
    is_thread_running = false;
    device_serial = "";

}
depth_device_kinect_v2::~depth_device_kinect_v2(){
    stop_capture();
    disconnect();
}



//hardcode kin paramters
//create own thread

bool depth_device_kinect_v2::connect(std::string _serial, CON_MODE _mode){

    if(dev != 0)
    {
        std::cout << "please close device first" << std::endl;
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
    
    //NOW OPEN DEVICE
    if(pipeline)
    {
        dev = freenect2.openDevice(_serial, pipeline);
    }
    else
    {
        dev = freenect2.openDevice(_serial);
    }
    
    if(dev == 0)
    {
        std::cout << "failure opening device!" << std::endl;
        return false;
    }
    
    device_serial = _serial;
    
    
    
    //TODO createenum option for stream

    
    
   
    return true;
}


std::string depth_device_kinect_v2::get_default_device_serial(){
    return freenect2.getDefaultDeviceSerialNumber();
}

bool depth_device_kinect_v2::start_capture(){
    if(dev != 0){
     dev->start();
    }
    is_thread_running = true; //needed before start
    //create thread
    if (pthread_create(&processing_thread, NULL, processing_frames, this))
    {
        std::cout << "ERROR - starting processing thread" << std::endl;
        is_thread_running = false;
        return;
    }
    return  is_thread_running;
}



bool depth_device_kinect_v2::stop_capture(){
    is_thread_running = false;
    if(pthread_join(processing_thread, NULL)) {
               fprintf(stderr, "Error joining thread\n");
        return 2;
    }
    if(dev != 0){
        dev->stop();
    }
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



bool depth_device_kinect_v2::disconnect(){
    if(dev != 0)
    {
        dev->stop();
    dev->close();
    }
    return true; //TODO return release frames
}




void* depth_device_kinect_v2::processing_frames(void* _this){
    depth_device_kinect_v2* caller = static_cast<depth_device_kinect_v2*>(_this);
    
    

    std::cout << "thread start" <<std::endl;
    if(caller == nullptr){
        std::cout << "static_cast error" << std::endl;
        return;
    }
    if(caller->dev == nullptr){
        return;
    }

    libfreenect2::SyncMultiFrameListener listener(libfreenect2::Frame::Color |libfreenect2::Frame::Depth );
    libfreenect2::FrameMap frames;
   
    caller->dev->setColorFrameListener(&listener);
    caller->dev->setIrAndDepthFrameListener(&listener);
    

    while (true) {
        
        std::cout << "b";
        if (!listener.waitForNewFrame(frames, 1000))
        {
           std::cout << "waitForNewFrameTimeout" << std::endl;
           return;
       }
        
        
       libfreenect2::Frame *rgb = frames[libfreenect2::Frame::Color];
        
        
        //depth processing
        //ADD CUDA OPENCL HERE
        //USING ARRAYFIRE
       libfreenect2::Frame *depth = frames[libfreenect2::Frame::Depth];
        float *frame_data = (float *)depth->data;
        float raw_depth_value = -1.0f;
        for (size_t w = 0; w < depth->width; w++) {
            for (size_t h = 0; h < depth->height; h++) {
                raw_depth_value = frame_data[h*depth->width+w];
                //CALC REAL 3D POINT
            }
        }
        
       
        
        
        listener.release(frames);
    }
   
    std::cout << "thread end" <<std::endl;
}
