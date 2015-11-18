// headers--------------------------------------------------------------------------------------------
#include <windows.h>
#include <windowsx.h>
#include <winuser.h>
#include <math.h>
#include <memory.h>
#include <algorithm>
using namespace std;

#include "Interface.h"
#include "MathTools.h"
#include "PhysicsEngine.h"
#include "3DGraphicsEngine.h"
#include "resource.h"


// local variables and defines-------------------------------------------------------------------------
HINSTANCE hInst;

ball *pBalls = NULL; // pointer that contains all the balls in the simulation
int numBalls = 0; // tells us the number of balls in the simulation

vector r_vantagePoint; // vector describing viewpoint of the simulation
double o_vantageAngle; // vector describing the rotation of the camera

int ammoFired = 0; // 0 if the ammo has not been fired, 1 if it has
 

// my functions----------------------------------------------------------------------------------------
int LoadSimulation(HWND hWnd, int universeID)
{
	switch(universeID)
	{
	case USCD:
		{
			numBalls = sizeof(uscd) / sizeof(ball);

			pBalls = new ball[numBalls + 1];

			memcpy(pBalls, &uscd[0], sizeof(uscd));	
			
			r_vantagePoint = 2000.0 * i - 800.0 * k + 300.0 * j;
			o_vantageAngle = 0;
		}
		break;
	case UOFA:
		{
			numBalls = sizeof(uofa) / sizeof(ball);

			pBalls = new ball[numBalls + 1];

			memcpy(pBalls, &uofa[0], sizeof(uofa));	
			
			r_vantagePoint = 800.0 * i + 1000.0 * k + 1000 * j;
			o_vantageAngle = 0;
		}
		break;
	case JARED:
		{
			numBalls = sizeof(jared) / sizeof(ball);

			pBalls = new ball[numBalls + 1];

			memcpy(pBalls, &jared[0], sizeof(jared));			

			r_vantagePoint = (2500.0 * i + 2000.0 * k - 600.0 * j) * 4 / 5;
			o_vantageAngle = 0;
		}
		break;
	}

	*(pBalls + numBalls) = ball(r_vantagePoint * 5 / 7, 0, 10.0, 40.0);
	numBalls++;
	ammoFired = 0;

	InitMy3DGraphicsEngine(hWnd);

	return 1;
}

int CloseSimulation()
{
	delete pBalls;

	return 1;
}

int RenderSimulation()
{
	sphere sphere;

	if(!BeginFrame())
		return 0;

	for(int set = 0; set < numBalls; set++)
	{ 
		// the below code renders the ball
		sphere.radius = (pBalls + set)->radius;
		sphere.color = RGB(180, 100, 40);
		sphere.r = (pBalls + set)->r;
		AddSphereToList(sphere);
		// done rendering ball

		// the below code renders the x, y, z axis of the ball
		sphere.radius = 2;

		sphere.color = RGB(255, 0, 0);
		sphere.r = (pBalls + set)->r_x1;
		AddSphereToList(sphere);
		sphere.r = (pBalls + set)->r_x2;
		AddSphereToList(sphere);

		sphere.color = RGB(0, 255, 0);
		sphere.r = (pBalls + set)->r_y1;
		AddSphereToList(sphere);
		sphere.r = (pBalls + set)->r_y2;
		AddSphereToList(sphere);

		sphere.color = RGB(0, 0, 255);
		sphere.r = (pBalls + set)->r_z1;
		AddSphereToList(sphere);
		sphere.r = (pBalls + set)->r_z2;
		AddSphereToList(sphere);
		// done
	}

	SetCameraPosition(r_vantagePoint);
	SetCameraDirection(-1 * r_vantagePoint);
	SetCameraAngle(o_vantageAngle);

	if(!AddSpheresOnListToFrame())
		return 0;

	AddTextToFrame("USE THE ARROW KEYS TO ADJUST THE CAMERA POSITION", 10, 10, RGB(100, 100, 100));
	AddTextToFrame("USE PAGE UP AND PAGE DOWN TO ADJUST THE CAMERA ANGLE", 10, 45, RGB(100, 100, 100));
	AddTextToFrame("HOLD DOWN THE SPACE BAR TO FIRE!", 10, 80, RGB(100, 100, 100));

	ClearList();

	if(!EndFrame())
		return 0;

	return 1;
}

