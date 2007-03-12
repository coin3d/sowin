#ifndef SOGUIVIEWERP_H
#define SOGUIVIEWERP_H

/**************************************************************************\
 *
 *  This file is part of the Coin 3D visualization library.
 *  Copyright (C) 1998-2005 by Systems in Motion.  All rights reserved.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  ("GPL") version 2 as published by the Free Software Foundation.
 *  See the file LICENSE.GPL at the root directory of this source
 *  distribution for additional information about the GNU GPL.
 *
 *  For using Coin with software that can not be combined with the GNU
 *  GPL, and for taking advantage of the additional benefits of our
 *  support services, please contact Systems in Motion about acquiring
 *  a Coin Professional Edition License.
 *
 *  See <URL:http://www.coin3d.org/> for more information.
 *
 *  Systems in Motion, Postboks 1283, Pirsenteret, 7462 Trondheim, NORWAY.
 *  <URL:http://www.sim.no/>.
 *
\**************************************************************************/

#ifndef SOWIN_INTERNAL
#error this is a private header file
#endif /* !SOWIN_INTERNAL */

#include <Inventor/SbRotation.h>
#include <Inventor/SbVec3f.h>

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif // HAVE_CONFIG_H

#include <Inventor/Win/common/gl.h>
#include <Inventor/Win/common/SbGuiList.h>
#include <Inventor/Win/viewers/SoWinViewer.h>

class SoSeparator;
class SoCamera;
class SoOrthographicCamera;
class SoPerspectiveCamera;
class SoGetBoundingBoxAction;
class SoNode;
class SoTimerSensor;
class SoDirectionalLight;
class SoSwitch;
class SoBaseColor;
class SoDrawStyle;
class SoLightModel;
class SoMaterialBinding;
class SoPolygonOffset;
class SoComplexity;
class SoSearchAction;
class SoGetMatrixAction;

class SoWinViewerP {
public:
  SoWinViewerP(SoWinViewer * publ);
  ~SoWinViewerP(void);

  SoSeparator * createSuperScene(void);

  static void convertOrtho2Perspective(const SoOrthographicCamera * in,
                                       SoPerspectiveCamera * out);
  static void convertPerspective2Ortho(const SoPerspectiveCamera * in,
                                       SoOrthographicCamera * out);

  SoCamera * camera;
  SoWinViewer::Type type;
  SbBool viewingflag;
  SoGetBoundingBoxAction * autoclipbboxaction;
  SoSeparator * sceneroot;
  SoNode * scenegraph;


  // Seek functionality
  SoTimerSensor * seeksensor;
  float seekperiod;
  SbBool inseekmode;
  SbBool seektopoint;
  SbVec3f camerastartposition, cameraendposition;
  SbRotation camerastartorient, cameraendorient;
  float seekdistance;
  SbBool seekdistanceabs;

  // Home position storage.
  SoNode * storedcamera;

  SoDirectionalLight * headlight;

  // Drawstyles
  SoWinViewer::DrawStyle drawstyles[2];
  SoSwitch * drawstyleroot, * hiddenlineroot, * polygonoffsetparent;
  SoBaseColor * sobasecolor;
  SoComplexity * socomplexity;
  SoDrawStyle * sodrawstyle;
  SoLightModel * solightmodel;
  SoMaterialBinding * somaterialbinding;
  SoSeparator * usersceneroot;
  SoSwitch * superimpositionroot;
#ifdef HAVE_SOPOLYGONOFFSET
  SoPolygonOffset * sopolygonoffset;
#endif // HAVE_SOPOLYGONOFFSET
  // Automatic setting of clipping planes
  SbBool adjustclipplanes;

  // Keep track of the frames-per-second counter.
  // Const value trick for old compilers.
  enum Constants { FRAMESARRAY_SIZE = 100 };
  SbVec2f frames[FRAMESARRAY_SIZE];
  float totalcoin, totaldraw;
  double lastgettimeofday;
  int framecount;
  
  // Stereo-related
  SbBool stereoviewing, stereotypesetexplicit;
  float stereooffset;
  SoWinViewer::StereoType stereotype;
  SbBool stereoanaglyphmask[2][3];
  SbViewportRegion stereostencilmaskvp;
  GLubyte * stereostencilmask;
  enum StencilType { ROWS, COLUMNS, NONE };
  SoWinViewer::StereoType stereostenciltype;
  enum Eye { LEFT, RIGHT, RESTORE };
  struct StereoData {
    SbVec3f camerapos, cameradir, offsetvec, focalpoint;
    SbRotation camerarot;
    float offset;
    SbBool nodenotify, positionnotify, orientationnotify;
  };
  void setStereoEye(SoCamera * camera,
                    const SoWinViewerP::Eye eye,
                    SoWinViewerP::StereoData & storage) const;
  void initStencilBufferForInterleavedStereo(void);

  // Misc
  SoType cameratype;
  SbBool cursoron, localsetbuffertype;
  SoCallbackList * interactionstartCallbacks, * interactionendCallbacks;
  int interactionnesting;
  SoWinViewer::BufferType buffertype;
  SbColor wireframeoverlaycolor;

  void reallyRedraw(const SbBool clearcol, const SbBool clearz = TRUE);

  // Seek functionality
  static void seeksensorCB(void * data, SoSensor *);

  // Drawstyles
  void changeDrawStyle(SoWinViewer::DrawStyle style);
  SbBool drawInteractiveAsStill(void) const;
  SbBool drawAsHiddenLine(void) const;
  SbBool drawAsWireframeOverlay(void) const;
  SoWinViewer::DrawStyle currentDrawStyle(void) const;

  // Automatic setting of clipping planes
  void setClippingPlanes(void);

  // Methods to keep track of frames-per-second value.
  void resetFrameCounter(void);
  SbVec2f addFrametime(const double ft);
  void recordFPS(const double rendertime);

  // Misc
  static void interactivestartCB(void *, SoWinViewer * thisp);
  static void interactiveendCB(void *, SoWinViewer * thisp);
  void moveCameraScreen(const SbVec2f & screenpos);
  void getCameraCoordinateSystem(SoCamera * camera, SoNode * root,
                                 SbMatrix & matrix, SbMatrix & inverse);

  SoGroup * getParentOfNode(SoNode * root, SoNode * node) const;
  SoSearchAction * searchaction;

  SoGetMatrixAction * matrixaction;
  SbPList * superimpositions;
  SbGuiList<SbBool> superimpositionsenabled;
  SoWinViewer * pub;

  // auto clipping parameters
  SoWinViewer::AutoClippingStrategy autoclipstrategy;
  float autoclipvalue;
  SoWinAutoClippingCB * autoclipcb;
  void * autoclipuserdata;
};

#endif // SOGUIVIEWERP_H
