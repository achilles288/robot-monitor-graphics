#ifndef __MYGLCANVAS_H__
#define __MYGLCANVAS_H__

#include <rmg/particle.hpp>
#include <rmg/object2d.hpp>
#include <rmg/object3d.hpp>
#include <rmg/wxcanvas.hpp>


class MyGLCanvas: public rmg::wxCanvas {
  private:
    rmg::Object3D *floor, *block1, *block2, *cylinder, *sphere;
    rmg::Object2D *sprite1, *sprite2;
    rmg::Particle3D *fire1, *fire2, *fire3;
    
  public:
    MyGLCanvas(wxWindow *parent);
    void update() override;
    
    void onMouseClick(const rmg::MouseEvent &event) override;
    void onKeyPress(const rmg::KeyboardEvent &event) override;
};

#endif
