// Basic test example for embedding a SoWin-component (the
// examinerviewer, to be exact) into a native Win32 window.
//
// Build with: ``sowin-config --build embedded embedded.cpp''
//
// <mortene@sim.no>

#include <Inventor/Win/viewers/SoWinExaminerViewer.h>
#include <Inventor/Win/SoWin.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoCone.h>

LRESULT CALLBACK
mainwinproc(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
{
 
 if ( message == WM_DESTROY ) {
  PostQuitMessage( 0 );
  return 0;
 }
  
 if ( message == WM_SIZE ) {
   printf("size\n");
 }

 return DefWindowProc(window, message, wparam, lparam);
}

int WINAPI
WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
        LPSTR lpCmdLine, int nShowCmd)
{
  WNDCLASS windowclass;
  windowclass.lpszClassName = "MainWindow";
  windowclass.hInstance = hInstance;
  windowclass.lpfnWndProc = mainwinproc;
  windowclass.style = CS_OWNDC;
  windowclass.lpszMenuName = NULL;
  windowclass.hIcon = LoadIcon(NULL, MAKEINTRESOURCE(IDI_APPLICATION));
  windowclass.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_ARROW));
  windowclass.hbrBackground = GetSysColorBrush(COLOR_BTNFACE);
  windowclass.cbClsExtra = 0;
  windowclass.cbWndExtra = 4;

  RegisterClass(&windowclass);

  HWND rootwin =
    CreateWindow("MainWindow",
                 "MainWindow",
                 WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                 CW_USEDEFAULT, // xpos
                 CW_USEDEFAULT, // ypos
                 600, // width
                 600, // height
                 NULL, // parent
                 NULL,
                 hInstance,
                 NULL);

  SoWin::init(rootwin);

  SoSeparator * s = new SoSeparator; // Scene root
  s->addChild(new SoCone);

  SoWinExaminerViewer * eviewer = new SoWinExaminerViewer(rootwin);
  eviewer->setSceneGraph(s);
  eviewer->show();

  SoWin::mainLoop();

  return 0;
}
