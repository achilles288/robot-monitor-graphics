/**
 * @file wxcanvas.hpp
 * @brief RMG graphical context embedded in wxWidgets
 * 
 * Derived class of wxGLCanvas and rmg::Context. This class serves as a port
 * to wxWidgets GUI framework. This allows making 3D graphics and interactions
 * within GUI widgets.
 *
 * @copyright Copyright (c) 2020 Khant Kyaw Khaung
 * 
 * @license{This project is released under the MIT License.}
 */


#pragma once
#ifndef __RMG_WX_CANVAS_H__
#define __RMG_WX_CANVAS_H__

#ifndef RMG_WX_API
#ifdef _WIN32
#ifdef RMG_WX_EXPORT
#define RMG_WX_API __declspec(dllexport)
#else
#define RMG_WX_API __declspec(dllimport)
#endif
#else
#define RMG_WX_API
#endif
#endif


#include <rmg/context.hpp>

#include <wx/glcanvas.h>
#include <wx/timer.h>


namespace rmg {

/**
 * @brief Gets the default display attributes
 */
RMG_WX_API const wxGLAttributes &getWxGLDefaultAttributes();

/**
 * @brief RMG graphical context embedded in wxWidgets
 * 
 * Derived class of wxGLCanvas and rmg::Context. This class serves as a port
 * to wxWidgets GUI framework. This allows making 3D graphics and interactions
 * within GUI widgets.
 */
class RMG_WX_API wxCanvas: public wxGLCanvas, public Context {
  private:
    wxGLContext *context;
    wxTimer timer;
    
    void onWxPaint(wxPaintEvent& event);
    void onWxResize(wxSizeEvent& event);
    void onWxTimer(wxTimerEvent& event);
    void onWxMouseEnter(wxMouseEvent& event);
    void onWxMouseLeave(wxMouseEvent& event);
    void onWxMousePress(uint8_t button);
    void onWxMouseRelease(uint8_t button);
    void onWxMouseLeftPress(wxMouseEvent& event);
    void onWxMouseLeftRelease(wxMouseEvent& event);
    void onWxMouseMiddlePress(wxMouseEvent& event);
    void onWxMouseMiddleRelease(wxMouseEvent& event);
    void onWxMouseRightPress(wxMouseEvent& event);
    void onWxMouseRightRelease(wxMouseEvent& event);
    void onWxMouseMove(wxMouseEvent& event);
    void onWxMouseWheel(wxMouseEvent& event);
    void onWxKeyPress(wxKeyEvent& event);
    void onWxKeyRelease(wxKeyEvent& event);
    
  public:
    /**
     * @brief Default constructor
     */
    wxCanvas() = default;
    
    /**
     * @brief Creates a window with the given parameters
     * 
     * @param parent Pointer to a parent window
     * @param dispAttrs The display attributes
     * @param id Window identifier
     * @param pos Window position
     * @param size Window size
     * @param style Window style
     * @param name Window name
     * @param palette Palette for indexed colour (i.e. non WX_GL_RGBA) mode
     */
    wxCanvas(
        wxWindow *parent,
        const wxGLAttributes &dispAttrs = getWxGLDefaultAttributes(),
        wxWindowID id = wxID_ANY,
        const wxPoint &pos = wxDefaultPosition,
        const wxSize &size = wxDefaultSize,
        long style = 0,
        const wxString &name = "GLCanvas",
        const wxPalette &palette = wxNullPalette
    );
    
    /**
     * @brief Gets the running time of the context
     * 
     * @return Running time in seconds
     */
    float getTime() const override;
    
    /**
     * @brief Makes OpenGL rederer focuses on this context
     * 
     * Whenever functions regarding OpenGL resources is intended to be
     * called, the function needs to be called first especially when working
     * with multiple contexts.
     */
    void setCurrent() override;
    
    /**
     * @brief Flushes the drawn graphics by OpenGL onto the screen
     */
    void flush() override;
    
    /**
     * @brief Cleans up GPU resources
     */
    void destroy() override;
};

}

#endif
