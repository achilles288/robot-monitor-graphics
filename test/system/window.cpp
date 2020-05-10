#include <rmg/window.hpp>

#include <cstdio>
#include <cstring>


static void drawTriangle(float ratio, float t) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotatef(t, 0.f, 0.f, 1.f);
    glBegin(GL_TRIANGLES);
    glColor3f(1.f, 0.f, 0.f);
    glVertex3f(-0.6f, -0.4f, 0.f);
    glColor3f(0.f, 1.f, 0.f);
    glVertex3f(0.6f, -0.4f, 0.f);
    glColor3f(0.f, 0.f, 1.f);
    glVertex3f(0.f, 0.6f, 0.f);
    glEnd();
}


class TestWindow: public rmg::Window {
  private:
    float t;
    
    char* buttonToString(const rmg::MouseEvent &event) {
        static char str[16];
        memset(str, '\0', 16);
        if(event.getButton() == rmg::MouseButton::Left)
            sprintf(str, "left");
        else if(event.getButton() == rmg::MouseButton::Middle)
            sprintf(str, "middle");
        else if(event.getButton() == rmg::MouseButton::Right)
            sprintf(str, "right");
        else
            sprintf(str, "NULL");
        return str;
    }
    
    char* mouseModifiersToString(const rmg::MouseEvent &event) {
        static char str[8];
        memset(str, '\0', 8);
        sprintf(
            str,
            "%d%d%d%d%d%d%d",
            event.isCtrl(),
            event.isAlt(),
            event.isShift(),
            event.isLeftPressed(),
            event.isMiddlePressed(),
            event.isRightPressed(),
            event.isEntered()
        );
        return str;
    }
    
  public:
    TestWindow(): rmg::Window() {
        setWindowName("Window Event Testing");
        setWindowSize(300, 300);
        t = 0;
    }
    
    void update() override {
        rmg::Rect r = getContextSize();
        drawTriangle(r.x/(float)r.y, t);
    }
    
    void onMouseClick(const rmg::MouseEvent &event) override {
        char* button = buttonToString(event);
        char* mod = mouseModifiersToString(event);
        printf("Window%ld clicked - x:%d y:%d button:%s modifiers:%s\n",
               getID(), event.getX(), event.getY(), button, mod);
    }
    
    void onMousePress(const rmg::MouseEvent &event) override {
        char* button = buttonToString(event);
        char* mod = mouseModifiersToString(event);
        printf("Window%ld pressed - x:%d y:%d button:%s modifiers:%s\n",
               getID(), event.getX(), event.getY(), button, mod);
    }
    
    void onMouseRelease(const rmg::MouseEvent &event) override {
        char* button = buttonToString(event);
        char* mod = mouseModifiersToString(event);
        printf("Window%ld released - x:%d y:%d button:%s modifiers:%s\n",
               getID(), event.getX(), event.getY(), button, mod);
    }
    
    void onMouseMove(const rmg::MouseEvent &event) override {
        if(!event.isShift())
            return;
        t += (event.getDiffX()*0.5f);
        char* button = buttonToString(event);
        char* mod = mouseModifiersToString(event);
        printf("Window%ld moved - x:%d y:%d dx:%d dy:%d "
               "button:%s modifiers:%s\n",
               getID(), event.getX(), event.getY(),
               event.getDiffX(), event.getDiffY(), button, mod);
    }
    
    void onMouseWheel(const rmg::MouseEvent &event) override {
        char* button = buttonToString(event);
        char* mod = mouseModifiersToString(event);
        printf("Window%ld wheel - x:%d y:%d scroll:%d "
               "button:%s modifiers:%s\n",
               getID(), event.getX(), event.getY(), event.getScroll(),
               button, mod);
    }
    
    void onMouseEntry(const rmg::MouseEvent &event) override {
        char* button = buttonToString(event);
        char* mod = mouseModifiersToString(event);
        printf("Window%ld entry - x:%d y:%d button:%s modifiers:%s\n",
               getID(), event.getX(), event.getY(), button, mod);
    }
    
    void onKeyboard(const rmg::KeyboardEvent &event) override {
        if(event.getKeycode() == 'Q') {
            printf("Exit\n");
            Context::destroyAll();
            return;
        }
        printf("Window%ld keyboard - key:%c(%d) modifiers:%d%d%d\n",
               getID(), event.getKeycode(), event.getKeycode(),
               event.isCtrl(), event.isAlt(), event.isShift());
    }
};


int main() {
    auto window1 = new TestWindow();
    //auto window2 = new TestWindow();
    printf("You can test mouse and keyboard events\n"
           "Press 'Q' to exit the program\n");
    rmg::Window::mainLoop();
    int err = 0;
    if(window1->getErrorCode() != 0)// || window2->getErrorCode() != 0)
        err = 1;
    delete window1;
    //delete window2;
    exit(err);
}