void ProcessUserInput(double dt)
{
	vector r_;

	if(GetAsyncKeyState(VK_UP) & 0x8000)
		r_ = R_v(dt * CAMERA_ANGULAR_VELOCITY, r_vantagePoint.y * i - r_vantagePoint.x * j) * r_vantagePoint;
	if(GetAsyncKeyState(VK_DOWN) & 0x8000)
		r_ = R_v(-dt * CAMERA_ANGULAR_VELOCITY, r_vantagePoint.y * i - r_vantagePoint.x * j) * r_vantagePoint;

	if(GetAsyncKeyState(VK_LEFT) & 0x8000)
		r_ = R_z(-dt * CAMERA_ANGULAR_VELOCITY) * r_vantagePoint;
	if(GetAsyncKeyState(VK_RIGHT) & 0x8000)
		r_ = R_z(dt * CAMERA_ANGULAR_VELOCITY) * r_vantagePoint;

	if(r_.x > 0.0)
		r_vantagePoint = r_;

	if(GetAsyncKeyState(VK_NEXT) & 0x8000)
		o_vantageAngle += CAMERA_ANGULAR_VELOCITY * dt;
	if(GetAsyncKeyState(VK_PRIOR) & 0x8000)
		o_vantageAngle -= CAMERA_ANGULAR_VELOCITY * dt;

	if(!ammoFired)
		RepositionBall(*(pBalls + numBalls - 1), r_vantagePoint * 5 / 7);

	if(GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		(pBalls + numBalls - 1)->v = (pBalls + numBalls - 1)->r / -5.0;
		(pBalls + numBalls - 1)->w = 0.1 * PI * i;

		ammoFired = 1;
	}
}

void ProcessPhysics(double dt)
{
	// the below code resolves each collision, one collision at a time, in the order that the collisions happen
	double t1, t2 = dt;

	while(dt > 0.0)
	{
		int stoA = -1, stoB = -1;

		for(int seta = 0; seta < numBalls; seta++)
		{
			for(int setb = 0; setb < numBalls; setb++)
			{
				t1 = DoCollide(*(pBalls + seta), *(pBalls + setb));

				if(t1 >= 0.0 && t1 <= t2)
				{
					stoA = seta;
					stoB = setb;

					t2 = t1;				
				}
			}
		}

		for(int set = 0; set < numBalls; set++)
			Translate(*(pBalls + set), t2);

		if(stoA != -1)
			ResolveCollision(*(pBalls + stoA), *(pBalls + stoB));

		dt -= t2;
	}
}

int UpdateSimulation(double dt)
{
	ProcessUserInput(dt);

	ProcessPhysics(dt);

	if(!RenderSimulation())
		return 0;

	return 1;
}

// windows functions------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
	HWND hWnd;
	MSG msg;
	WNDCLASSEX aWNDCLASSEX;
	DWORD t1, t2;

	// init windows stuff
	aWNDCLASSEX.cbSize = sizeof(WNDCLASSEX); 
	aWNDCLASSEX.style = CS_DBLCLKS | CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	aWNDCLASSEX.lpfnWndProc = (WNDPROC)ProcMain;
	aWNDCLASSEX.cbClsExtra = 0;
	aWNDCLASSEX.cbWndExtra = 0;
	aWNDCLASSEX.hInstance = hInstance;
	aWNDCLASSEX.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	aWNDCLASSEX.hCursor = LoadCursor(hInstance, IDC_ARROW);
	aWNDCLASSEX.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);;
	aWNDCLASSEX.lpszMenuName = MAKEINTRESOURCE(IDR_MENU);
	aWNDCLASSEX.lpszClassName = PROGRAM_NAME;
	aWNDCLASSEX.hIconSm = LoadIcon(hInstance, IDI_APPLICATION);

	if(!RegisterClassEx(&aWNDCLASSEX))
		return 0;

	hInst = hInstance;

	if(!(hWnd = CreateWindow(PROGRAM_NAME, PROGRAM_NAME, WS_OVERLAPPEDWINDOW,
		10, 10, 600, 600, NULL, 
		NULL, hInstance, NULL)))
		return 0;

    ShowWindow(hWnd, iCmdShow);
    UpdateWindow(hWnd);

	if(!LoadSimulation(hWnd, UOFA))
		return 0;

	t1 = GetTickCount();

	while(true)
	{
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if(msg.message == WM_QUIT)
				break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		t2 = GetTickCount();

		if(t2 - t1 > 1000 / frameRate) // we only want to update the physics simulator so many times a second
		{
			if(!UpdateSimulation((double)(t2 - t1) / 1000.0)) // call this function to update the position of all the balls.
				PostQuitMessage(0);

			t1 = t2;
		}
	}

	CloseSimulation();

	return msg.wParam;
}

LRESULT CALLBACK ProcMain(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
	case WM_COMMAND:
		{
			switch(LOWORD(wParam))
			{
			case ID_FILE_UCSD:
				{
					CloseSimulation();
					LoadSimulation(hWnd, USCD);
				}
				break;
			case ID_FILE_UOFA:
				{
					CloseSimulation();
					LoadSimulation(hWnd, UOFA);
				}
				break;
			case ID_FILE_JARED:
				{
					CloseSimulation();
					LoadSimulation(hWnd, JARED);
				}
				break;
			case ID_FILE_EXIT:
				PostQuitMessage(0);
				break;
			case ID_HELP_ABOUT:
				{			   
					DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)AboutProc);
				}
				break;
			}
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0); // closing
		break;
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}

	return 0;
}

LRESULT CALLBACK AboutProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
	case WM_INITDIALOG:
		return TRUE;
	case WM_MOVE:
		RenderSimulation();
		return TRUE;
	case WM_COMMAND:
		if(LOWORD(wParam) == IDCANCEL || LOWORD(wParam) == IDC_OK)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}
		break;
	}

	return FALSE;
}