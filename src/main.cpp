#include <iostream>
#include <assert.h>
#include "derivative.h"


//  Test Const value and its derivative
// F(x) = 99
// 'F(x) = 0
bool TestConstIntPostive(void)
{

	bool ret = true;

	typedef ConstInt<99> c;
	ret = (c::eval(0) == 99);
	typedef c::derivative c_d;
	ret = (c_d::eval(0) == 0);

	return ret;
}

//  Test negative Const value and its derivative
// F(x) = -99
// 'F(x) = 0
bool TestConstIntNegative(void)
{

	bool ret = true;

	typedef ConstInt<-99> c;
	typedef c::derivative c_d;

	ret = (c::eval(0) == -99);
	
	ret = (c_d::eval(0) == 0);

	return ret;
}

//  Test add operation and its derivative
// F(x) = 99 + 88
// 'F(x) = 0
bool TestAddOperationWithDerivative(void)
{
	bool ret = true;

	typedef ConstInt<99> c1;
	typedef ConstInt<88> c2;
	typedef Add<c1, c2> y;

	ret = (y::eval(0) == (88+99));
	typedef y::derivative y_d;

	ret = (y_d::eval(0) == 0);


	return ret;
}


//  Test mul operation and its derivative
// F(x) = 99 * 88
// 'F(x) = 0
bool TestMulOperationWithDerivative(void)
{
	bool ret = true;

	typedef ConstInt<99> c1;
	typedef ConstInt<88> c2;
	typedef Mul<c1, c2> y;

	ret = (y::eval(0) == (88*99));
	typedef y::derivative y_d;

	ret = (y_d::eval(0) == 0);


	return ret;
}

//  Test Negative operation and its derivative
// F(x) = -99
// 'F(x) = 0
bool TestNegWithDerivative(void)
{
	bool ret = true;

	typedef ConstInt<99> c1;
	typedef Neg<c1> y;

	ret = (y::eval(0) == (0 - 99));
	typedef y::derivative y_d;

	ret = (y_d::eval(0) == 0);


	return ret;
}

//  Test Power operation and its derivative
// F(x) = x^3
// 'F(x) = 3*x^2

bool TestMonomialWithDerivative(void)
{
	bool ret = true;

	typedef Monomial<3> y;

	ret = (y::eval(2) == (2^3));

	typedef y::derivative y_d;

	ret = (y_d::eval(2) == (3 * (2^2)));


	return ret;
}

//  Test Power operation with negation and its derivative
// F(x) = -x^3
// 'F(x) = -3*x^2

bool TestMonomialWithNegativeithDerivative(void)
{
	bool ret = true;

	typedef Monomial<3> y;
	typedef Neg<y> y_n;

	ret = (y_n::eval(2) == -8);

	typedef y_n::derivative y_n_d;

	ret = (y_n_d::eval(2) ==  -12);


	return ret;
}

//  Test sin operation and its derivative
// F(x) = sin(x)
// 'F(x) = cos(x)
bool TestSinwithDerivative(void)
{
	bool ret = true;

	typedef Sin y;
	typedef y::derivative y_d;

	ret = (y::eval(M_PI/2) == std::sin(M_PI/2));

	ret = (y_d::eval(M_PI/2) ==  std::cos(M_PI/2));

	return ret;
}

//  Test cos operation and its derivative
// F(x) = cos(x)
// 'F(x) = -sin(x)
bool TestCoswithDerivative(void)
{
	bool ret = true;

	typedef Cos y;
	typedef y::derivative y_d;

	ret = (y::eval(M_PI/2) == std::cos(M_PI/2));

	ret = (y_d::eval(M_PI/2) ==  (0.F - std::sin(M_PI/2)));

	return ret;
}

// F(x) =  x^3*sin(x)+x*sin(x)
// https://www.derivative-calculator.net/#expr=x%5E3sin%28x%29%20%2B%20xSin%28x%29
// 'F(x) = (3*x^2+1)*sin(x)+(x^3+x)*cos(x)
bool TestMixOfOperationswithDerivative(void)
{
	bool ret = true;

	typedef Sin y;
	typedef Monomial<3> n_3;
	typedef Monomial<1> n_1;
	typedef Mul<n_3, y> left;
	typedef Mul<n_1, y> right;
	typedef Add<left,right> func;

	typedef func::derivative func_d;

	double x = M_PI/4;
	double expected_result = (3*(std::pow(x,2))+1)*std::sin(x)+((std::pow(x,3))+x)*std::cos(x);

	ret = (func_d::eval(M_PI/4) == expected_result);

	
	return ret;
}



 int main ( int argc , char *argv[] ) 
{
	UNUSED(argc);
	UNUSED(argv);

	assert(TestConstIntPostive());

	assert(TestConstIntNegative());

	assert(TestAddOperationWithDerivative());

	assert(TestMulOperationWithDerivative());

	assert(TestNegWithDerivative());

	assert(TestMonomialWithNegativeithDerivative());

	assert(TestSinwithDerivative());

	assert(TestCoswithDerivative());

	assert(TestMixOfOperationswithDerivative());

	std::cout << "OK" << std::endl;


	return 0;
}
