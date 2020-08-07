#pragma once
#include<chrono>

class Matrix2D;
class Vector;

class LinearSystem {
	
protected:
	int mSize;
	Matrix2D* mpA;
	Vector* mpb;
	LinearSystem() = default;
	LinearSystem(const LinearSystem& otherlinearsystem) =  default;

public:
	LinearSystem( const Matrix2D& matrix, const Vector& vector);
	int getSize() {
		return mSize;
	}
    ~LinearSystem();
	virtual Vector Solve();
	Vector SolveMKL();

};

class Timer
{
private:
	// Type aliases to make accessing nested type easier
	using clock_t = std::chrono::high_resolution_clock;
	using second_t = std::chrono::duration<double, std::ratio<1> >;

	std::chrono::time_point<clock_t> m_beg;

public:
	Timer() : m_beg(clock_t::now())
	{
	}

	void reset()
	{
		m_beg = clock_t::now();
	}

	double elapsed() const
	{
		return std::chrono::duration_cast<second_t>(clock_t::now() - m_beg).count();
	}
};