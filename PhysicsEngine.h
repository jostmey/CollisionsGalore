// Okay, so this is really where all the magic is at. The below functions conserves
// linear momentum, angular momentum, and energy to compute the trajectories of colliding
// spheres. The code assumes the spheres are solid and of uniform density. I would like to
// claim that all the code below is original, that I derived the formulas myself. But that
// would be a lie. I used the book 'Physics for Game Developers' by Bourg AS A GUIDE for 
// creating the function 'ResolveCollision'. However, I derived all the equations used in
// the other functions on this page as well as in the rest of my program.


#ifndef PHYSICS_ENGINE
#define PHYSICS_ENGINE

// headers-----------------------------------------------------------------------------
#include "MathTools.h"


// physical constants-----------------------------------------------------------------
#define Elasticty 1.0 // The elasticity between the balls
#define u_Friction 0.1 // The coefficient of friction between the balls. If this is
					   // set to zero then there will be no transfer of angular momentum
					   // from one ball to another


// spherical mass decleration---------------------------------------------------------
class ball
{
public:

	ball();
	ball(const vector &r_, const vector &w_, double mass_, double radius_);

	double mass, radius;

	vector r, // postion 
		   v, // velocity
		   w, // angular velocity (omega)
		   r_x1, // The below three vectors specify the ball's x, y, and z axis.
		   r_y1,
		   r_z1,
		   r_x2, // The below three vectors specify the ball's negative x, y, and z axis
		   r_y2,
		   r_z2;
};

double DoCollide(const ball &ball1, const ball &ball2); // If the two balls will collide, then this function 
														// will return the number of seconds it will take until
														// the two balls to collide. Otherwise, if the two balls
														// never collide then it will return -1.0

void Translate(ball &ball, double dt); // This function translates and rotates the balls.
									   // The amount of rotation and translation depends upon dt.

void ResolveCollision(ball &ball1, ball &ball2); // This function handles the collision between the two balls.
												 // It recomputes the ball's velocity and angular velocity.
												 // It is important to know that after calling ResolveCollision
												 // that any information obtained from DoCollide is rendered
												 // void. Thus, after calling ResolveCollide, the only way
												 // to know if two balls collide is to recall DoCollide.												 
												 // NOTE: this function assumes the two balls are in contact!

void RepositionBall(ball &ball, const vector &r); // This function repositions a ball according to parameter 'const vector &r'.
											      // It also resets the spheres x, y, and z axis.

#endif