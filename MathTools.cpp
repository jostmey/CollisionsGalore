// headers---------------------------------------------------------------
#include <math.h>
#include <memory.h>
#include "MathTools.h"


// utility functions-------------------------------------------------------
void swap(double *p1, double *p2)
{
	double sto = *p1;
	*p1 = *p2;
	*p2 = sto;
}


// vector definitions-----------------------------------------------------
vector::vector()
{
	x = 0;
	y = 0;
	z = 0;
}

vector::vector(const double &x_)
{
	x = x_;
	y = x_;
	z = x_;
}

vector::vector(const double &x_, const double &y_, const double &z_)
{
	x = x_;
	y = y_;
	z = z_;
}

vector vector::operator = (const double &x) const
{
	return (i + j + k) * x;
}

double vector::operator * (const vector &v) const 
{
	return x * v.x + y * v.y + z * v.z;
}

vector vector::operator * (const double &c) const
{
	return vector(x * c, y * c, z * c);
}

vector vector::operator / (const double &c) const
{
	return vector(x / c, y / c, z / c);
}

vector::operator *= (const double &c)
{
	x *= c;
	y *= c;
	z *= c;
}

vector::operator *= (const matrix3x3 &M)
{
	vector v(x, y, z);
	
	v = M * v;

	x = v.x;
	y = v.y;
	z = v.z;
}


vector::operator /= (const double &c)
{
	x /= c;
	y /= c;
	z /= c;
}

vector vector::operator + (const vector &v) const
{
	return vector(x + v.x, y + v.y, z + v.z);
}

vector vector::operator - (const vector &v) const
{
	return vector(x - v.x, y - v.y, z - v.z);
}

vector::operator += (const vector &v)
{
	x += v.x;
	y += v.y;
	z += v.z;
}

vector::operator -= (const vector &v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
}

