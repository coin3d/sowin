// File: multiview.cpp

#include <Inventor/Win/viewers/SoWinExaminerViewer.h>
#include <Inventor/Win/viewers/SoWinPlaneViewer.h>
#include <Inventor/Win/SoWin.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoCone.h>

HWND examiner = NULL;
HWND plane = NULL;

SoWinExaminerViewer * ev = NULL;
SoWinPlaneViewer * pv = NULL;

void sizeWindow(HWND window, int width, int height)
{
	UINT flags = SWP_NOMOVE | SWP_NOZORDER;
	SetWindowPos(window, NULL, 0, 0, width, height, flags);
}

LRESULT CALLBACK mainWindowProc(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
{
	if ( message == WM_DESTROY ) {
		PostQuitMessage( 0 );
		return 0;
	}
	if ( message == WM_SIZE ) {
		MoveWindow(plane, 0, 0, LOWORD(lparam) / 2, HIWORD(lparam), TRUE);
		MoveWindow(examiner, LOWORD(lparam) / 2, 0, LOWORD(lparam) / 2, HIWORD(lparam), TRUE);
	}
	return DefWindowProc(window, message, wparam, lparam);
}

LRESULT CALLBACK planeWindowProc(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
{
	if (message == WM_SIZE) {
		if (pv) pv->setSize(SbVec2s(LOWORD(lparam), HIWORD(lparam)));
		return 0;
	}
	return DefWindowProc(window, message, wparam, lparam);
}

LRESULT CALLBACK examinerWindowProc(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
{
	if (message == WM_SIZE) {
		if (ev) ev->setSize(SbVec2s(LOWORD(lparam), HIWORD(lparam)));
		return 0;
	}
	return DefWindowProc(window, message, wparam, lparam);
}

HWND createWindow(
	HINSTANCE instance,
	HWND parent,
	LPSTR wndclassname,
	UINT style,
	SbVec2s pos,
	SbVec2s size,
	WNDPROC proc
	)
{
  WNDCLASS windowclass;

  LPCTSTR icon = MAKEINTRESOURCE(IDI_APPLICATION);
  LPCTSTR cursor = MAKEINTRESOURCE(IDC_ARROW);
  HMENU menu = NULL;
  HBRUSH brush = (HBRUSH) GetSysColorBrush(COLOR_BTNFACE);

  windowclass.lpszClassName = wndclassname;
  windowclass.hInstance = instance;
  windowclass.lpfnWndProc = proc;
  windowclass.style = CS_OWNDC;
  windowclass.lpszMenuName = NULL;
  windowclass.hIcon = LoadIcon(NULL, icon);
  windowclass.hCursor = LoadCursor(instance, cursor);
  windowclass.hbrBackground = brush;
  windowclass.cbClsExtra = 0;
  windowclass.cbWndExtra = 4;

  RegisterClass(&windowclass);

  HWND window = CreateWindow(wndclassname,
    wndclassname,
    style,
    pos[0],
    pos[1],
    size[0],
    size[1],
    parent,
    NULL,
    instance,
    NULL);
  
  return window;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
  HWND mainwin = createWindow(hInstance,
    NULL,
    "MainWindow",
    WS_OVERLAPPEDWINDOW | WS_VISIBLE,
    SbVec2s(CW_USEDEFAULT,CW_USEDEFAULT),
    SbVec2s(600,600),
    mainWindowProc);

  HWND planewin = createWindow(hInstance,
    mainwin,
    "PlaneWindow",
    WS_CHILD | WS_VISIBLE,
    SbVec2s(0,0),
    SbVec2s(300,600),
    planeWindowProc);
  HWND examinerwin = createWindow(hInstance,
    mainwin,
    "ExaminerWindow",
    WS_CHILD | WS_VISIBLE,
    SbVec2s(300,0),
    SbVec2s(300,600),
    examinerWindowProc);
  
  plane = planewin;
  examiner = examinerwin;

  SoWin::init(mainwin);

  SoSeparator * s = new SoSeparator;
  s->addChild(new SoCone);

  SoWinExaminerViewer * eviewer = ev = new SoWinExaminerViewer(examinerwin);
  eviewer->setSceneGraph(s);
  eviewer->show();

  SoWinPlaneViewer * pviewer = pv = new SoWinPlaneViewer(planewin);
  pviewer->setSceneGraph(s);
  pviewer->show();

  sizeWindow(mainwin, 500, 500); // The viewers size to default
                                 // size when created. We size them back.
  SoWin::mainLoop();

  return 0;
}
