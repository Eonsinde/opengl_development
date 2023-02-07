/**
	* This class is used to send data down to an intended shader
*/
#ifndef __UNIFORM_H__
#define __UNIFORM_H__

#include <vector>

template <typename T>
class Uniform
{
private:
	Uniform();
	Uniform(const Uniform&);
	Uniform& operator=(const Uniform&);
	~Uniform();

public:

	static void Set(unsigned int slot, T* inputArray, unsigned int arrayLength);
	// for single values like int, float, double
	static void Set(unsigned int slot, const T& value);
	static void Set(unsigned int slot, std::vector<T>& inputArray);
};

#endif

