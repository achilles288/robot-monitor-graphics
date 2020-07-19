#include "myglcanvas.h"

#include <cstdio>

#include <rmg/cube.hpp>
#include <rmg/cylinder.hpp>
#include <rmg/sphere.hpp>

using rmg::radian;
using rmg::Vec3;
using rmg::Euler;
using rmg::Cube3D;
using rmg::Cylinder3D;
using rmg::Sphere3D;


MyGLCanvas::MyGLCanvas(wxWindow *parent)
       :rmg::wxCanvas(parent)
{
    Vec3 pos = Vec3(-13.3606f, 6.3603f, 9.8690f);
    Euler rot = Euler(0.0f, 0.5472f, -0.4640f);
    Euler lightAngles = Euler(0.0f, radian(60), radian(30));
    float fov = radian(45);
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
    block1 = new Cube3D(this, 2, 3, 2);
    block1->setColor(1.0f, 0, 0);
    block1->setRoughness(0.2f);
    block1->setTranslation(-4, 0, 2);
    block2 = new Cube3D(this, 2.5f, 2.2f, 4.1f);
    block2->setColor(0, 1.0f, 0);
    block2->setRoughness(0.3f);
    block2->setTranslation(2, 3.464f, 3);
    cylinder = new Cylinder3D(this, 2.4f, 3.0f);
    cylinder->setColor(1.0f, 0, 1.0f);
    cylinder->setRoughness(0.4f);
    cylinder->setTranslation(2, -3.464f, 3);
    sphere = new Sphere3D(this, 2.2f);
    sphere->setColor(1.0f, 1.0f, 0);
    sphere->setRoughness(0.6f);
    sphere->setTranslation(-0.5f, -0.5f, 3);
    addObject(floor);
    addObject(block1);
    addObject(block2);
    addObject(cylinder);
    addObject(sphere);
}


void MyGLCanvas::update() {
    float t = getTime();
    block1->setRotation(0.3f*t, 0.7f*t, 1.5f*t);
    block2->setRotation(0.6f*t, 1.7f*t, 0.8f*t);
    cylinder->setRotation(0, 0.9f*t, 1.8f*t);
    sphere->setTranslation(-0.5f, -0.5f, 3+1.5f*cos(3*t));
}


void MyGLCanvas::onMouseClick(const rmg::MouseEvent &event) {
    printf("%d %d%d%d %d %d\n", (int)event.getButton(), event.isLeftPressed(),
     event.isMiddlePressed(), event.isRightPressed(), event.getX(), event.getY());
}

void MyGLCanvas::onKeyPress(const rmg::KeyboardEvent &event) {
    printf("%d %d%d%d\n", event.getKeycode(), event.isCtrl(), event.isAlt(),
           event.isShift());
}
