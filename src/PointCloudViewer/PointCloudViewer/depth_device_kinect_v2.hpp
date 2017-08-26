//
//  depth_device_kinect_v2.hpp
//  PointCloudViewer
//
//  Created by Marcel Ochsendorf on 17.08.17.
//  Copyright © 2017 Marcel Ochsendorf. All rights reserved.
//

#ifndef depth_device_kinect_v2_hpp
#define depth_device_kinect_v2_hpp

#include <stdio.h>
#include <iostream>
#include <string.h>


//using libfreenect2
#include <libfreenect2/libfreenect2.hpp>
#include <libfreenect2/frame_listener_impl.h>
#include <libfreenect2/registration.h>
#include <libfreenect2/packet_pipeline.h>
#include <libfreenect2/logger.h>

//pthread for processing
#include <pthread.h>
#include<mutex>


//for sf::vector
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>


//for the primitives



//NOT CHANGEABLE DEFINES BY THE V2 Hardware
#define MIN_DEPTH_MM 0
#define MAX_DEPTH_MM 4500

#define KINECT_V2_CAMERA_PARAMS_RES_DEPTH_X 512
#define KINECT_V2_CAMERA_PARAMS_RES_DEPTH_Y 424
#define KINECT_V2_CAMERA_PARAMS_RES_DEPTH_PIXELS (KINECT_V2_CAMERA_PARAMS_RES_DEPTH_X*KINECT_V2_CAMERA_PARAMS_RES_DEPTH_Y)
#define  KINECT_V2_CAMERA_PARAMS_CX 254.878f
#define  KINECT_V2_CAMERA_PARAMS_CY 205.395f
#define  KINECT_V2_CAMERA_PARAMS_FX 365.456f
#define  KINECT_V2_CAMERA_PARAMS_FY 365.456f
#define  KINECT_V2_CAMERA_PARAMS_K1 0.0905474f
#define  KINECT_V2_CAMERA_PARAMS_K2 -0.26819f
#define  KINECT_V2_CAMERA_PARAMS_K3 0.0950862f
#define  KINECT_V2_CAMERA_PARAMS_P1 0.0f
#define  KINECT_V2_CAMERA_PARAMS_P2 0.0f


class depth_device_kinect_v2{


public:
    depth_device_kinect_v2();
    ~depth_device_kinect_v2();
    
    enum CON_MODE{
        CON_MODE_OGL,
        CON_MODE_OCL,
        CON_MODE_CUDA,
        CON_MODE_AUTO,
        CON_MODE_CPU
    };
    
    

 
    sf::Vector3f* depth_points;
    
    
    //hardcode kin paramters
    //create own thread
    
    bool connect(std::string _serial, CON_MODE _mode = CON_MODE::CON_MODE_CPU);
    bool disconnect();
    
    
    bool start_capture();
    bool stop_capture();
    std::string get_default_device_serial();
    sf::Vector2i get_resolution();
    
    //scan
    void update(); //todo remove
    
   private:
    
    static void* processing_frames(void* _this);

    bool is_thread_running = false;
    float depth_point_scaling_factor = 1.0f;
    std::string device_serial = "";
    //libfreenect vars
    libfreenect2::Freenect2 freenect2;
    libfreenect2::Freenect2Device *dev = 0;
    libfreenect2::PacketPipeline *pipeline = 0;
    int deviceId = -1;
    pthread_t processing_thread;
    
    
public:
     std::mutex depth_read_lock;

    
    
    
};




#endif /* depth_device_kinect_v2_hpp */
