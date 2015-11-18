#ifndef GRAPHICS_ENGINE
#define GRAPHICS_ENGINE

// headers-------------------------------------------------------------------------
#include <list>
using namespace std;

#include "MathTools.h"


// class declarations-----------------------------------------------------------------
class sphere
{
public:

	vector r;
	double radius;
	COLORREF color;
};

list<sphere> sphereList;

void SetObservationPoint(vector &r_observer, vector &o_observer);

vector Perspectivefy(






#endif GRAPHICS_ENGINE