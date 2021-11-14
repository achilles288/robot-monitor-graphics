#include <rmg/window.hpp>

#include <rmg/config.h>
#include <rmg/cube.hpp>
#include <rmg/sphere.hpp>

using namespace rmg;


class MyWindow: public Window {
  private:
    Object3D *floor, *cube, *teapot;

  public:
    MyWindow() {
        setBackgroundColor(0.847f, 0.949f, 1.0f);
        // setCameraTranslation(0, 0, 0);
        // setCameraRotation(0, 0, 0);
        // setDirectionalLightAngles(0, 0);
        // setPerspectiveProjection(radian(40), 1.0f, 40.0f);
        setDirectionalLightColor(1, 1, 1, 2);

        floor = new Cube3D(this, 15, 15, 1);
        floor->setColor(0.3f, 0.6f, 0.5f);
        floor->setRoughness(0.7f);
        floor->setTranslation(10, 0, -0.5f);
        cube = new Cube3D(this, 3, 1, 1);
        cube->setColor(0.7f, 0.2f, 1.0f);
        cube->setRoughness(0.3f);
        cube->setTranslation(10, 0, 0.5f);
        teapot = new Object3D(this, RMG_RESOURCE_PATH "/models/teapot.obj");
        teapot->setColor(1.0f, 0, 0.3f);
        teapot->setRoughness(0.25f);
        teapot->setTranslation(10, 0, 1.1f);
        teapot->setScale(2.5f);
        addObject(floor);
        addObject(cube);
        addObject(teapot);
    }

    void update() override {}
};


int main() {
    Window* window = new MyWindow();
    window->setWindowSize(400, 240);
    Window::mainLoop();
    int err = 0;
    if(window->getErrorCode() != 0)
        err = 1;
    delete window;
    exit(err);
}
