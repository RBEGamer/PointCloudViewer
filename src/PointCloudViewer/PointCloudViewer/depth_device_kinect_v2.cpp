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
    
    depth_points = new sf::Vector3f[KINECT_V2_CAMERA_PARAMS_RES_DEPTH_X*KINECT_V2_CAMERA_PARAMS_RES_DEPTH_Y]();
#ifdef __CUDACC__
    //TODO MALLOC ON DEV
#endif
    
    
    
}
depth_device_kinect_v2::~depth_device_kinect_v2(){
    stop_capture();
    disconnect();
    delete [] depth_points;
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
    
    
    
 //TODO MALLOC POINTS
    //CREATE RING BUFFER with x times the size for scrolling effect

    
    
   
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

sf::Vector2i depth_device_kinect_v2::get_resolution(){
    sf::Vector2i p;
    p.x = KINECT_V2_CAMERA_PARAMS_RES_DEPTH_X;
    p.y = KINECT_V2_CAMERA_PARAMS_RES_DEPTH_Y;
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
    

    
    //DEPTH POINT VARS FOR CPU CALC
    float raw_depth_value = 0.0f;
    float px = 0.0f,py = 0.0f, pz = 0.0f;
    
    
   // caller->dd = &processed_depth_array_h;
   
    
    
    float fact = 1.0f;
    while (caller->is_thread_running) {
        
        fact = caller->depth_point_scaling_factor;
        
        if (!listener.waitForNewFrame(frames, 1000))
        {
           std::cout << "waitForNewFrameTimeout" << std::endl;
           continue;
       }
        
        
       libfreenect2::Frame *rgb = frames[libfreenect2::Frame::Color];
        //TODO ADD SIGN DETECTION
        
        
        
        
        //TODO ADD CUDA
       //GET RAW DATA OF THE DEPTH FRAME AND CLAC 3d point 1.0f = 1.0 meter
       libfreenect2::Frame *depth = frames[libfreenect2::Frame::Depth];
        float *frame_data = (float *)depth->data;

        
        
        if(caller->depth_read_lock.try_lock()){
        
        for (size_t w = 0; w < KINECT_V2_CAMERA_PARAMS_RES_DEPTH_X; w++) {
            for (size_t h = 0; h < KINECT_V2_CAMERA_PARAMS_RES_DEPTH_Y; h++) {
                raw_depth_value = frame_data[h*KINECT_V2_CAMERA_PARAMS_RES_DEPTH_X+w];
                //TODO CEHCK RANGE 0-4500
                //skip ranges
                if(raw_depth_value > MIN_DEPTH_MM && raw_depth_value < MAX_DEPTH_MM){
                /*
                 point.z = (depthValue);// / (1.0f); // Convert from mm to meters
                 point.x = (x - CameraParams.cx) * point.z / CameraParams.fx;
                 point.y = (y - CameraParams.cy) * point.z / CameraParams.fy;
                 */
                    pz = raw_depth_value/1000.0f;//// Convert from mm to meters
                    px = (w - KINECT_V2_CAMERA_PARAMS_CX) * pz / KINECT_V2_CAMERA_PARAMS_FX;
                    py = (h - KINECT_V2_CAMERA_PARAMS_CY) * pz / KINECT_V2_CAMERA_PARAMS_FY;
                    //assign claced point to array
                    *(caller->depth_points+h*depth->width+w+0) = sf::Vector3f(px*fact,py*fact,pz*fact);
                //    valid_depth_point[h*depth->width+w] = true;
                }else{
                  //  valid_depth_point[h*depth->width+w] = false;
                }

                } //END h
            } //END W
            
        caller->depth_read_lock.unlock();
        }//edn trylock
    //
   
      
        
        
        
       //TODO CLEANUP CUDA
        #ifdef __CUDACC__
        #endif
        
        //RELEASE FRAME
        listener.release(frames);
    }
   
    std::cout << "thread end" <<std::endl;
}
