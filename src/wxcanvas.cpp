/**
 * @file wxcanvas.cpp
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


#include "rmg/wxcanvas.hpp"

#include <wx/dcclient.h>
#include <wx/time.h>


namespace rmg {

/**
 * @brief Gets the default display attributes
 */
const wxGLAttributes &getWxGLDefaultAttributes() {
    static wxGLAttributes dispAttrs;
    dispAttrs = wxGLAttributes();
    dispAttrs
        .PlatformDefaults()
        .DoubleBuffer()
        .Depth(16)
        .Samplers(4)
    .EndList();
    return dispAttrs;
}

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
wxCanvas::wxCanvas(wxWindow *parent, const wxGLAttributes &dispAttrs,
                   wxWindowID id, const wxPoint &pos, const wxSize &size,
                   long style, const wxString &name, const wxPalette &palette)
          
         :wxGLCanvas(parent, dispAttrs, id, pos, size, style, name, palette)
{
    wxGLContextAttrs ctxAttrs;
    ctxAttrs
        .CoreProfile()
        .OGLVersion(3, 2)
        .Robust()
        .ResetIsolation()
    .EndList();
    context = new wxGLContext(this, NULL, &ctxAttrs);
    if(!context->IsOK()) {
        wxLogMessage("error: Requires OpenGL 3.2. "
                     "Please check if you have the latest GPU driver.");
        delete context;
        context = nullptr;
        return;
    }
    
    timer.SetOwner(this);
    Connect(
        wxEVT_TIMER,
        wxTimerEventHandler(wxCanvas::onWxTimer),
        NULL,
        this
    );
    timer.Start(16);
    
    Connect(
        wxEVT_PAINT,
        wxPaintEventHandler(wxCanvas::onWxPaint),
        NULL,
        this
    );
    Connect(
        wxEVT_SIZE,
        wxSizeEventHandler(wxCanvas::onWxResize),
        NULL,
        this
    );
    Connect(
        wxEVT_ENTER_WINDOW,
        wxMouseEventHandler(wxCanvas::onWxMouseEnter),
        NULL,
        this
    );
    Connect(
        wxEVT_LEAVE_WINDOW,
        wxMouseEventHandler(wxCanvas::onWxMouseLeave),
        NULL,
        this
    );
    Connect(
        wxEVT_LEFT_DOWN,
        wxMouseEventHandler(wxCanvas::onWxMouseLeftPress),
        NULL,
        this
    );
    Connect(
        wxEVT_LEFT_UP,
        wxMouseEventHandler(wxCanvas::onWxMouseLeftRelease),
        NULL,
        this
    );
    Connect(
        wxEVT_MIDDLE_DOWN,
        wxMouseEventHandler(wxCanvas::onWxMouseMiddlePress),
        NULL,
        this
    );
    Connect(
        wxEVT_MIDDLE_UP,
        wxMouseEventHandler(wxCanvas::onWxMouseMiddleRelease),
        NULL,
        this
    );
    Connect(
        wxEVT_RIGHT_DOWN,
        wxMouseEventHandler(wxCanvas::onWxMouseRightPress),
        NULL,
        this
    );
    Connect(
        wxEVT_RIGHT_UP,
        wxMouseEventHandler(wxCanvas::onWxMouseRightRelease),
        NULL,
        this
    );
    Connect(
        wxEVT_MOTION,
        wxMouseEventHandler(wxCanvas::onWxMouseMove),
        NULL,
        this
    );
    Connect(
        wxEVT_MOUSEWHEEL,
        wxMouseEventHandler(wxCanvas::onWxMouseWheel),
        NULL,
        this
    );
    Connect(
        wxEVT_KEY_DOWN,
        wxKeyEventHandler(wxCanvas::onWxKeyPress),
        NULL,
        this
    );
    Connect(
        wxEVT_KEY_UP,
        wxKeyEventHandler(wxCanvas::onWxKeyRelease),
        NULL,
        this
    );
}

/**
 * @brief Cleans up context resources
 */
void wxCanvas::destroy() {
    if(isDestroyed())
        return;
    Context::destroy();
    Context *current = getCurrent();
    setCurrent();
    if(context != nullptr)
        delete context;
    current->setCurrent();
}




void wxCanvas::onWxPaint(wxPaintEvent& event) {
    if(!isDestroyed())
        render();
}

void wxCanvas::onWxResize(wxSizeEvent& event) {
    wxSize size = event.GetSize();
    setContextSize(size.GetWidth(), size.GetHeight());
}

void wxCanvas::onWxTimer(wxTimerEvent& event) { Refresh(); }

void wxCanvas::onWxMouseEnter(wxMouseEvent& event) {
    mouseEvent.mouseStates |= RMG_MOUSE_STATE_ENTRY;
    onMouseEntry(mouseEvent);
}

