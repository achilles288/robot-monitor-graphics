#ifndef __MYGLCANVAS_H__
#define __MYGLCANVAS_H__

#include <rmg/object3d.hpp>
#include <rmg/wxcanvas.hpp>


class MyGLCanvas: public rmg::wxCanvas {
  private:
    rmg::Object3D *floor, *block1, *block2, *cylinder, *sphere;
    
  public:
    MyGLCanvas(wxWindow *parent);
    void update() override;
    
    void onMouseClick(const rmg::MouseEvent &event) override;
    void onKeyPress(const rmg::KeyboardEvent &event) override;
};

#endif
