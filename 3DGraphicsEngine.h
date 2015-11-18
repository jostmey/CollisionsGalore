// This is a 3D graphics engine. I custom wrote the code myself. I had a friend
// whose is studying architecture teach me how to draw in perspective. From that,
// I extrapolated several formulas that the computer uses to display 3D images.
// Note: this engine can only display spheres. It cannot be used to render any other
// shape. Also, sometimes this engine displays spheres as ellipses. This is okay though.
// It is a consequence of compressing 3D images onto a 2D plane. If spheres were not
// displayed as ellipses then the 3D renderings would not be to scale.

#ifndef THREE_D_GRAPHICS_ENGINE
#define THREE_D_GRAPHICS_ENGINE

// headers-------------------------------------------------------------------------------
#include <windows.h>

#include "MathTools.h"


// defines and constants--------------------------------------------------------------------------
#define MAX_LIST_SIZE 2000
#define ZOOM_COEFFICIENT 2.0


// declarations------------------------------------------------------------------------
class sphere 
{
public:

	vector r; // position of sphere
	double radius; // radius of sphere
	COLORREF color; // color of sphere
};

void InitMy3DGraphicsEngine(HWND hWnd_); // Call this before any other function on this page!
										 // The handle that is passed specifies the window
										 // that the engine will draw in.

int AddSphereToList(const sphere &sphere); // Like it says at the top of this page, this engine displays
										   // spheres in 3D. The first step in having a sphere rendered is
										   // to pass a 'sphere' object to this function. The sphere is then
										   // added to a list of things that will be displayed. If the list is
										   // full and the sphere cannot be displayed, the function returns 0
										   // Otherwise, it returns 0
void ClearList(); // This removes all the spheres on the list

void SetCameraPosition(const vector &r); // Sets the observation position
void SetCameraDirection(const vector &r); // Sets the direction we are looking
void SetCameraAngle(const double &o); // tilts are view theta radians from the horizon

int BeginFrame(); // Call this create a new frame. Once we have painted everything
				  // on this frame we may call EndFrame() to render the frame on the screen
int AddTextToFrame(char *pText, int xPos, int yPos, COLORREF color); // This function paints text on the frame
int AddSpheresOnListToFrame(); // This function paints all the spheres on the list onto the frame
int EndFrame(); // This takes the frame we have been drawing on and pastes in onto the computer screen

#endif THREE_D_GRAPHICS_ENGINE