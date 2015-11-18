// headers-------------------------------------------------------
#include <math.h>
#include "PhysicsEngine.h"


// ball defintion-------------------------------------------------
ball::ball()
{
	mass = 10;
	radius = 0;
	r_x1 = radius * i + r;
	r_y1 = radius * j + r;
	r_z1 = radius * k + r;
	r_x2 = -radius * i + r;
	r_y2 = -radius * j + r;
	r_z2 = -radius * k + r;
}

ball::ball(const vector &r_, const vector &w_, double mass_, double radius_)
{
	r = r_;
	w = w_;
	mass = mass_;
	radius = radius_;
	r_x1 = radius * i + r;
	r_y1 = radius * j + r;
	r_z1 = radius * k + r;
	r_x2 = -radius * i + r;
	r_y2 = -radius * j + r;
	r_z2 = -radius * k + r;
}

void RepositionBall(ball &ball, const vector &r) // This function moves a ball to the given location. It also resets the balls x, y, and axis
{
	ball.r = r;
	ball.r_x1 = ball.radius * i + ball.r;
	ball.r_y1 = ball.radius * j + ball.r;
	ball.r_z1 = ball.radius * k + ball.r;
	ball.r_x2 = -ball.radius * i + ball.r;
	ball.r_y2 = -ball.radius * j + ball.r;
	ball.r_z2 = -ball.radius * k + ball.r;
}

double DoCollide(const ball &ball1, const ball &ball2)
{
	// at the moment the two balls collide then
	// [x_1 - x_2 + (v_x1 - v_x2)t]^2 + [y_1 - y_2 + (v_y1 - v_y2)t]^2
	// + [z_1 - z_2 + (v_z1 - v_z2)t]^2 = (r_1 - r_2)^2 . Thus, we can
	// use the quadratic formula to solve for t. If the soultion for t is
	// complex then the two balls will not collide

	// computing a, b, and c (the variables used in the quadratic formula)
	double a = (ball1.v - ball2.v) * (ball1.v - ball2.v);
	
	double b = 2 * (ball1.v - ball2.v) * (ball1.r - ball2.r);

	double c = (ball1.r - ball2.r) * (ball1.r - ball2.r)
			 - (ball1.radius + ball2.radius) * (ball1.radius + ball2.radius);
	// done computing a, b, and c

	double sto = b * b - 4 * a * c; // computing the part of the quadratic formula underneath the radical sign

	if(sto < 0.0) 	  // the solution to t is complex iff b^2 - 4ac < 0
		return -1.0f; // since the solution is complex then the two balls will never collide

	// There are two solutions for t. So what do these two solutions
	// represent? Which solution do we want? Well, the eqaution that we are
	// solving assumes the two balls can pass through each other.
	// So one solution corresponds to when the two ball first begin to
	// overlap and the other solution corresponds to when the two balls 
	// have just finished passing through each other. Let t1 and t2 be
	// the two solutions. Let t1 be the solution for when the two ball
	// first start to overlap. Then t1 < t2. So...

	sto = (- b - sqrt(sto)) / (2 * a);

	if(sto < 0.0) // check to make sure the collision will happen. It could be
				// that the collision was in the past!
		return -1.0f;

	return sto; // returning the solution
}

void Translate(ball &ball, double dt)
{
	// the below code rotates r_x, r_y, and r_z around vector w
	double o = Magnitude(ball.w) * dt;
	
	ball.r_x1 = ball.radius * Hat(R_v(o, ball.w) * (ball.r_x1 - ball.r));
	ball.r_y1 = ball.radius * Hat(R_v(o, ball.w) * (ball.r_y1 - ball.r));
	ball.r_z1 = ball.radius * Hat(R_v(o, ball.w) * (ball.r_z1 - ball.r));

	ball.r_x2 = -1 * ball.r_x1;
	ball.r_y2 = -1 * ball.r_y1;
	ball.r_z2 = -1 * ball.r_z1;

	ball.r_x1 += ball.r + ball.v * dt;
	ball.r_y1 += ball.r + ball.v * dt;
	ball.r_z1 += ball.r + ball.v * dt;

	ball.r_x2 += ball.r + ball.v * dt;
	ball.r_y2 += ball.r + ball.v * dt;
	ball.r_z2 += ball.r + ball.v * dt;
	// done rotating

	ball.r += ball.v * dt; // translate the ball
}

void ResolveCollision(ball &ball1, ball &ball2) // I'd like to say that I derived the formulas used by this function. But that would be a lie. I used the book "Physics for Game Developers" by Bourg to help guide me through the equations.
{
    // Okay, the first thing that needs done is to compute the relative velocity at the point of impact.
	// This computation must takes into account both angular and linear momentum.
	vector v_rel, // relative velocity
		   r1, // vector that streches from ball1's center of gravity to the point of impact
		   r2; // vector that streches from ball2's center of gravity to the point of impact

	r1 = ball1.radius / (ball1.radius + ball2.radius) * (ball2.r - ball1.r);
	r2 = ball1.radius / (ball1.radius + ball2.radius) * (ball1.r - ball2.r);

	v_rel = ball1.v + (ball1.w ^ r1) - ball2.v - (ball2.w ^ r2);
	// So the above computation wasn't to bad.


	// let us compute the unit vector normal to the colliding surfaces
	vector n = -1 * Hat(r1); // <- for some reason I need a negative sign. If its not here then the collisions sometimes look funcky
	// done

	
	// computing the vector tanget to the the colliding surfaces
	vector t = Hat((n ^ v_rel) ^ n);
	// done


	// The rotational inertia is...
	double I1 = 2.0 / 5.0 * ball1.mass * ball1.radius * ball1.radius, // This equation assume the sphere are solid and of uniform density
		   I2 = 2.0 / 5.0 * ball1.mass * ball2.radius * ball2.radius;
	// done computing rotational inertia


	// The below code computes the impulse
	double J = -1 * (v_rel * n) * (Elasticty + 1) / (1/ball1.mass + 1/ball2.mass + (n * ((r1 ^ n / I1) ^ r1)) + (n * ((r2 ^ n / I2) ^ r2)));
	// done computing the impluse


	// And finally we modify the velocities.
	ball1.v += (J * n + (u_Friction * J * t)) / ball1.mass;
	ball2.v -= (J * n + (u_Friction * J * t)) / ball2.mass;

	ball1.w += ((r1 ^ (J * n + (u_Friction * J * t))) / I1);
	ball2.w += ((r2 ^ (J * n + (u_Friction * J * t))) / I2);
	// done
}