vector vector::operator ^ (const vector &v) const
{
	return vector(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
}

double Magnitude(const vector &v)
{
	return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

vector Hat(vector v)
{
	return v / Magnitude(v);
}

vector operator * (const double &c, const vector &v)
{
	return vector(v.x * c, v.y * c, v.z * c);
}


// matrix definitions---------------------------------------------------------
matrix3x3::matrix3x3()
{
	e11 = 0;
	e12 = 0;
	e13 = 0;
	e21 = 0;
	e22 = 0;
	e23 = 0;
	e31 = 0;
	e32 = 0;
	e33 = 0;
}

matrix3x3::matrix3x3(const double &e11_, const double &e12_, const double &e13_,
					 const double &e21_, const double &e22_, const double &e23_,
					 const double &e31_, const double &e32_, const double &e33_)
{
	e11 = e11_;
	e12 = e12_;
	e13 = e13_;
	e21 = e21_;
	e22 = e22_;
	e23 = e23_;
	e31 = e31_;
	e32 = e32_;
	e33 = e33_;
}

matrix3x3 matrix3x3::operator * (const matrix3x3 &X) const
{
	return matrix3x3(e11 * X.e11 + e12 * X.e21 + e13 * X.e31, e11 * X.e12 + e12 * X.e22 + e13 * X.e32, e11 * X.e13 + e12 * X.e23 + e13 * X.e33,
				     e21 * X.e11 + e22 * X.e21 + e23 * X.e31, e21 * X.e12 + e22 * X.e22 + e23 * X.e32, e21 * X.e13 + e22 * X.e23 + e23 * X.e33,
					 e31 * X.e11 + e32 * X.e21 + e33 * X.e31, e31 * X.e12 + e32 * X.e22 + e33 * X.e32, e31 * X.e13 + e32 * X.e23 + e33 * X.e33);
}

matrix3x3 matrix3x3::operator * (const double &c) const
{
	return matrix3x3(e11 * c, e12 * c, e13 * c,
			         e21 * c, e22 * c, e23 * c,
				     e31 * c, e32 * c, e33 * c);
}

matrix3x3 matrix3x3::operator / (const double &c) const
{
	return matrix3x3(e11 / c, e12 / c, e13 / c,
			         e21 / c, e22 / c, e23 / c,
				     e31 / c, e32 / c, e33 / c);
}

matrix3x3::operator *= (const double &c)
{
	e11 *= c; 
	e12 *= c;
	e13 *= c;
	e21 *= c;
	e22 *= c;
	e23 *= c;
	e31 *= c;
	e32 *= c;
	e33 *= c;
}

matrix3x3::operator /= (const double &c)
{
	e11 /= c; 
	e12 /= c;
	e13 /= c;
	e21 /= c;
	e22 /= c;
	e23 /= c;
	e31 /= c;
	e32 /= c;
	e33 /= c;
}

matrix3x3 matrix3x3::operator + (const matrix3x3 &X) const
{
	return matrix3x3(e11 + X.e11, e12 + X.e12, e13 + X.e13,
			         e21 + X.e21, e22 + X.e22, e23 + X.e23,
			         e31 + X.e31, e32 + X.e32, e33 + X.e33);
}

matrix3x3 matrix3x3::operator - (const matrix3x3 &X) const
{
	return matrix3x3(e11 - X.e11, e12 - X.e12, e13 - X.e13,
			         e21 - X.e21, e22 - X.e22, e23 - X.e23,
				     e31 - X.e31, e32 - X.e32, e33 - X.e33);
}

matrix3x3::operator += (const matrix3x3 &X)
{
	e11 += X.e11; 
	e12 += X.e12;
	e13 += X.e13;
	e21 += X.e21;
	e22 += X.e22;
	e23 += X.e23;
	e31 += X.e31;
	e32 += X.e32;
	e33 += X.e33;
}

matrix3x3::operator -= (const matrix3x3 &X)
{
	e11 -= X.e11; 
	e12 -= X.e12;
	e13 -= X.e13;
	e21 -= X.e21;
	e22 -= X.e22;
	e23 -= X.e23;
	e31 -= X.e31;
	e32 -= X.e32;
	e33 -= X.e33;
}

double Det(const matrix3x3 &X)
{
	return X.e11 * X.e22 * X.e33
		 + X.e12 * X.e23 * X.e31 
		 + X.e13 * X.e21 * X.e32
		 - X.e11 * X.e23 * X.e32 
		 - X.e12 * X.e21 * X.e33 
		 - X.e13 * X.e22 * X.e31;
}

matrix3x3 Inverse(const matrix3x3 &X)
{
	matrix3x3 Y; // Y will be the invserse

	// computing the matrix of cofactors
	Y.e11 = X.e22 * X.e33 - X.e23 * X.e32;
	Y.e12 = X.e23 * X.e31 - X.e21 * X.e33;
	Y.e13 = X.e21 * X.e32 - X.e22 * X.e31;

	Y.e21 = X.e13 * X.e32 - X.e12 * X.e33;
	Y.e22 = X.e11 * X.e33 - X.e13 * X.e31;
	Y.e23 = X.e12 * X.e31 - X.e11 * X.e32;

	Y.e31 = X.e12 * X.e23 - X.e13 * X.e22;
	Y.e32 = X.e13 * X.e21 - X.e11 * X.e23;
	Y.e33 = X.e11 * X.e22 - X.e12 * X.e21;
	// done computing the matrix of cofactors

	// transposing
	swap(&Y.e12, &Y.e21);
	swap(&Y.e13, &Y.e31);
	swap(&Y.e23, &Y.e32);
	// done transposing

	Y /= Det(X); // dividing each element by the determinant of X

	return Y; // returning the inverse of X
}

matrix3x3 operator * (const double &c, const matrix3x3 &X)
{
	return matrix3x3(c * X.e11, c * X.e12, c * X.e13,
			         c * X.e21, c * X.e22, c * X.e23,
				     c * X.e31, c * X.e32, c * X.e33);
}

vector operator * (const matrix3x3 &X, const vector &v)
{
	return vector(X.e11 * v.x + X.e12 * v.y + X.e13 * v.z,
			      X.e21 * v.x + X.e22 * v.y + X.e23 * v.z,
			      X.e31 * v.x + X.e32 * v.y + X.e33 * v.z);
}

vector operator * (const vector &v, const matrix3x3 &X)
{
	return vector(X.e11 * v.x + X.e21 * v.y + X.e31 * v.z,
			      X.e12 * v.x + X.e22 * v.y + X.e32 * v.z,
			      X.e13 * v.x + X.e23 * v.y + X.e33 * v.z);
}

// assorted math function definitions-----------------------------------------------------------------
double Maximum(double x, double y)
{
	if(y > x)
		return y;

	return x;
}

double Sign(double x)
{
	if(x < 0.0)
		return -1.0;

	return 1.0;
}

double Sine(double x)
{
	int index = (int)(2 * SIZE_OF_SIN_TABLE * x / PI),
		sign = 1;

	if(x < 0.0)
	{
		sign = -1;
		index *= -1;
	}

	index %= 4 * SIZE_OF_SIN_TABLE;

	switch(index / SIZE_OF_SIN_TABLE)
	{
	case 0:
		return sign * sinTable[index];
	case 1:
		return sign * sinTable[2 * SIZE_OF_SIN_TABLE - index - 1];
	case 2:
		return -sign * sinTable[index - 2 * SIZE_OF_SIN_TABLE];
	case 3:
		return -sign * sinTable[4 * SIZE_OF_SIN_TABLE - index - 1];
	}

	return 2.0; // return error
}

double Cosine(double x)
{
	return Sine(x + PI / 2);
}

matrix3x3 R_x(double o)
{
	return matrix3x3(1.0, 0.0           , 0        ,
				     0.0, Cosine(o)     , Sine(o)  ,
				     0.0, -1.0 * Sine(o), Cosine(o));
}

matrix3x3 R_y(double o)
{
	return matrix3x3(Cosine(o), 0.0, -1.0 * Sine(o),
			         0.0      , 1.0, 0.0           , 
				     Sine(o)  , 0.0, Cosine(o)     );
}

matrix3x3 R_z(double o)
{
	return matrix3x3(Cosine(o)     , Sine(o)  , 0.0,
			         -1.0 * Sine(o), Cosine(o), 0.0,
				     0.0           , 0.0      , 1.0);
}

matrix3x3 R_v(double o, vector v)
{
	if(v.x == 0.0 && v.y == 0.0 && v.z == 0)
		return I;

	v = Hat(v);

	return matrix3x3 (Cosine(o) + (1 - Cosine(o)) * v.x * v.x, (1 - Cosine(o)) * v.x * v.y - Sine(o) * v.z, (1 - Cosine(o)) * v.x * v.z + Sine(o) * v.y,
				     (1 - Cosine(o)) * v.x * v.y + Sine(o) * v.z, Cosine(o) + (1 - Cosine(o)) * v.y * v.y, (1 - Cosine(o)) * v.y * v.z - Sine(o) * v.x,
				     (1 - Cosine(o)) * v.x * v.z - Sine(o) * v.y, (1 - Cosine(o)) * v.y * v.z + Sine(o) * v.x, Cosine(o) + (1 - Cosine(o)) * v.z * v.z);
}

double Absolute(double x)
{
	if(x < 0.0)
		return -x;

	return x;
}