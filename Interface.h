// This code handles all the interactions with the user. There's really not much to say.

#ifndef INTERFACE
#define INTERFACE

// headers-------------------------------------------------------------------------------
#include <windows.h>

#include "MathTools.h"
#include "PhysicsEngine.h"


// defines and constants------------------------------------------------------------------
#define PROGRAM_NAME "CollisionsGalore"

const DWORD frameRate = 30;

#define CAMERA_ANGULAR_VELOCITY PI / 10 // speed at which the observer can change his or her position


// my function declarations----------------------------------------------------------------
int LoadSimulation(HWND hWnd, int universeID); // Call this function to start the simulation. The parameter
											   // universeID indicates which of the various "universes" you
									           // want to run the simulate.
int RenderSimulation();
void ProcessPhysics(double dt);
void ProcessUserInput(double dt);

int UpdateSimulation(double dt); // Call this function to update the position of the balls.
								 // The parameter 'dt' indicate how many seconds have
								 // elapsed since this function was last called.

int CloseSimulation(); // Call this function when exiting the program or when you wish to start a
					   // new simulation. Basically, this function cleans up the memory. If you don't
					   // call it there could be memory leakage.


// windows function declarations---------------------------------------------------------------
LRESULT CALLBACK ProcMain(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK AboutProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam);


// the below code defines the different univeses----------------------------------------------------
#define LETTER_SEPARATION 100.0
#define RADIUS 40.0

#define USCD 1
ball uscd[] = {ball(LETTER_SEPARATION * (6 * j + 2 * k), 0, 10.0, RADIUS), // beginning of 'U'
			   ball(LETTER_SEPARATION * (6 * j + k), 0, 10.0, RADIUS),
			   ball(LETTER_SEPARATION * (6 * j), 0, 10.0, RADIUS),
			   ball(LETTER_SEPARATION * (6 * j - k), 0, 10.0, RADIUS),
			   ball(LETTER_SEPARATION * (6 * j - 2 * k), 0, 10.0, RADIUS),
			   ball(LETTER_SEPARATION * (5 * j - 2 * k), 0, 10.0, RADIUS),
			   ball(LETTER_SEPARATION * (4 * j - 2 * k), 0, 10.0, RADIUS),
			   ball(LETTER_SEPARATION * (4 * j - k), 0, 10.0, RADIUS),
			   ball(LETTER_SEPARATION * (4 * j), 0, 10.0, RADIUS),
			   ball(LETTER_SEPARATION * (4 * j + k), 0, 10.0, RADIUS),
			   ball(LETTER_SEPARATION * (4 * j + 2 * k), 0, 10.0, RADIUS), // end of 'U'
			   ball(LETTER_SEPARATION * (2 * k), 0, 10.0, RADIUS), // beginning of 'C'
			   ball(LETTER_SEPARATION * (j + 2 * k), 0, 10.0, RADIUS),
			   ball(LETTER_SEPARATION * (2 * j + 2 * k), 0, 10.0, RADIUS),
			   ball(LETTER_SEPARATION * (2 * j + k), 0, 10.0, RADIUS),
			   ball(LETTER_SEPARATION * (2 * j), 0, 10.0, RADIUS),
			   ball(LETTER_SEPARATION * (2 * j - k), 0, 10.0, RADIUS),
			   ball(LETTER_SEPARATION * (2 * j - 2 * k), 0, 10.0, RADIUS),
			   ball(LETTER_SEPARATION * (j - 2 * k), 0, 10.0, RADIUS),
			   ball(LETTER_SEPARATION * (-2 * k), 0, 10.0, RADIUS), // end of 'C'
			   ball(LETTER_SEPARATION * (-4 * j + 2 * k), 0, 10.0, RADIUS), // beginning of 'S'
			   ball(LETTER_SEPARATION * (-3 * j + 2 * k), 0, 10.0, RADIUS),
			   ball(LETTER_SEPARATION * (-2 * j + 2 * k), 0, 10.0, RADIUS),
			   ball(LETTER_SEPARATION * (-2 * j + k), 0, 10.0, RADIUS),
			   ball(LETTER_SEPARATION * (-2 * j), 0, 10.0, RADIUS),
			   ball(LETTER_SEPARATION * (-3 * j), 0, 10.0, RADIUS),
			   ball(LETTER_SEPARATION * (-4 * j), 0, 10.0, RADIUS),
			   ball(LETTER_SEPARATION * (-4 * j -1 * k), 0, 10.0, RADIUS),
			   ball(LETTER_SEPARATION * (-4 * j-2 * k), 0, 10.0, RADIUS),
			   ball(LETTER_SEPARATION * (-3 * j - 2 * k), 0, 10.0, RADIUS),
			   ball(LETTER_SEPARATION * (-2 * j - 2 * k), 0, 10.0, RADIUS), // end of 'S'
			   ball(LETTER_SEPARATION * (-6 * j + 2 * k), 0, 10.0, RADIUS), // beginning of 'D'
			   ball(LETTER_SEPARATION * (-6 * j + k), 0, 10.0, RADIUS),
			   ball(LETTER_SEPARATION * (-6 * j), 0, 10.0, RADIUS),
			   ball(LETTER_SEPARATION * (-6 * j - k), 0, 10.0, RADIUS),
			   ball(LETTER_SEPARATION * (-6 * j - 2 * k), 0, 10.0, RADIUS),
			   ball(LETTER_SEPARATION * (-7 * j - 2 * k), 0, 10.0, RADIUS),
			   ball(LETTER_SEPARATION * (-8 * j - k), 0, 10.0, RADIUS),
			   ball(LETTER_SEPARATION * (-8 * j), 0, 10.0, RADIUS),
			   ball(LETTER_SEPARATION * (-8 * j + k), 0, 10.0, RADIUS),
			   ball(LETTER_SEPARATION * (-7 * j + 2 * k), 0, 10.0, RADIUS) // end of 'D'

};

