// headers---------------------------------------------------------------------------
#include <windows.h>
#include <math.h>
#include <algorithm>

#include "3DGraphicsEngine.h"


// local variables-------------------------------------------------------------------
HWND hWnd;
HDC primaryBuffer, backBuffer;
HBITMAP bitmap;
RECT aRect;

sphere list[MAX_LIST_SIZE]; // This list contains all the spheres to be rendered
int numSpheres = 0; // This is the number of spheres on the list

vector r_camera = 0, // This vector specifies the location of the camera
	   i_camera = i, // i_, j_, and k_ specify the camera's x, y, and z axis in terms of i, j, k. These vectors i_, j_ , and k_ come in real handy
	   j_camera = j, 
	   k_camera = k;
double o_camera = 0.0; // This specifies how many radians the camera is tilted from the horizon


// local declarations-----------------------------------------------------------------
bool operator < (const sphere &sphereA, const sphere &sphereB);


// local definitions-------------------------------------------------------------------
bool operator < (const sphere &sphereA, const sphere &sphereB)
{
	// The below code measures which sphere is farther away.
	if((sphereA.r - r_camera) * (sphereA.r - r_camera) <
	   (sphereB.r - r_camera) * (sphereB.r - r_camera))
	   return true;

	return false;
}

// definitions-----------------------------------------------------------------
void InitMy3DGraphicsEngine(HWND hWnd_) // So this function is basically a wrapper
{
	hWnd = hWnd_;
}

int AddSphereToList(const sphere &sphere) // This function adds spheres to the list. It returns 0 if the list is full
{
	if(numSpheres == MAX_LIST_SIZE)
		return 0;

	list[numSpheres] = sphere;

	numSpheres++;

	return 1;
}

void ClearList() // Uh,..., this is another wrapper function
{
	numSpheres = 0;
}

void SetCameraPosition(const vector &r) // again, this is a wrapper function
{
	r_camera = r;
}

void SetCameraDirection(const vector &r) // This function takes r and computes i_, j_ and k_
{
	i_camera = -1 * Hat(r); // computing the camera's x axis in terms of i, j, and k. Note: we are looking down the positive x-axis

	if(i_camera.x == 0 && i_camera.y == 0.0) // This checks to see if we are looking straight down or straight up the z - axis
	{
		if(i_camera.z > 0.0)
		{
			j_camera = i;
			k_camera = j;
		}
		else
		{
			j_camera = i;
			k_camera = -1 * j;
		}
	}
	else
	{
		double s = sqrt(i_camera.x * i_camera.x + i_camera.y * i_camera.y);

		j_camera = -i_camera.y / s * i + i_camera.x / s * j; // computing j_ from i_. This code fixes j_ so that it is always normal to k.
		k_camera = -i_camera.x * i_camera.z / s * i - i_camera.y * i_camera.z / s * j + s * k; // computing k_. This code fixes k_ so that it is always normal to i_ and j_
	}
}

void SetCameraAngle(const double &o) // Yet another wrapper function
{
	o_camera = o;
}

int BeginFrame() // This code creates two buffers. One buffer is the frame that we draw on. The other buffer refers to the computer screen.
{
	if(!GetClientRect(hWnd, &aRect))
		return 0;
	
	if((primaryBuffer = GetDC(hWnd)) == NULL || 
	   (backBuffer = CreateCompatibleDC(primaryBuffer)) == NULL ||
	   (bitmap = CreateCompatibleBitmap(primaryBuffer, aRect.right - aRect.left, aRect.bottom - aRect.top)) == NULL)
	   return 0;

	if(SelectObject(backBuffer, bitmap) == NULL)
		return 0;

	if(SetBkColor(backBuffer, RGB(0, 0, 0)) == CLR_INVALID)
		return 0;

	return 1;
}

int AddTextToFrame(char *pText, int xPos, int yPos, COLORREF color) // wrapper function
{
	SetTextColor(backBuffer, color);

	TextOut(backBuffer, xPos, yPos, pText, strlen(pText));

	return 1;
}

