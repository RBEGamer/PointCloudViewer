//
//  depth_device.hpp
//  PointCloudViewer
//
//  Created by Marcel Ochsendorf on 17.08.17.
//  Copyright © 2017 Marcel Ochsendorf. All rights reserved.
//

#ifndef depth_device_hpp
#define depth_device_hpp

#include <stdio.h>



class depth_device{

    
    
public:
    depth_device();
    virtual ~depth_device();
    
    

    //perform a scan
    virtual void update();
    virtual void print_device_info();
    


};


#endif /* depth_device_hpp */
