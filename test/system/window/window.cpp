#include <rmg/window.hpp>

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>

#include <rmg/config.h>
#include <rmg/cube.hpp>
#include <rmg/cylinder.hpp>
#include <rmg/sphere.hpp>

using namespace rmg;


class TestWindow: public Window {
  private:
    Object3D *floor, *cube, *cylinder, *sphere, *teapot;
    Vec3 pos = Vec3(-13.3606f, 6.3603f, 9.8690f);
    Euler rot = Euler(0.0f, 0.5472f, -0.4640f);
    Euler lightAngles = Euler(0.0f, 0.87f, 0.52f);
    float fov = radian(45);
    bool keyW, keyA, keyS, keyD, keyF, keyG;
    bool shift = false;
    bool lightConfig = false;
    
  public:
    TestWindow() {
        keyW = keyA = keyS = keyD = keyF = keyG = false;
        setBackgroundColor(0.847f, 0.949f, 1.0f);
        setCameraTranslation(pos);
        setCameraRotation(rot);
        setDirectionalLightAngles(lightAngles);
        // setOrthographicProjection(8.0f, 1.0f, 30.0f);
        setPerspectiveProjection(fov, 1.0f, 30.0f);
        setDirectionalLightColor(1, 1, 1, 2);
        floor = new Cube3D(this, 15, 15, 1);
        floor->setColor(0.3f, 0.3f, 0.4f);
        floor->setRoughness(0.7f);
        floor->setTranslation(0, 0, -0.5f);
        cube = new Cube3D(this, 2, 3, 2);
        cube->setColor(1.0f, 0, 0);
        cube->setRoughness(0.5f);
        cube->setTranslation(-4, 0, 2);
        cylinder = new Cylinder3D(this, 2.4f, 3.0f);
        cylinder->setColor(1.0f, 0, 0.8f);
        cylinder->setRoughness(0.35f);
        cylinder->setTranslation(2, -3.464f, 3);
        sphere = new Sphere3D(this, 2.2f);
        sphere->setColor(1.0f, 1.0f, 0);
        sphere->setRoughness(0.7f);
        sphere->setTranslation(-0.5f, -0.5f, 3);
        teapot = new Object3D(this, RMG_RESOURCE_PATH "/models/teapot.obj");
        teapot->setColor(0, 1.0f, 0.3f);
        teapot->setRoughness(0.25f);
        teapot->setTranslation(2, 3.464f, 3);
        teapot->setScale(2.5f);
        addObject(floor);
        addObject(cube);
        addObject(cylinder);
        addObject(sphere);
        addObject(teapot);
    }
    
    void update() override {
        /*
        static int counter = 1;
        if(getTime() > 2.0f*counter) {
            counter++;
            printf("Time: %.2f  FPS: %.2f\n", getTime(), getFPS());
        }
        */
        static float t1 = 0;
        float t = getTime();
        float dt = t - t1;
        t1 = t;
        
        cube->setRotation(0.3f*t, -0.9f*t, -1.1f*t);
        cylinder->setRotation(-0.5f, -0.9f*t, 1.8f*t);
        sphere->setRotation(-1.0f, 0.8f*t, -1.2f*t);
        sphere->setTranslation(-0.5f, -0.5f, 3.1f+2*cos(3*t));
        teapot->setRotation(0, 0, 0.4f*t);
        
        bool move = false;
        if(keyW || keyA || keyS || keyD || keyF || keyG)
            move = true;
        
        if(move && lightConfig) {
            float rotSpeed = radian(45);
            if(keyW)
                lightAngles.pitch += rotSpeed*dt;
            if(keyA)
                lightAngles.yaw -= rotSpeed*dt;
            if(keyS)
                lightAngles.pitch -= rotSpeed*dt;
            if(keyD)
                lightAngles.yaw += rotSpeed*dt;
            lightAngles.pitch = std::clamp(lightAngles.pitch, -1.571f, 1.571f);
            setDirectionalLightAngles(lightAngles);
        }
        else if(move) {
            if(!shift) {
                float speed = 5.0f;
                Vec3 v0, v;
                if(keyW)
                    v0.x += speed;
                if(keyA)
                    v0.y += speed;
                if(keyS)
                    v0.x -= speed;
                if(keyD)
                    v0.y -= speed;
                if(keyF)
                    v0.z += speed;
                if(keyG)
                    v0.z -= speed;
                v.x = v0.x*cos(rot.yaw) - v0.y*sin(rot.yaw);
                v.y = v0.x*sin(rot.yaw) + v0.y*cos(rot.yaw);
                v.z = v0.z;
                pos = pos + v*dt;
                setCameraTranslation(pos);
            }
            else {
                float rotSpeed = radian(45);
                if(keyW)
                    rot.pitch -= rotSpeed*dt;
                if(keyA)
                    rot.yaw += rotSpeed*dt;
                if(keyS)
                    rot.pitch += rotSpeed*dt;
                if(keyD)
                    rot.yaw -= rotSpeed*dt;
                rot.pitch = std::clamp(rot.pitch, -1.571f, 1.571f);
                setCameraRotation(rot);
            }
        }
    }
    
    void onKeyPress(const KeyboardEvent& event) override {
        if(event.isShift())
            shift = true;
        
        if(event.getKeycode() == 'W')
            keyW = true;
        else if(event.getKeycode() == 'A')
            keyA = true;
        else if(event.getKeycode() == 'S')
            keyS = true;
        else if(event.getKeycode() == 'D')
            keyD = true;
        else if(event.getKeycode() == 'F')
            keyF = true;
        else if(event.getKeycode() == 'G')
            keyG = true;
        
        else if(event.getKeycode() == 'L') {
            lightConfig = !lightConfig;
        }
        
        else if(event.getKeycode() == 'P') {
            std::cout << "Position: " << pos << "  "
                      << "Rotation: " << rot << std::endl;
        }
        
        else if(event.getKeycode() == 'Q') {
            destroy();
        }
    }
    
    void onKeyRelease(const KeyboardEvent& event) override {
        if(!event.isShift())
            shift = false;
        
        if(event.getKeycode() == 'W')
            keyW = false;
        else if(event.getKeycode() == 'A')
            keyA = false;
        else if(event.getKeycode() == 'S')
            keyS = false;
        else if(event.getKeycode() == 'D')
            keyD = false;
        else if(event.getKeycode() == 'F')
            keyF = false;
        else if(event.getKeycode() == 'G')
            keyG = false;
    }
};


int main() {
    Window *window1 = new TestWindow();
    // Window *window2 = new TestWindow();
    printf("You can test mouse and keyboard events\n"
           "Press 'Q' to exit the program\n");
    Window::mainLoop();
    int err = 0;
    if(window1->getErrorCode() != 0)// || window2->getErrorCode() != 0)
        err = 1;
    delete window1;
    // delete window2;
    exit(err);
}
