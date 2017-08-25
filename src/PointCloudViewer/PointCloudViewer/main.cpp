//main.cpp Marcel Ochsendorf github.com/RBEGamer



#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>


#include <vector>
#include <cmath>

#if defined(__APPLE__) && defined(__MACH__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>


#include "primitive.hpp"
#include "primitive_cube.hpp"


#include "depth_device_kinect_v2.hpp"

#define PI 3.1415926535897932384626433832795







//HELPER FUNCS HERE ---------------------------------------------------------------
#if defined(__APPLE__)
//on my old mac i have a opengl version < 2.1 where the gluPerspective still exists -> Xcode 8.2
#else
void perspectiveGL( GLdouble fovY, GLdouble aspect, GLdouble zNear, GLdouble zFar )
{
    GLdouble fW, fH;
    //fH = tan( (fovY / 2) / 180 * PI ) * zNear;
    fH = tan( fovY / 360 * PI ) * zNear;
    fW = fH * aspect;
    glFrustum( -fW, fW, -fH, fH, zNear, zFar );
}
#define gluPerspective(x,y,z,w) perspectiveGL(x,y,z,w)
#endif



//TIMER HERE
sf::Clock clockmain;
sf::Time lastKeyPress;
sf::Time delta;
sf::Time updateTime;



std::vector<primitive*> objs;
std::vector<primitive_cube*> cubes;


depth_device_kinect_v2 kinect_device;




std::vector<primitive*> allocate_cubes(std::vector<primitive*> *_obj_list, std::vector<primitive_cube*> *_cube_list, const unsigned int _count){
std::vector<primitive*> alloc_prims;
    for (size_t i = 0; i < _count; i++) {
        primitive_cube* testcube = new primitive_cube();
        objs.push_back(testcube);
        cubes.push_back(testcube);
        alloc_prims.push_back(testcube);
    }
    if(alloc_prims.size() != _count){
        std::cout << "ERROR - allocate_cubes failed for " << _count << " objects" << std::endl;
    }
    return alloc_prims;
}

int cleanup(){ //TODO DELETE MISSING
    std::cout << "cleanup" << std::endl;
    for (size_t i = 0; i < objs.size(); i++) {
        if(objs.at(i) != nullptr){
        delete objs.at(i);
        objs.at(i) = NULL;
        }
    }
    kinect_device.stop_capture();
    kinect_device.disconnect();
    objs.clear();
    return 0;
}


void process_sfml_event(sf::Window& _window){
    sf::Event event;
    while (_window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed){
            cleanup();
            _window.close();
        }
        if (event.type == sf::Event::Resized)
        {
            std::cout << "glViewport resize event" << std::endl;
            glViewport(0, 0, event.size.width, event.size.height);
        }
        if (event.type == sf::Event::KeyPressed){
            if (event.key.code == sf::Keyboard::Escape){
                cleanup();
                _window.close();
            }
            // if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
            //       camera_position += sf::Vector3f(10.1f,0.0f,0.0f)*delta.asSeconds();
            //  }
        }
    }
}






int main(int argc, char const** argv)
{
    
     sf::RenderWindow window(sf::VideoMode(800, 600), "PointCloudViewer");
    //clearcol
    glClearDepth(1.f);
    glClearColor(0.1412f, 0.1412f, 0.1412f, 0.f);
    
    
    /*TODO
     create own define file for types
     create scenemanager for holding objects
     include ini loader
     add input handler for key events
     add shader support
     add can data rec send wtih mutli can for tx2
     
     
     */
 
  
    /*
    

    float radius = 100;
    int angle = 30;
    for (int i = 0; i < 360; i+=10)
    {
        for (int j = 0; j < 180; j+=10)
        {
            //Use the equation of the Spherical Coordinate system to display a sphere
            sf::Vector3f posVec = sf::Vector3f(radius* sin((i)* PI / 180.0) * cos((j)* PI / 180.0), radius* sin((i)* PI / 180.0) * sin((j)* PI / 180.0), radius* cos((i)* PI / 180.0));
            float cubeSize = 1.0f;
            sf::Color colour = sf::Color(rand() % 205 + 50, rand() % 205 + 50, rand() % 205 + 50);
           
      
    
            testcube->position =posVec;
            testcube->scale = sf::Vector3f(cubeSize,cubeSize,cubeSize);
            testcube->color= sf::Vector3f(colour.r/255.0f,colour.g/255.0f,colour.b/255.0f);
         
            
            
        }
    }
    
    */
    
    
    
    
    
    
    
   std::vector<primitive*> test =  allocate_cubes(&objs,&cubes,512*424);
    
    
    
    
    
    
    
    
    

    if(kinect_device.connect(kinect_device.get_default_device_serial(), depth_device_kinect_v2::CON_MODE::CON_MODE_CPU)){
        std::cout << "kinect connected" << std::endl;
        kinect_device.start_capture();
    }else{
        std::cout << "no kinect with serial found" << std::endl;
    }

    
    //init  all existing objs //todo remove
   // for (size_t i = 0; i < objs.size(); i++) {
   //         objs.at(i)->init();
   // }
    
    
    
    
    while (window.isOpen())
    {
        //calc deltatime
        delta = clockmain.getElapsedTime() - updateTime;
        updateTime = clockmain.getElapsedTime();
        //handle input events
        
        kinect_device.update();
        
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //Enable the OpenGL configs to draw in 3D
        // Enable Z-buffer read and write
        glEnable(GL_DEPTH_TEST);
        glDepthMask(GL_TRUE);
        // Setup a perspective projection
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(90.f, 1.f, 1.f, 2000.0f);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        
        
        kinect_device.depth_read_lock.lock();
        for (size_t w = 0; w < KINECT_V2_CAMERA_PARAMS_RES_DEPTH_X; w++) {
            for (size_t h = 0; h < KINECT_V2_CAMERA_PARAMS_RES_DEPTH_Y; h++) {
                objs.at(h*KINECT_V2_CAMERA_PARAMS_RES_DEPTH_X+w)->position = sf::Vector3f(&kinect_device.dd[h*KINECT_V2_CAMERA_PARAMS_RES_DEPTH_X+w][0],kinect_device.dd[h*KINECT_V2_CAMERA_PARAMS_RES_DEPTH_X+w][1],kinect_device.dd[h*KINECT_V2_CAMERA_PARAMS_RES_DEPTH_X+w][2]);
            }
        }
            kinect_device.depth_read_lock.unlock();
        
        
        //draw objs
        for (size_t i = 0; i < objs.size(); i++) {
            objs.at(i)->update(delta.asSeconds());
            objs.at(i)->draw();
        }
        
         window.display();
        
        
        
        process_sfml_event(window);

    }
    
    
    return cleanup();

}


















