/**************************************************************************
 *
 *  This file is part of the Coin SoWin GUI binding library.
 *  Copyright (C) 2000 by Systems in Motion.  All rights reserved.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public License
 *  version 2.1 as published by the Free Software Foundation.  See the
 *  file LICENSE.LGPL at the root directory of the distribution for
 *  more details.
 *
 *  If you want to use Coin SoWin for applications not compatible with the
 *  LGPL, please contact SIM to aquire a Professional Edition License.
 *
 *  Systems in Motion, Prof Brochs gate 6, N-7030 Trondheim, NORWAY
 *  http://www.sim.no/ support@sim.no Voice: +47 22114160 Fax: +47 22207097
 *
 **************************************************************************/

#ifndef SOWIN_GLWIDGET_H
#define SOWIN_GLWIDGET_H

#include <Inventor/SbBasic.h>

#include <windows.h>
#include <Inventor/Win/SoWinBasic.h>
#include <Inventor/Win/SoWinComponent.h>

class SoWinGLArea;

enum GLModes {
  SO_GL_RGB      = 0x01, SO_GLX_RGB      = SO_GL_RGB,
  SO_GL_DOUBLE   = 0x02, SO_GLX_DOUBLE   = SO_GL_DOUBLE,
  SO_GL_ZBUFFER  = 0x04, SO_GLX_ZBUFFER  = SO_GL_ZBUFFER,
  SO_GL_OVERLAY  = 0x08, SO_GLX_OVERLAY  = SO_GL_OVERLAY,
  SO_GL_STEREO   = 0x10, SO_GLX_STEREO   = SO_GL_STEREO,
  SO_GL_DEFAULT_MODE =
    ( SO_GL_RGB | SO_GL_DOUBLE | SO_GL_ZBUFFER )
};

// *************************************************************************

class SOWIN_DLL_API SoWinGLWidget : public SoWinComponent {
  SOWIN_OBJECT_ABSTRACT_HEADER( SoWinGLWidget, SoWinComponent );

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
  
  virtual void setNormalVisual( PIXELFORMATDESCRIPTOR * vis );
  PIXELFORMATDESCRIPTOR * getNormalVisual( void );

  virtual void setOverlayVisual( PIXELFORMATDESCRIPTOR * vis );
  PIXELFORMATDESCRIPTOR * getOverlayVisual( void );
  
  virtual void setPixelFormat( int format );
  int getPixelFormat( void );

  void setDoubleBuffer( SbBool set );
  SbBool isDoubleBuffer( void );
  
  void setBorder( SbBool set );
  int getBorderSize( void );
  SbBool isBorder( void ) const;
  
  void setDrawToFrontBufferEnable( SbBool enable );
  SbBool isDrawToFrontBufferEnable( void ) const;

  void setQuadBufferStereo( const SbBool enable );
  SbBool isQuadBufferStereo( void ) const;

  void setCursor( HCURSOR newCursor );
  HCURSOR getCursor( void );

  SbBool hasOverlayGLArea( void ) const;
  SbBool hasNormalGLArea( void ) const;

  // FIXME: implemented in SoQt. mariusbu 20010719.
  //unsigned long getOverlayTransparentPixel( void );

  void processExternalEvent( HWND window,
                             UINT message,
                             WPARAM wparam,
                             LPARAM lparam );

protected:
  
  SoWinGLWidget( HWND parent = NULL,
                 const char * name = NULL,
                 SbBool embed = TRUE,
                 int glModes = SO_GL_RGB,
                 SbBool build = TRUE );

  virtual ~SoWinGLWidget( void );

  virtual void processEvent( MSG * msg );
  virtual void redraw( void ) = 0;
  virtual void redrawOverlay( void );

  virtual void initGraphic( void );
  virtual void initOverlayGraphic( void );
  virtual void sizeChanged( const SbVec2s newSize );
  virtual void widgetChanged( HWND newWidget );
  virtual SbBool glScheduleRedraw( void );

  void setGLSize( SbVec2s newSize );
  SbVec2s getGLSize( void ) const;
  float getGLAspectRatio( void ) const;

  void setGlxSize( SbVec2s newSize ) { this->setGLSize( newSize ); }
  const SbVec2s getGlxSize( void ) const { return this->getGLSize( ); }
  float getGlxAspectRatio( void ) const { return this->getGLAspectRatio( ); }
  
  static LRESULT eventHandler( HWND hwnd,
                               UINT message,
                               WPARAM wParam,
                               LPARAM lParam );
  
  void setStereoBuffer( SbBool set );
  SbBool isStereoBuffer( void );
  SbBool isRGBMode( void );

  int	getDisplayListShareGroup( HGLRC ctx );

  HWND buildWidget( HWND parent );
  HWND getManagerWidget( void );
  HWND getGLWidget( void );

  void setOverlayRender( const SbBool enable );
  SbBool isOverlayRender(void) const;

  SbBool makeNormalCurrent( void );
  SbBool swapNormalBuffers( void );
  SbBool swapOverlayBuffers( void );

  void glLockNormal( void );
  void glUnlockNormal( void );

  void glLockOverlay( void );
  void glUnlockOverlay( void );

  void glSwapBuffers( void );
  void glFlushBuffer( void );

  SbBool waitForExpose;
  SbBool drawToFrontBuffer;
  
  HWND parent;
  HWND toplevel;

private:  

  static LRESULT CALLBACK glWindowProc( HWND window,
                                        UINT message,
                                        WPARAM wparam,
                                        LPARAM lparam );


  static LRESULT CALLBACK managerWindowProc( HWND window,
                                             UINT message,
                                             WPARAM wparam,
                                             LPARAM lparam );

  void buildNormalGLWidget( PIXELFORMATDESCRIPTOR * pfd = NULL );
  void buildOverlayGLWidget( PIXELFORMATDESCRIPTOR * pfd = NULL );
  BOOL createGLContext( HWND window );

  LRESULT onCreate( HWND window, UINT message, WPARAM wparam, LPARAM lparam );
  LRESULT onSize( HWND window, UINT message, WPARAM wparam, LPARAM lparam );
  LRESULT onPaint( HWND window, UINT message, WPARAM wparam, LPARAM lparam );
  LRESULT onDestroy( HWND window, UINT message, WPARAM wparam, LPARAM lparam );

  HWND managerWidget;
  HWND normalWidget;
  HWND overlayWidget;

  HGLRC ctxNormal;
  HGLRC ctxOverlay;

  HDC hdcNormal;
  HDC hdcOverlay;

  SbVec2s glSize;
  SbBool enableDrawToFrontBuffer;

  PIXELFORMATDESCRIPTOR pfdNormal;
  PIXELFORMATDESCRIPTOR pfdOverlay;

  BOOL haveFocus;
  BOOL stealFocus;
  BOOL haveBorder;
  HCURSOR currentCursor;

  int glModes;
  int borderSize;

}; // class SoWinGLWidget

// *************************************************************************

#endif // !SOWIN_GLWIDGET_H
