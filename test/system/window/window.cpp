#include <rmg/window.hpp>

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>

#include <rmg/config.h>
#include <rmg/cube.hpp>
#include <rmg/cylinder.hpp>
#include <rmg/line3d.hpp>
#include <rmg/particle.hpp>
#include <rmg/sphere.hpp>
#include <rmg/sprite.hpp>

#include "../../testconf.h"

using namespace rmg;


static float clip(float n, float lower, float upper) {
    n = (n > lower) * n + !(n > lower) * lower;
    return (n < upper) * n + !(n < upper) * upper;
}


class TestWindow: public Window {
  private:
    Object3D *floor, *cube1, *cube2, *cylinder, *sphere, *teapot;
    Sprite2D *sprite1, *sprite2, *sprite3;
    Particle3D *fire1, *fire2, *fire3;
    Line3D *lines[8];
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
        
        // 3D solid objects
        floor = new Cube3D(this, 15, 15, 1);
        floor->setColor(0.3f, 0.3f, 0.4f);
        floor->setRoughness(0.7f);
        floor->setTranslation(0, 0, -0.5f);
        cube1 = new Cube3D(this, 2, 3, 2);
        cube1->setColor(1.0f, 0, 0);
        cube1->setRoughness(0.5f);
        cube1->setTranslation(-4, 0, 2);
        cube2 = new Object3D(*cube1);
        cube2->setColor(0, 0, 1.0f);
        cube2->setTranslation(-5, 5, 2);
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
        teapot->setScale(2.5f, 2, 2.5f);
        addObject(floor);
        addObject(cube1);
        addObject(cube2);
        addObject(cylinder);
        addObject(sphere);
        addObject(teapot);
        
        // 2D overlay objects
        sprite1 = new Sprite2D(this, RMG_RESOURCE_PATH "/icons/rmg-app.png");
        sprite1->setAlignment(Alignment::BottomLeft);
        sprite1->setTranslation(48, -48);
        sprite2 = new Sprite2D(this, RMG_RESOURCE_PATH "/test/wine.png");
        sprite2->setAlignment(Alignment::BottomRight);
        sprite2->setTranslation(-48, -48);
        sprite3 = new Sprite2D(*sprite2);
        sprite3->setTranslation(-64, -32);
        addObject(sprite1);
        addObject(sprite3);
        addObject(sprite2);
        
        // Particles
        fire1 = new Particle3D(this, RMG_RESOURCE_PATH "/test/fire.tif");
        fire1->setSize(0.4f, 0.6f);
        fire1->setTranslation(-5, -3, 1);
        fire2 = new Particle3D(*fire1);
        fire2->setTranslation(-4, -5, 2);
        fire3 = new Particle3D(*fire1);
        fire3->setSize(0.5f, 0.8f);
        fire3->setTranslation(-3, -4, 1.5f);
        addObject(fire1);
        addObject(fire2);
        addObject(fire3);
        
        // 3D lines
        for(int i=0; i<8; i++) {
            lines[i] = new Line3D(this, 0.1f, Color(0,0,0));
            addObject(lines[i]);
        }
        lines[0]->setPoint1(-7.5f, -7.5f, 0);
        lines[1]->setPoint1( 7.5f, -7.5f, 0);
        lines[2]->setPoint1( 7.5f,  7.5f, 0);
        lines[3]->setPoint1(-7.5f,  7.5f, 0);
        lines[0]->setPoint2(-7.5f, -7.5f, 7.5f);
        lines[1]->setPoint2( 7.5f, -7.5f, 7.5f);
        lines[2]->setPoint2( 7.5f,  7.5f, 7.5f);
        lines[3]->setPoint2(-7.5f,  7.5f, 7.5f);
        
        lines[4]->setPoint1(-7.5f, -7.5f, 7.5f);
        lines[5]->setPoint1( 7.5f, -7.5f, 7.5f);
        lines[6]->setPoint1( 7.5f,  7.5f, 7.5f);
        lines[7]->setPoint1(-7.5f,  7.5f, 7.5f);
        lines[7]->setPoint2(-7.5f, -7.5f, 7.5f);
        lines[4]->setPoint2( 7.5f, -7.5f, 7.5f);
        lines[5]->setPoint2( 7.5f,  7.5f, 7.5f);
        lines[6]->setPoint2(-7.5f,  7.5f, 7.5f);
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
        
        cube1->setRotation(0.3f*t, -0.9f*t, -1.1f*t);
        cylinder->setRotation(-0.5f, -0.9f*t, 1.8f*t);
        sphere->setRotation(-1.0f, 0.8f*t, -1.2f*t);
        sphere->setTranslation(-0.5f, -0.5f, 3.1f+2*cos(3*t));
        teapot->setRotation(0, 0, 0.4f*t);
        sprite2->setRotation(0.45f*t);
        
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
            lightAngles.pitch = clip(lightAngles.pitch, -1.571f, 1.571f);
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
                rot.pitch = clip(rot.pitch, -1.571f, 1.571f);
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
    Window::mainLoop();
    int err = 0;
    if(window1->getErrorCode() != 0)// || window2->getErrorCode() != 0)
        err = 1;
    delete window1;
    // delete window2;
    exit(err);
}