void wxCanvas::onWxMouseLeave(wxMouseEvent& event) {
    mouseEvent.mouseStates ^= mouseEvent.mouseStates & RMG_MOUSE_STATE_ENTRY;
    onMouseEntry(mouseEvent);
}

void wxCanvas::onWxMousePress(uint8_t button) {
    if(button == RMG_MOUSE_STATE_LEFT)
        mouseEvent.button = MouseButton::Left;
    else if(button == RMG_MOUSE_STATE_MIDDLE)
        mouseEvent.button = MouseButton::Middle;
    else if(button == RMG_MOUSE_STATE_RIGHT)
        mouseEvent.button = MouseButton::Right;
    
    mouseEvent.mouseStates |= button;
    mouseEvent.xp = mouseEvent.x;
    mouseEvent.yp = mouseEvent.y;
    onMousePress(mouseEvent);
    mouseEvent.button = MouseButton::None;
    SetFocusFromKbd();
}

void wxCanvas::onWxMouseRelease(uint8_t button) {
    if(button == RMG_MOUSE_STATE_LEFT)
        mouseEvent.button = MouseButton::Left;
    else if(button == RMG_MOUSE_STATE_MIDDLE)
        mouseEvent.button = MouseButton::Middle;
    else if(button == RMG_MOUSE_STATE_RIGHT)
        mouseEvent.button = MouseButton::Right;
    
    int16_t dx = mouseEvent.x - mouseEvent.xp;
    int16_t dy = mouseEvent.y - mouseEvent.yp;
    if(abs(dx) < 5 && abs(dy) < 5)
        onMouseClick(mouseEvent);
    mouseEvent.mouseStates ^= mouseEvent.mouseStates & button;
    onMouseRelease(mouseEvent);
    mouseEvent.button = MouseButton::None;
}

void wxCanvas::onWxMouseLeftPress(wxMouseEvent& event) {
    onWxMousePress(RMG_MOUSE_STATE_LEFT);
}

void wxCanvas::onWxMouseLeftRelease(wxMouseEvent& event) {
    onWxMouseRelease(RMG_MOUSE_STATE_LEFT);
}

void wxCanvas::onWxMouseMiddlePress(wxMouseEvent& event) {
    onWxMousePress(RMG_MOUSE_STATE_MIDDLE);
}

void wxCanvas::onWxMouseMiddleRelease(wxMouseEvent& event) {
    onWxMouseRelease(RMG_MOUSE_STATE_MIDDLE);
}

void wxCanvas::onWxMouseRightPress(wxMouseEvent& event) {
    onWxMousePress(RMG_MOUSE_STATE_RIGHT);
}

void wxCanvas::onWxMouseRightRelease(wxMouseEvent& event) {
    onWxMouseRelease(RMG_MOUSE_STATE_RIGHT);
}

void wxCanvas::onWxMouseMove(wxMouseEvent& event) {
    wxClientDC dc(this);
    wxPoint point = event.GetLogicalPosition(dc);
    mouseEvent.dx = point.x - mouseEvent.x;
    mouseEvent.dy = point.y - mouseEvent.y;
    mouseEvent.x = point.x;
    mouseEvent.y = point.y;
    onMouseMove(mouseEvent);
}

void wxCanvas::onWxMouseWheel(wxMouseEvent& event) {
    if(event.GetWheelAxis() == wxMOUSE_WHEEL_VERTICAL) {
        mouseEvent.scroll = (int8_t) event.GetWheelDelta();
        onMouseWheel(mouseEvent);
    }
}

static int16_t wxKeycodeToRMGKeycode(int16_t keycode);

void wxCanvas::onWxKeyPress(wxKeyEvent& event) {    
    uint8_t mask = 0b0000;
    int16_t rkey = wxKeycodeToRMGKeycode(event.GetKeyCode());
    if(rkey == RMG_KEY_CTRL)
        mask = RMG_KEY_STATE_CTRL;
    else if(rkey == RMG_KEY_ALT)
        mask = RMG_KEY_STATE_ALT;
    else if(rkey == RMG_KEY_SHIFT)
        mask = RMG_KEY_STATE_SHIFT;
    mouseEvent.keycode = rkey;
    mouseEvent.keyStates |= mask;
    onKeyPress(*((rmg::KeyboardEvent*)(&mouseEvent)));
}