#define UOFA 2
ball uofa[] = {ball(LETTER_SEPARATION * (7 * j + 2 * k), 0, 10.0, RADIUS), // beginning of 'U'
			   ball(LETTER_SEPARATION * (7 * j + k), 0, 10.0, RADIUS),
			   ball(LETTER_SEPARATION * (7 * j), 0, 10.0, RADIUS),
			   ball(LETTER_SEPARATION * (7 * j - k), 0, 10.0, RADIUS),
			   ball(LETTER_SEPARATION * (7 * j - 2 * k), 0, 10.0, RADIUS),
			   ball(LETTER_SEPARATION * (6 * j - 2 * k), 0, 10.0, RADIUS),
			   ball(LETTER_SEPARATION * (5 * j - 2 * k), 0, 10.0, RADIUS),
			   ball(LETTER_SEPARATION * (5 * j - k), 0, 10.0, RADIUS),
			   ball(LETTER_SEPARATION * (5 * j), 0, 10.0, RADIUS),
			   ball(LETTER_SEPARATION * (5 * j + k), 0, 10.0, RADIUS),
			   ball(LETTER_SEPARATION * (5 * j + 2 * k), 0, 10.0, RADIUS), // end of 'U'
			   ball(LETTER_SEPARATION * (3 * j), 0, 10.0, RADIUS), // beginning of 'o'
			   ball(LETTER_SEPARATION * (2 * j), 0, 10.0, RADIUS),
			   ball(LETTER_SEPARATION * (j), 0, 10.0, RADIUS),
			   ball(LETTER_SEPARATION * (j - k), 0, 10.0, RADIUS),
			   ball(LETTER_SEPARATION * (j - 2 * k), 0, 10.0, RADIUS),
			   ball(LETTER_SEPARATION * (2 * j - 2 * k), 0, 10.0, RADIUS),
			   ball(LETTER_SEPARATION * (3 * j - 2 * k), 0, 10.0, RADIUS),
			   ball(LETTER_SEPARATION * (3 * j - k), 0, 10.0, RADIUS), // end of 'o'
			   ball(LETTER_SEPARATION * (-1 * j), 0, 10.0, RADIUS), // beginning of 'f'
			   ball(LETTER_SEPARATION * (-2 * j), 0, 10.0, RADIUS),
			   ball(LETTER_SEPARATION * (-3 * j), 0, 10.0, RADIUS),
			   ball(LETTER_SEPARATION * (-2 * j + k), 0, 10.0, RADIUS),
			   ball(LETTER_SEPARATION * (-2 * j + 2 * k), 0, 10.0, RADIUS),
			   ball(LETTER_SEPARATION * (-3 * j + 2 * k), 0, 10.0, RADIUS),
			   ball(LETTER_SEPARATION * (-2 * j - k), 0, 10.0, RADIUS),
			   ball(LETTER_SEPARATION * (-2 * j - 2 * k), 0, 10.0, RADIUS), // end of 'f'
			   ball(LETTER_SEPARATION * (-5 * j + 2 * k), 0, 10.0, RADIUS), // beginning of 'A'
			   ball(LETTER_SEPARATION * (-6 * j + 2 * k), 0, 10.0, RADIUS),
			   ball(LETTER_SEPARATION * (-7 * j + 2 * k), 0, 10.0, RADIUS),
			   ball(LETTER_SEPARATION * (-7 * j + k), 0, 10.0, RADIUS),
			   ball(LETTER_SEPARATION * (-7 * j), 0, 10.0, RADIUS),
			   ball(LETTER_SEPARATION * (-7 * j - k), 0, 10.0, RADIUS),
			   ball(LETTER_SEPARATION * (-7 * j - 2 * k), 0, 10.0, RADIUS),
			   ball(LETTER_SEPARATION * (-5 * j + k), 0, 10.0, RADIUS),
			   ball(LETTER_SEPARATION * (-5 * j), 0, 10.0, RADIUS),
			   ball(LETTER_SEPARATION * (-5 * j - k), 0, 10.0, RADIUS),
			   ball(LETTER_SEPARATION * (-5 * j - 2 * k), 0, 10.0, RADIUS),
			   ball(LETTER_SEPARATION * (-6 * j), 0, 10.0, RADIUS) // end of 'A'
};