int AddSpheresOnListToFrame()
{
	// we must sort the spheres so that spheres that are farther from the camera are at the back of the
	// list. That's what function std::sort does. It refers to the above definition of '<' to figure
	// out which spheres are farthest away.
	std::sort(list, list + numSpheres); 
	// done sorting

	double yCenter,
		   zCenter,
		   s_y,
		   s_z,
		   red,
		   green,
		   blue,
		   dist;

	HBRUSH brush;
	HPEN pen;
	COLORREF color;

	vector r_,
		   c1_,
		   c2_;

	yCenter = (aRect.right + aRect.left) / 2;
	zCenter = (aRect.bottom + aRect.top) / 2;

	// the below code cycles through every sphere, painting each one on the back buffe
	for(int set = numSpheres - 1; set >= 0; set--)
	{
		// the below code makes spheres that are farther away appear more grey
		red = (double)GetRValue(list[set].color);
		green = (double)GetGValue(list[set].color);
		blue = (double)GetBValue(list[set].color);

		dist = Magnitude(list[set].r - r_camera);

		red += (255.0 - red) * (1 - exp(-dist / 1000.0)) / 20.0;
		green += (255.0 - green) * (1 - exp(-dist / 1000.0)) / 14.0;
		blue += (255.0 - blue) * (1 - exp(-dist / 1000.0)) / 10.0;

		color = RGB((BYTE)red, (BYTE)green, (BYTE)blue);
		// done graying spheres


		// The below code preforms a change in coordinate systems. It changes from the origin
		// to the position of the observer
		r_ = ((list[set].r - r_camera) * i_camera) * i +
			 ((list[set].r - r_camera) * j_camera) * j + 
			 ((list[set].r - r_camera) * k_camera) * k;
		r_ = R_x(o_camera) * r_;
		// Done changing coordinate systems


		// The below computes where each sphere needs to rendered on the computer screen. My
		// architect friend 
		if(r_.x >= -300.0)
			continue;

		s_y = sqrt(r_.z * r_.z + r_.x * r_.x - list[set].radius * list[set].radius),
		s_z = sqrt(r_.y * r_.y + r_.x * r_.x - list[set].radius * list[set].radius);

		c1_ = (r_.y * s_y + list[set].radius * r_.x) / (r_.x * s_y - list[set].radius * r_.y) * j
			+ (r_.z * s_z + list[set].radius * r_.x) / (r_.x * s_z - list[set].radius * r_.z) * k;
		c2_ = (r_.y * s_y - list[set].radius * r_.x) / (r_.x * s_y + list[set].radius * r_.y) * j
			+ (r_.z * s_z - list[set].radius * r_.x) / (r_.x * s_z + list[set].radius * r_.z) * k;

		c1_ *= ZOOM_COEFFICIENT * Maximum(yCenter, zCenter);
		c2_ *= ZOOM_COEFFICIENT * Maximum(yCenter, zCenter);
		// end of computation


		// The below code checks to see if the sphere is within our viewing range
		if(c1_.y + list[set].radius > 2 * yCenter && c1_.z - list[set].radius < 0)
			continue;

		if(c2_.y - list[set].radius < 0 && c2_.z + list[set].radius > 2 * zCenter)
			continue;
		// done testing if the sphere is in view


		// the below code draws the spheres on the back buffer
		if((brush = CreateSolidBrush(color)) == NULL || // purchasing a brush from windows
		   SelectObject(backBuffer, brush) == NULL || // dipping the brush in paint
		   (pen = CreatePen(PS_SOLID, 0, RGB(0, 0, 0))) == NULL || // purchasing a pen from windows
		   SelectObject(backBuffer, pen) == NULL) // dipping the pen in paint
		   return 0;

		if(!Ellipse(backBuffer, (int)(c1_.y + yCenter), (int)(c1_.z + zCenter),
							    (int)(c2_.y + yCenter), (int)(c2_.z + zCenter)))
			return 0;

		if(DeleteObject(pen) == 0 || // throwing away the pen
		   DeleteObject(brush) == 0) // throwing away the brush. How wasteful!
		   return 0;
		// done drawing the spheres
	}

	return 1;
}

int EndFrame() // This function copies the back buffer onto the primary buffer, i.e., it copies everything from the frame onto the screen. It also does a little cleanup
{
	if(!BitBlt(primaryBuffer, 0, 0, aRect.right - aRect.left, aRect.bottom - aRect.top,
  			   backBuffer, 0, 0, SRCCOPY))
		return 0;

	if(!DeleteObject(bitmap) ||
	   !DeleteDC(backBuffer) ||
	   !ReleaseDC(hWnd, primaryBuffer))
	   return 0;

	return 1;
}