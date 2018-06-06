// This example demonstrates how to set up and SoWin renderarea within
// a "stand-alone" application window.

#include <stdlib.h> // exit()
#include <Inventor/Win/SoWin.h>
#include <Inventor/Win/SoWinRenderArea.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoPerspectiveCamera.h>
#include <Inventor/nodes/SoDirectionalLight.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoSphere.h>

// Dummy message handler for 2nd window
LRESULT CALLBACK
WindowFunc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  switch(message) {
  case WM_DESTROY:
    PostQuitMessage(0);
    break;
  default:
    return DefWindowProc(hwnd, message, wParam, lParam);
  }
  return 0;
}

int
main(int argc, char ** argv)
{
  WNDCLASSEX windowclass;

  windowclass.cbSize = sizeof(WNDCLASSEX);
  windowclass.hInstance = NULL;
  windowclass.lpszClassName = TEXT("AppWindow");
  windowclass.lpfnWndProc = WindowFunc;
  windowclass.style = 0;
  windowclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
  windowclass.hIconSm = LoadIcon(NULL, IDI_WINLOGO);
  windowclass.hCursor = LoadCursor(NULL, IDC_ARROW);
  windowclass.lpszMenuName = NULL;
  windowclass.cbClsExtra = 0;
  windowclass.cbWndExtra = 0;
  windowclass.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);

  if (!RegisterClassEx(&windowclass)) { exit(1); }

  HWND appwin = CreateWindow(TEXT("AppWindow"),
                             TEXT("AppWindow"), // title
                             WS_OVERLAPPEDWINDOW,
                             CW_USEDEFAULT,
                             CW_USEDEFAULT,
                             CW_USEDEFAULT,
                             CW_USEDEFAULT,
                             HWND_DESKTOP,
                             NULL,
                             (HINSTANCE)NULL,
                             NULL);

  SoWin::init(appwin);

  // Create a scene containing a sphere
  SoSeparator * root = new SoSeparator;
  root->ref(); // increment the root's reference counter

  SoPerspectiveCamera * camera = new SoPerspectiveCamera;
  SoDirectionalLight * light = new SoDirectionalLight;
  SoMaterial * material = new SoMaterial;
  SoSphere * sphere = new SoSphere;

  root->addChild(camera); // add camera node to the scene graph
  root->addChild(light); // add directional light to the scene
  root->addChild(material); // add material (with default settings)
  root->addChild(sphere); // add sphere node to the scene graph

  // Create a renderingarea which will be used to display the
  // scene graph in the window.
  SoWinRenderArea * renderarea = new SoWinRenderArea(appwin);

  // Make the camera able to see the whole scene
  camera->viewAll(root, renderarea->getViewportRegion());

  // Display the scene in our renderarea and change the title
  renderarea->setSceneGraph(root);
  renderarea->setTitle("Sphere");
  renderarea->show();

  SoWin::show(appwin);  //display the main window
  SoWin::mainLoop();  //main Coin event loop
  delete renderarea;  //free up the resources occupied by the renderarea

  root->unref();  //decrement the root's reference counter
  return 0;
}
