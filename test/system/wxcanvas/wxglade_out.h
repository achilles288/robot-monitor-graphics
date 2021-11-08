// -*- C++ -*-
//
// generated by wxGlade 0.9.4 on Sat Jul 18 20:22:40 2020
//
// Example for compiling a single file project under Linux using g++:
//  g++ MyApp.cpp $(wx-config --libs) $(wx-config --cxxflags) -o MyApp
//
// Example for compiling a multi file project under Linux using g++:
//  g++ main.cpp $(wx-config --libs) $(wx-config --cxxflags) -o MyApp Dialog1.cpp Frame1.cpp
//

#ifndef WXGLADE_OUT_H
#define WXGLADE_OUT_H

#include "myglcanvas.h"

#include <wx/wx.h>
#include <wx/image.h>

// begin wxGlade: ::dependencies
#include <wx/spinctrl.h>
// end wxGlade

// begin wxGlade: ::extracode
// end wxGlade


class MyFrame: public wxFrame {
public:
    // begin wxGlade: MyFrame::ids
    // end wxGlade

    MyFrame(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos=wxDefaultPosition, const wxSize& size=wxDefaultSize, long style=wxDEFAULT_FRAME_STYLE);

private:

protected:
    // begin wxGlade: MyFrame::attributes
    wxMenu* menuFile;
    wxMenuItem* itemOpenModel;
    wxMenuItem* itemOpenTexture;
    wxMenuItem* itemExit;
    wxMenu* menuEdit;
    wxMenuItem* itemCreateModel;
    wxMenuItem* itemCreateCube;
    wxMenuItem* itemCreateCylinder;
    wxMenuItem* itemCreateSphere;
    wxMenuItem* itemEditTexture;
    wxMenuItem* itemEditLighting;
    wxMenu* menuView;
    wxMenuItem* itemGridView;
    wxMenu* menuHelp;
    wxMenuItem* itemAbout;
    wxMenuBar* frame_menubar;
    wxBitmapButton* btnPan;
    wxBitmapButton* btnMove;
    wxBitmapButton* btnRotate;
    wxBitmapButton* btnScale;
    wxBitmapButton* btnTexture;
    wxBitmapButton* btnLighting;
    MyGLCanvas* canvas;
    wxBoxSizer* sizerEditorWidgets;
    wxSpinCtrlDouble* spin_ctrl_double_1;
    wxSpinCtrlDouble* spin_ctrl_double_2;
    wxSpinCtrlDouble* spin_ctrl_double_3;
    // end wxGlade

    DECLARE_EVENT_TABLE();

public:
    void onOpenModel(wxCommandEvent &event); // wxGlade: <event_handler>
    void onOpenTexture(wxCommandEvent &event); // wxGlade: <event_handler>
    void onExit(wxCommandEvent &event); // wxGlade: <event_handler>
    void onEditModel(wxCommandEvent &event); // wxGlade: <event_handler>
    void onCreateCube(wxCommandEvent &event); // wxGlade: <event_handler>
    void onCreateCylinder(wxCommandEvent &event); // wxGlade: <event_handler>
    void onCreateSphere(wxCommandEvent &event); // wxGlade: <event_handler>
    void onEditTranslation(wxCommandEvent &event); // wxGlade: <event_handler>
    void onEditRotation(wxCommandEvent &event); // wxGlade: <event_handler>
    void onEditScale(wxCommandEvent &event); // wxGlade: <event_handler>
    void onEditTexture(wxCommandEvent &event); // wxGlade: <event_handler>
    void onEditLighting(wxCommandEvent &event); // wxGlade: <event_handler>
    void onGridView(wxCommandEvent &event); // wxGlade: <event_handler>
    void onAbout(wxCommandEvent &event); // wxGlade: <event_handler>
    void onPan(wxCommandEvent &event); // wxGlade: <event_handler>
}; // wxGlade: end class


#endif // WXGLADE_OUT_H
