/**************************************************************************\
 *
 *  Copyright (C) 1998-1999 by Systems in Motion.  All rights reserved.
 *
 *  This file is part of the Coin library.
 *
 *  This file may be distributed under the terms of the Q Public License
 *  as defined by Troll Tech AS of Norway and appearing in the file
 *  LICENSE.QPL included in the packaging of this file.
 *
 *  If you want to use Coin in applications not covered by licenses
 *  compatible with the QPL, you can contact SIM to aquire a
 *  Professional Edition license for Coin.
 *
 *  Systems in Motion AS, Prof. Brochs gate 6, N-7030 Trondheim, NORWAY
 *  http://www.sim.no/ sales@sim.no Voice: +47 22114160 Fax: +47 67172912
 *
\**************************************************************************/

#ifndef SOWIN_GLWIDGET_H
#define SOWIN_GLWIDGET_H

#include <Inventor/SbBasic.h>

#include <windows.h>
#include <Inventor/Win/SoWinBasic.h>
#include <Inventor/Win/SoWinComponent.h>

class SoWinGLArea;

enum GLModes {        // remove the GLX ones?
  SO_GL_RGB      = 0x01, SO_GLX_RGB      = SO_GL_RGB,
  SO_GL_DOUBLE   = 0x02, SO_GLX_DOUBLE   = SO_GL_DOUBLE,
  SO_GL_ZBUFFER  = 0x04, SO_GLX_ZBUFFER  = SO_GL_ZBUFFER,
  SO_GL_OVERLAY  = 0x08, SO_GLX_OVERLAY  = SO_GL_OVERLAY,
  SO_GL_STEREO   = 0x10, SO_GLX_STEREO   = SO_GL_STEREO
};

// *************************************************************************

class SOWIN_DLL_EXPORT SoWinGLWidget : public SoWinComponent {
    typedef SoWinComponent inherited;
protected:    
    // Subclasses can pass in a bitwise OR specifying the GL modes
    // (e.g. SO_GLX_RGB | SO_GLX_DOUBLE | SO_GLX_ZBUFFER | SO_GLX_OVERLAY)
    // If build is FALSE, this will not build its widget tree until
    // buildWidget() is explicity called; else, buildWidget() is called here.
    SoWinGLWidget(
	    HWND parent = NULL,
	    const char *name = NULL, 
	    SbBool embed = TRUE, 
	    int glModes = SO_GLX_RGB|SO_GL_DOUBLE, //SO_GLX_RGB
	    SbBool build = TRUE);

    virtual ~SoWinGLWidget( void );

public:
    HWND getNormalWindow( void );
    HWND getOverlayWindow( void );

    HWND getNormalWidget( void );
    HWND getOverlayWidget( void );

    HDC getNormalDC( void );
    HDC getOverlayDC( void );

    HGLRC getNormalContext( void );
    HGLRC getOverlayContext( void );

    void setStealFocus( SbBool doStealFocus );

    virtual void setNormalVisual( PIXELFORMATDESCRIPTOR *vis );
    PIXELFORMATDESCRIPTOR * getNormalVisual( void );

    virtual void setOverlayVisual( PIXELFORMATDESCRIPTOR *vis );    // no effect
    PIXELFORMATDESCRIPTOR * getOverlayVisual( void );

    // Specify exactly what the pixel format should be.
    // These methods take a pixel format index, where the ones immediately
    // above take a ptr to a PIXELFORMATDESCRIPTOR struct.  These methods
    // allow an application to specify a pixel format that has extended
    // attributes that can't be specified in a PFD struct.
    // We don't have separate calls for normal and overlay because the
    // overlay is not a separate window on Win32 machines.
    // The specified format *must* support OpenGL and drawing to a window.
    //
    virtual void setPixelFormat( int format );
    int getPixelFormat( void );

    void setDoubleBuffer( SbBool set );
    SbBool isDoubleBuffer( void );
    
    void setBorder( SbBool set );   // show/hide 3 pixel border ( default = off )
    int getBorderSize( void );
    SbBool isBorder( void ) const;
    
    // Inventor 2.1 changed the behavior of double buffered windows to
    // redraw temporary to the front buffer when an expose event is received
    // or when a new sceneGraph() is set on an SoXtRenderArea. This does not
    // apply for general interactive rendering. The idea is that it is 
    // better to see something redraw (especially if it is slow) than
    // to see garbage in the window (in the expose case) or an old invalid 
    // scene graph (in the SoXtRenderArea::setSceneGraph() case).
    //
    // This API enables you to turn this functionality OFF if for some reason
    // you are unable to prevent repeated expose from causing a redraw (which
    // is bad and should be fixed, as it gets worse for large scenes). 
    // This will be the case for example if you can't create a pulldown 
    // menu in the popup planes.
    //
    // NOTE: this api might be removed in some future releases and is only
    // intended as a porting help for Inventor 2.0 to 2.1
    //
    void setDrawToFrontBufferEnable( SbBool enable );
    SbBool isDrawToFrontBufferEnable( void ) const;