#define JARED 3
ball jared[] = {ball(LETTER_SEPARATION * (9 * j + 3 * k), 0, 10.0, RADIUS), // beginning of 'J'
			    ball(LETTER_SEPARATION * (8 * j + 3 * k), 0, 10.0, RADIUS),
			    ball(LETTER_SEPARATION * (7 * j + 3 * k), 0, 10.0, RADIUS),
			    ball(LETTER_SEPARATION * (6 * j + 3 * k), 0, 10.0, RADIUS),
			    ball(LETTER_SEPARATION * (5 * j + 3 * k), 0, 10.0, RADIUS),
			    ball(LETTER_SEPARATION * (7 * j + 2 * k), 0, 10.0, RADIUS),
			    ball(LETTER_SEPARATION * (7 * j + k), 0, 10.0, RADIUS),
			    ball(LETTER_SEPARATION * (7 * j), 0, 10.0, RADIUS),
			    ball(LETTER_SEPARATION * (8 * j - k), 0, 10.0, RADIUS),
			    ball(LETTER_SEPARATION * (9 * j - k), 0, 10.0, RADIUS), // end of 'J'
			    ball(LETTER_SEPARATION * (3 * j + k), 0, 10.0, RADIUS), // beginning of 'a'
			    ball(LETTER_SEPARATION * (4 * j + k), 0, 10.0, RADIUS),
			    ball(LETTER_SEPARATION * (5 * j), 0, 10.0, RADIUS),
			    ball(LETTER_SEPARATION * (5 * j - k), 0, 10.0, RADIUS),
			    ball(LETTER_SEPARATION * (4 * j - k), 0, 10.0, RADIUS),
			    ball(LETTER_SEPARATION * (3 * j - k), 0, 10.0, RADIUS),
			    ball(LETTER_SEPARATION * (3 * j), 0, 10.0, RADIUS), 
			    ball(LETTER_SEPARATION * (2 * j - k), 0, 10.0, RADIUS), // end of 'a'
			    ball(LETTER_SEPARATION * (-1 * j + k), 0, 10.0, RADIUS), // beginning of 'r'
			    ball(LETTER_SEPARATION * (k), 0, 10.0, RADIUS),
			    ball(LETTER_SEPARATION * (0), 0, 10.0, RADIUS),
			    ball(LETTER_SEPARATION * (-1 * k), 0, 10.0, RADIUS), // end of 'r'
			    ball(LETTER_SEPARATION * (-3 * j + 2 * k), 0, 10.0, RADIUS), // beginning of 'e'
			    ball(LETTER_SEPARATION * (-3 * j + k), 0, 10.0, RADIUS),
			    ball(LETTER_SEPARATION * (-3 * j), 0, 10.0, RADIUS),
			    ball(LETTER_SEPARATION * (-4 * j - k), 0, 10.0, RADIUS),
			    ball(LETTER_SEPARATION * (-5 * j - k), 0, 10.0, RADIUS),
			    ball(LETTER_SEPARATION * (-4 * j + 3 * k), 0, 10.0, RADIUS),
			    ball(LETTER_SEPARATION * (-5 * j + 2 * k), 0, 10.0, RADIUS),
			    ball(LETTER_SEPARATION * (-5 * j + k), 0, 10.0, RADIUS),
			    ball(LETTER_SEPARATION * (-4 * j + k), 0, 10.0, RADIUS), // end of 'e'
			    ball(LETTER_SEPARATION * (-9 * j + 3 * k), 0, 10.0, RADIUS), // beginning of 'd'
			    ball(LETTER_SEPARATION * (-9 * j + 2 * k), 0, 10.0, RADIUS),
			    ball(LETTER_SEPARATION * (-9 * j + k), 0, 10.0, RADIUS),
			    ball(LETTER_SEPARATION * (-9 * j), 0, 10.0, RADIUS),
			    ball(LETTER_SEPARATION * (-9 * j - k), 0, 10.0, RADIUS),
			    ball(LETTER_SEPARATION * (-8 * j - k), 0, 10.0, RADIUS),
			    ball(LETTER_SEPARATION * (-7 * j - k), 0, 10.0, RADIUS),
			    ball(LETTER_SEPARATION * (-7 * j), 0, 10.0, RADIUS),
			    ball(LETTER_SEPARATION * (-8 * j + k), 0, 10.0, RADIUS), // end of 'd'
};

#endif INTERFACE