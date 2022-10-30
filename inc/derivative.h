#ifndef DERIVATIVE_H
#define DERIVATIVE_H

#include <cmath>
#define UNUSED(expr) do { (void)(expr); } while (0)

struct Cos;
struct Sin;


template <int value>
struct ConstInt
{

	using derivative = ConstInt<0>;

	static constexpr double eval(const double x)
	{
		UNUSED(x);
		return value;
	}
};

template <typename Left, typename Right>
struct Add
{
	using derivative = Add<typename Left::derivative, typename Right::derivative>;

	static constexpr double eval(const double x)
	{

		return Left::eval(x) + Right::eval(x);
	}
};

template <typename Left, typename Right>
struct Mul
{
	using derivative = Add<Mul<typename Left::derivative, Right>, Mul<Left, typename Right::derivative>>;

	static constexpr double eval(const double x)
	{

		return Left::eval(x) * Right::eval(x);
	}
};

template <typename value>
struct Neg
{

	using derivative = Neg<typename value::derivative>;

	static constexpr double eval(const double x)
	{

		return 0 - value::eval(x);
	}
};

template <int Exponent>
struct Monomial
{

	using derivative = Mul<ConstInt<Exponent>, Monomial<Exponent - 1>>;

	static_assert(0 <= Exponent, "Exponent must be more than Zero!");
	static constexpr double eval(const double x)
	{
		return std::pow(x, Exponent);
	}
};


struct Sin
{

	using derivative = Cos;

	static inline double eval(const double x)
	{
		return std::sin(x);
	}

	
};

struct Cos
{
	using derivative = Neg<Sin>;

	static inline double eval(const double x)
	{
		return std::cos(x);
	}

	
};

#endif //DERIVATIVE_H