    void setCursor( HCURSOR newCursor );
    HCURSOR getCursor( void ); // coin spesific
protected:
    // subclasses MUST redefine redraw() to draw in the normal bit planes.
    // redrawOverlay() should be defined if the overlay planes are being
    // used, and processEvent() should be defined if X events are being 
    // received (see eventMask).

/*  virtual void redraw( void ) = 0;
    virtual void redrawOverlay( void );
    virtual void processEvent( MSG * anymsg );*/
    void redraw( void );
    void redrawOverlay( void );
    virtual void processEvent( MSG * msg );

    virtual void initGraphic( void );
    virtual void initOverlayGraphic( void );
    virtual void sizeChanged( const SbVec2s newSize );
    virtual void widgetChanged( HWND newWidget );
    
    // sets/gets the size of the glx widget(s) - Note this size could be
    // different from the SoWinComponent::getSize() method which return
    // the size of the component, not necessary the same as the glx widget
    // window (because of extra stuff like the decoration in the viewers).
    void setGlxSize( SbVec2s newSize );
    const SbVec2s getGlxSize( void ) const;
    const SbVec2s getGLSize( void ) const;
    
    static void eventHandler( HWND, SoWinGLWidget *, MSG *, BOOL *);

    void setStereoBuffer( SbBool set );
    SbBool isStereoBuffer( void );
    SbBool isRGBMode( void );
    
    // returns the display lists share group for given context:
    int	getDisplayListShareGroup( HGLRC ctx );   // 2.1
    
    HWND buildWidget( HWND parent );
    HWND getGlxMgrWidget( void );
    HWND getGLWidget( void );

    SbBool makeNormalCurrent( void );

    SbBool swapNormalBuffers( void );
    SbBool swapOverlayBuffers( void );

    DWORD getThreadId( void );
    void setThreadId(DWORD id);

    void changeCursor( HCURSOR newCursor );

    void glExpose( void );
    virtual void glInit( void );
    virtual void glReshape( int width, int height );
    virtual void glRender( void );
    void glLock( void );
    void glUnlock( void );
    void glSwapBuffers( void );
    void glFlushBuffer( void );
    float getGLAspectRatio( void );

    UINT colorMap;	// set when color index is used
    UINT overlayColorMap; // set when overlay is used

    SbBool waitForExpose;
    SbBool drawToFrontBuffer;
private:
    // creates a GLX widget of the correct current type and get the current
    // set of windows, color maps, etc...
    void buildNormalGLWidget(PIXELFORMATDESCRIPTOR *pfd = NULL);
    void buildOverlayGLWidget(PIXELFORMATDESCRIPTOR *pfd = NULL);

    void destroyNormalWindows( void );
    void destroyGLWidget(HWND &w, HGLRC &ctx, SbBool normalWindow);

    static void managerStructureNotifyCB( HWND, SoWinGLWidget *, MSG *, BOOL *);

    // Callback for SoWinGL "manager widget" window
    static LRESULT CALLBACK managerWindowProc( HWND window,
                                               UINT message,
		 					                   WPARAM wparam,
                                               LPARAM lparam );

    // Callback for SoWinGL "gl widget" window
    static LRESULT CALLBACK glWindowProc( HWND window,
                                          UINT message,
		 					              WPARAM wparam,
                                          LPARAM lparam );

    static LRESULT dispatchMessage( HWND window,
                             UINT message,
                             WPARAM wparam,
                             LPARAM lparam);

    HWND getManagerWidget( void );

    HWND managerWidget;
    HWND doubleBufferWidget;
    HWND singleBufferWidget;
    HWND overlayWidget;

    HGLRC ctxNormal;
    HGLRC ctxOverlay;
    HGLRC ctxSingle;
    HGLRC ctxDouble;
    
    HDC hdcNormal;
    HDC hdcOverlay;
    HDC hdcSingle;
    HDC hdcDouble;
    
    SbVec2s glSize;
    SbBool enableDrawToFrontBuffer;

    PIXELFORMATDESCRIPTOR pfd;
    int nPixelFormat;

    PIXELFORMATDESCRIPTOR pfdNormal;
    PIXELFORMATDESCRIPTOR pfdOverlay;
    PIXELFORMATDESCRIPTOR pfdSingle;
    PIXELFORMATDESCRIPTOR pfdDouble;

    // For 8bpp mode
    HPALETTE palNormal;
    HPALETTE palOverlay;
    HPALETTE palSingle;
    HPALETTE palDouble;

    HWND parent;
    HWND toplevel;

    // Process WM_SETFOCUS/WM_KILLFOCUS (see glxWindowProc).
    BOOL haveFocus;
    BOOL stealFocus;        // "focus follows pointer".
    UINT mouseCaptured;    // Guarantees you will also get the corresponding button up event.

    // Process WM_SETCURSOR (see glxWindowProc).
    HCURSOR currentCursor;

    // We also need (globally for the class) the default cursor to use.
    // static __SoWinStaticImport HCURSOR defaultCursor;
    static HCURSOR defaultCursor;

    DWORD dwThreadId;

    int *attribList;
    int glModes;
    int borderSize;
    
    SbBool windowResized;

}; // class SoWinGLWidget

// *************************************************************************

#endif // ! SOWIN_GLWIDGET_H