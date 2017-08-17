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
    
    
    struct RES_POINT{
        
        int x;
        int y;
    };
    
    
    //hardcode kin paramters
    //create own thread
    
    bool connect(std::string _serial, CON_MODE _mode = CON_MODE::CON_MODE_CPU);
    bool disconnect();
    
    
    bool start_capture();
    bool stop_capture();
    std::string get_default_device_serial();
     RES_POINT get_resolution();
    
    //scan
    void update(); //todo remove
    
   private:
    
    static void* processing_frames(void* _this);

    bool is_thread_running = false;

    std::string device_serial = "";
    //libfreenect vars
    libfreenect2::Freenect2 freenect2;
    libfreenect2::Freenect2Device *dev = 0;
    libfreenect2::PacketPipeline *pipeline = 0;
    int deviceId = -1;
    
     pthread_t processing_thread;
};




#endif /* depth_device_kinect_v2_hpp */