void wxCanvas::onWxKeyRelease(wxKeyEvent& event) {
    uint8_t mask = 0b0000;
    int16_t rkey = wxKeycodeToRMGKeycode((int16_t)event.GetKeyCode());
    if(rkey == RMG_KEY_CTRL)
        mask = RMG_KEY_STATE_CTRL;
    else if(rkey == RMG_KEY_ALT)
        mask = RMG_KEY_STATE_ALT;
    else if(rkey == RMG_KEY_SHIFT)
        mask = RMG_KEY_STATE_SHIFT;
    mouseEvent.keycode = rkey;
    mouseEvent.keyStates ^= mouseEvent.keyStates & mask;
    onKeyRelease(*((rmg::KeyboardEvent*)(&mouseEvent)));
}




/**
 * @brief Gets the running time of the context
 * 
 * @return Running time in seconds
 */
float wxCanvas::getTime() const {
    static bool startTimeCounted = false;
    static wxLongLong startTime = 0;
    if(!startTimeCounted) {
        startTime = wxGetLocalTimeMillis();
        startTimeCounted = true;
    }
    return ((float) (wxGetLocalTimeMillis() - startTime).GetLo()) / 1000.0f;
}

/**
 * @brief Makes OpenGL rederer focuses on this context
 * 
 * Whenever functions regarding OpenGL resources is intended to be
 * called, the function needs to be called first especially when working
 * with multiple contexts.
 */
void wxCanvas::setCurrent() {
    Context::setCurrent();
    if(context != nullptr) {
        SetCurrent(*context);
        wxPaintDC(this);
    }
}

/**
 * @brief Flushes the drawn graphics by OpenGL onto the screen
 */
void wxCanvas::flush() {
    glFlush();
    SwapBuffers();
}




#include <map>

static int16_t wxKeycodeToRMGKeycode(int16_t keycode) {
    if((keycode >= '0' && keycode <= '9') ||
       (keycode >= 'A' && keycode <= 'Z'))
    {
        return keycode;
    }
    
    if(keycode >= WXK_NUMPAD0 && keycode <= WXK_F12)
    {
        return keycode + RMG_KEY_NUM_0 - WXK_NUMPAD0;
    }
    
    static const std::map<int16_t, int16_t> table = {
        {WXK_BACK,            RMG_KEY_BACKSPACE},
        {WXK_TAB,             RMG_KEY_TAB},
        {WXK_RETURN,          RMG_KEY_ENTER},
        {WXK_ESCAPE,          RMG_KEY_ESCAPE},
        {WXK_SPACE,           RMG_KEY_SPACE},
        {WXK_DELETE,          RMG_KEY_DELETE},
        {WXK_SHIFT,           RMG_KEY_SHIFT},
        {WXK_ALT,             RMG_KEY_ALT},
        {WXK_RAW_CONTROL,     RMG_KEY_CTRL},
        {WXK_CAPITAL,         RMG_KEY_CAPS_LOCK},
        {WXK_END,             RMG_KEY_END},
        {WXK_HOME,            RMG_KEY_HOME},
        {WXK_LEFT,            RMG_KEY_ARROW_LEFT},
        {WXK_UP,              RMG_KEY_ARROW_UP},
        {WXK_RIGHT,           RMG_KEY_ARROW_RIGHT},
        {WXK_DOWN,            RMG_KEY_ARROW_DOWN},
        {WXK_INSERT,          RMG_KEY_INSERT},
        {WXK_NUMLOCK,         RMG_KEY_NUM_LOCK},
        {WXK_PAGEUP,          RMG_KEY_PAGE_UP},
        {WXK_PAGEDOWN,        RMG_KEY_PAGE_DOWN},
        {WXK_NUMPAD_ENTER,    RMG_KEY_ENTER},
        {WXK_NUMPAD_MULTIPLY, RMG_KEY_NUM_MULTIPLY},
        {WXK_NUMPAD_ADD,      RMG_KEY_NUM_ADD},
        {WXK_NUMPAD_SUBTRACT, RMG_KEY_NUM_SUBTRACT},
        {WXK_NUMPAD_DECIMAL,  RMG_KEY_NUM_DECIMAL},
        {WXK_NUMPAD_DIVIDE,   RMG_KEY_NUM_DIVIDE},
        {';',                 RMG_KEY_COLON},
        {'=',                 RMG_KEY_EQUAL},
        {',',                 RMG_KEY_COMMA},
        {'-',                 RMG_KEY_DASH},
        {'.',                 RMG_KEY_DOT},
        {'/',                 RMG_KEY_SLASH},
        {'`',                 RMG_KEY_BACKQUOTE},
        {'[',                 RMG_KEY_OPEN_BRACKET},
        {'\\',                RMG_KEY_BACKSLASH},
        {']',                 RMG_KEY_CLOSE_BRACKET},
        {'\'',                RMG_KEY_QUOTE}
    };
    auto it = table.find(keycode);
    if(it != table.end())
        return it->second;
    return -1;
}

}
