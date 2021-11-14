#include <rmg/window.hpp>

#include <rmg/config.h>
#include <rmg/cube.hpp>
#include <rmg/sprite.hpp>

using namespace rmg;


class MyWindow: public Window {
  private:
    Object3D *floor, *teapot;
    Object2D *sprite;

  public:
    MyWindow() {
        setBackgroundColor(0.847f, 0.949f, 1.0f);
        setCameraTranslation(-1.7f, 7, 6);
        setCameraRotation(0.0f, 0.5472f, -1.309f);
        setDirectionalLightAngles(0.87f, 0.52f);
        setPerspectiveProjection(radian(45), 1.0f, 30.0f);
        setDirectionalLightColor(1, 1, 1, 2);

        // 3D solid objects
        floor = new Cube3D(this, 15, 15, 1);
        floor->setColor(0.3f, 0.6f, 0.5f);
        floor->setRoughness(0.7f);
        floor->setTranslation(0, 0, -0.5f);
        teapot = new Object3D(this, RMG_RESOURCE_PATH "/models/teapot.obj");
        teapot->setColor(1.0f, 0, 0.3f);
        teapot->setRoughness(0.25f);
        teapot->setTranslation(0, 0, 1.1f);
        teapot->setScale(2.5f);
        addObject(floor);
        addObject(teapot);

        // 2D overlay object
        sprite = new Sprite2D(this, RMG_RESOURCE_PATH "/icons/rmg-app.png");
        sprite->setAlignment(Alignment::BottomLeft);
        sprite->setTranslation(48, -48);
        addObject(sprite);
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
