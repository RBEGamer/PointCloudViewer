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

    
    depth_points = new DEPTH_POINT[KINECT_V2_CAMERA_PARAMS_RES_DEPTH_X*KINECT_V2_CAMERA_PARAMS_RES_DEPTH_Y*3]();

    
    
    
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
    got_new_depth_data = false;
    //create thread
    if (pthread_create(&processing_thread, NULL, &processing_frames,(void *)this))
    {
        std::cout << "ERROR - starting processing thread" << std::endl;
        is_thread_running = false;
        return;
    }
    return  is_thread_running;
}



bool depth_device_kinect_v2::stop_capture(){
    is_thread_running = false;
    got_new_depth_data = false;
    if(pthread_join(processing_thread, NULL)) {
               fprintf(stderr, "Error joining thread\n");
        return 2;
    }
    if(dev != 0){
        dev->stop();
    }
}

sf::Vector2i depth_device_kinect_v2::get_resolution(){
    return  sf::Vector2i(KINECT_V2_CAMERA_PARAMS_RES_DEPTH_X,KINECT_V2_CAMERA_PARAMS_RES_DEPTH_Y);
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

sf::Vector3f depth_device_kinect_v2::get_depth_point(const  int _x, const int _y){
    if(depth_points == nullptr){
        std::cout << __FUNCTION__ << " - ERROR - ptr == null" << std::endl;
        throw __FUNCTION__;
        return sf::Vector3f(0.0f,0.0f,0.0f);
    }
    if(_x >= KINECT_V2_CAMERA_PARAMS_RES_DEPTH_X || _y >= KINECT_V2_CAMERA_PARAMS_RES_DEPTH_Y){
        std::cout << __FUNCTION__ << " - ERROR - coordinate out of range" << std::endl;
        throw __FUNCTION__;
        return sf::Vector3f(0.0f,0.0f,0.0f);
    }
    depth_read_lock.lock();
    sf::Vector3f tmp = sf::Vector3f((depth_points+_y*KINECT_V2_CAMERA_PARAMS_RES_DEPTH_X+_x+0)->x*depth_scale,
                                    (depth_points+_y*KINECT_V2_CAMERA_PARAMS_RES_DEPTH_X+_x+0)->y*depth_scale,
                                    (depth_points+_y*KINECT_V2_CAMERA_PARAMS_RES_DEPTH_X+_x+0)->z*depth_scale);
    depth_read_lock.unlock();
    return tmp;
}


//SIMPLY GOTO THOUGH EACH POINT AN UPDATE POSTION
bool depth_device_kinect_v2::refresh_existing_primitives_position(std::vector<primitive*> _primitives){
    if(dev == 0){
        std::cout << __FUNCTION__ << " - ERROR - please open device first" << std::endl;

        return false;
    }
    if(depth_points == nullptr){
        std::cout << __FUNCTION__ << " - ERROR - ptr == null" << std::endl;
        throw __FUNCTION__;
        return false;
    }
   
    
    depth_read_lock.lock();
    
   
    if(!got_new_depth_data){
        return 0;
    }
    
    size_t prim_index_counter = 0;
    for (size_t w = 0; w < KINECT_V2_CAMERA_PARAMS_RES_DEPTH_X; w++) {
        for (size_t h = 0; h < KINECT_V2_CAMERA_PARAMS_RES_DEPTH_Y; h++) {
            if(_primitives.at(prim_index_counter) == nullptr){
                prim_index_counter++;
                continue;
            }
            //Simply copy over
            if(prim_index_counter >= _primitives.size()){
                break;
            }
            _primitives.at(prim_index_counter)->position =  sf::Vector3f((depth_points+h*KINECT_V2_CAMERA_PARAMS_RES_DEPTH_X+w)->x*depth_scale,
                                                                         (depth_points+h*KINECT_V2_CAMERA_PARAMS_RES_DEPTH_X+w)->y*depth_scale,
                                                                         (depth_points+h*KINECT_V2_CAMERA_PARAMS_RES_DEPTH_X+w)->z*depth_scale);
            prim_index_counter++;
        }
    }
    got_new_depth_data = false;
    depth_read_lock.unlock();
    return prim_index_counter;
}





//THIS IS THE THREAD FUNCTION FOR GET A KINECT FRAME
void* depth_device_kinect_v2::processing_frames(void* _this){
    depth_device_kinect_v2* caller = reinterpret_cast<depth_device_kinect_v2*>(_this);
    
    

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
    
    
 
    
        while (caller->is_thread_running) {
        
       
        
            caller->got_new_depth_data = false;

            
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
      
            
//#ifdef __CUDACC__
//             cuda_calc_depth_3d_point<<<1, 1>>>(frame_data, caller->depth_points);
//#else
            
        for (size_t w = 0; w < KINECT_V2_CAMERA_PARAMS_RES_DEPTH_X; w++) {
            for (size_t h = 0; h < KINECT_V2_CAMERA_PARAMS_RES_DEPTH_Y; h++) {
                raw_depth_value = frame_data[h*KINECT_V2_CAMERA_PARAMS_RES_DEPTH_X+w];
                pz = raw_depth_value/DEPTH_UNIT_FACTOR;//// Convert from mm to meters
                px = (w - KINECT_V2_CAMERA_PARAMS_CX) * pz / KINECT_V2_CAMERA_PARAMS_FX;
                py = (h - KINECT_V2_CAMERA_PARAMS_CY) * pz / KINECT_V2_CAMERA_PARAMS_FY;
                //ASSIGN
                (caller->depth_points+h*depth->width+w)->x= px;// = sf::Vector3f(px,py,pz);
                (caller->depth_points+h*depth->width+w)->y= py;
                (caller->depth_points+h*depth->width+w)->z= pz;
                (caller->depth_points+h*depth->width+w)->length = sqrtf((powf(px, 2.0f)+powf(py, 2.0f)+powf(pz, 2.0f)));
                } //END h
            } //END W
//#endif
            caller->got_new_depth_data = true;
            caller->depth_read_lock.unlock();
        }//end trylock
    
   
        //RELEASE FRAME
        listener.release(frames);
    }
    std::cout << "thread end" <<std::endl;
}



#ifdef __CUDACC__
__global__ void cuda_calc_depth_3d_point(float* _raw_depth, DEPTH_POINT* _point_array)
{
   int i = blockIdx.x * blockDim.x + threadIdx.x;
    
    
}
#endif
