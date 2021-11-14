#include <rmg/window.hpp>

#include <rmg/config.h>
#include <rmg/sprite.hpp>

using namespace rmg;


class MyWindow: public Window {
  private:
    Sprite2D *robot, *wine;

  public:
    MyWindow() {
        setBackgroundColor(0.847f, 0.949f, 1.0f);

        robot = new Sprite2D(this, RMG_RESOURCE_PATH "/icons/rmg-app.png");
        robot->setTranslation(-20, 0);
        robot->setSize(100, 100);
        robot->setRotation(-0.57f);

        wine = new Sprite2D(this, RMG_RESOURCE_PATH "/test/wine.png");
        wine->setAlignment(Alignment::BottomLeft);
        wine->setTranslation(60, -50);

        addObject(robot);
        addObject(wine);
    }

    void update() override {
        float t = getTime();
        robot->setRotation(0.4f*t);
        wine->setTranslation(60, -96+32*cos(t));
    }
};


int main() {
    Window* window = new MyWindow();
    window->setWindowSize(400, 240);
    Window::mainLoop();
    int err = 0;
    if (window->getErrorCode() != 0)
        err = 1;
    delete window;
    exit(err);
}
