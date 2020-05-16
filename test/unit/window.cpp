#include <rmg/assert.hpp>
#include <rmg/window.hpp>
#include <gtest/gtest.h>

#include <GL/glew.h>
#include <GL/gl.h>

#include <cstdio>
#include <stdexcept>


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


class TestWindow1: public rmg::Window {
  public:
    TestWindow1(): rmg::Window() {}
    
    void update() override {
        float t = getTime();
        drawTriangle(1.778f, t*400);
        if(t > 0.1f) {
            #ifdef WIN32
            printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
            #else
            printf("\033[0;1;34mOpenGL Version:\033[0;1m %s\033[0m\n",
                   glGetString(GL_VERSION));
            #endif
            destroy();
        }
    }
};

TEST(Window, initAndDestroy) {
    EXPECT_EXIT(
        {
            auto window = new TestWindow1();
            rmg::Window::mainLoop();
            int err = window->getErrorCode();
            delete window;
            exit(err);
        },
        
        ::testing::ExitedWithCode(0),
        ".*"
    );
}




class TestWindow2: public rmg::Window {
  public:
    TestWindow2(): rmg::Window() {}
    
    void update() override {
        float t = getTime();
        drawTriangle(1.778f, t*-180);
        if(t > 0.1f) {
            throw std::runtime_error("Handled an exception\n");
        }
    }
};

TEST(Window, exceptionHandling) {
    EXPECT_EXIT(
        {
            auto window = new TestWindow2();
            rmg::Window::mainLoop();
            int err = window->getErrorCode();
            delete window;
            exit(err);
        },
        
        ::testing::ExitedWithCode(1),
        ".*"
    );
}




class TestWindow3: public rmg::Window {
  public:
    TestWindow3(): rmg::Window() {}
    
    void update() override {
        float t = getTime();
        rmg::Rect r;
        r = getContextSize();
        drawTriangle(r.x/(float)r.y, t*220);
        if(t > 0.1f) {
            static bool done = false;
            if(!done) {
                setWindowSize(400, 300);
                done = true;
            }
        }
        if(t > 0.2f) {
            static bool done = false;
            if(!done) {
                r = getContextSize();
                RMG_ASSERT(r.x == 400);
                RMG_ASSERT(r.y == 300);
                r = getWindowSize();
                RMG_ASSERT(r.x == 400);
                RMG_ASSERT(r.y == 300);
                done = true;
            }
        }
        if(t > 0.3f) {
            static bool done = false;
            if(!done) {
                setWindowSize(500, 400);
                done = true;
            }
        }
        if(t > 0.4f) {
            static bool done = false;
            if(!done) {
                r = getContextSize();
                RMG_ASSERT(r.x == 500);
                RMG_ASSERT(r.y == 400);
                r = getWindowSize();
                RMG_ASSERT(r.x == 500);
                RMG_ASSERT(r.y == 400);
                done = true;
            }
        }
        if(t > 0.5f) {
            destroy();
        }
    }
};

TEST(Window, setWindowSize) {
    EXPECT_EXIT(
        {
            auto window = new TestWindow3();
            rmg::Window::mainLoop();
            int err = window->getErrorCode();
            delete window;
            exit(err);
        },
        
        ::testing::ExitedWithCode(0),
        ".*"
    );
}




class TestWindow4: public rmg::Window {
  private:
    float t0;
    float rate;
    float duration;
    
  public:
    TestWindow4(float p, float w, float t): rmg::Window() {
        t0 = p;
        rate = w;
        duration = t;
    }
    
    void update() override {
        float t = getTime();
        drawTriangle(1.778f, t*100);
        if(t > duration) {
            destroy();
        }
    }
};

TEST(Window, DISABLED_multipleContextsInit) {
    EXPECT_EXIT(
        {
            auto window1 = new TestWindow4( 0.8f,  180, 0.4f);
            auto window2 = new TestWindow4(-0.4f, -230, 0.2f);
            auto window3 = new TestWindow4( 1.2f,  300, 0.6f);
            rmg::Window::mainLoop();
            int err = 0;
            if(window1->getErrorCode() != 0  ||
               window1->getErrorCode() != 0  ||
               window1->getErrorCode() != 0)
            {
                err = 1;
            }
            delete window1;
            delete window2;
            delete window3;
            exit(err);
        },
        
        ::testing::ExitedWithCode(0),
        ".*"
    );
}
