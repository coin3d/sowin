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
	    const char * name = NULL, 
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

    virtual void setPixelFormat( int format );
    int getPixelFormat( void );

    void setDoubleBuffer( SbBool set );
    SbBool isDoubleBuffer( void );
    
    void setBorder( SbBool set );   // show/hide 3 pixel border ( default = off )
    int getBorderSize( void );
    SbBool isBorder( void ) const;
    
    void setDrawToFrontBufferEnable( SbBool enable );
    SbBool isDrawToFrontBufferEnable( void ) const;

    void setCursor( HCURSOR newCursor );
    HCURSOR getCursor( void ); // coin spesific

protected:
    virtual void redraw( void ) = 0;
    virtual void redrawOverlay( void );
    virtual void processEvent( MSG * msg );

    virtual void initGraphic( void );
    virtual void initOverlayGraphic( void );
    virtual void sizeChanged( const SbVec2s newSize );
    virtual void widgetChanged( HWND newWidget );
    
    void setGlxSize( SbVec2s newSize );
    void setGLSize( SbVec2s newSize );  // Coin spesific
    const SbVec2s getGlxSize( void ) const;
    const SbVec2s getGLSize( void ) const;
    
    //static void eventHandler( HWND, SoWinGLWidget *, MSG *, BOOL * );
    static LRESULT eventHandler( HWND hwnd,
                                 UINT message,
                                 WPARAM wParam,
                                 LPARAM lParam );

    void setStereoBuffer( SbBool set );
    SbBool isStereoBuffer( void );
    SbBool isRGBMode( void );
    
    int	getDisplayListShareGroup( HGLRC ctx );
    
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
    void buildNormalGLWidget(PIXELFORMATDESCRIPTOR *pfd = NULL);
    void buildOverlayGLWidget(PIXELFORMATDESCRIPTOR *pfd = NULL);

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

    LRESULT onCreate( HWND window, UINT message, WPARAM wparam, LPARAM lparam );
    LRESULT onSize( HWND window, UINT message, WPARAM wparam, LPARAM lparam );
    LRESULT onPaint( HWND window, UINT message, WPARAM wparam, LPARAM lparam );
    LRESULT onDestroy( HWND window, UINT message, WPARAM wparam, LPARAM lparam );

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