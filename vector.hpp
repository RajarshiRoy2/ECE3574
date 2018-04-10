#ifndef VECTOR_HPP
#define VECTOR_HPP
#include <vector>
#include <mutex>
using namespace std;

template<typename T>
class OutputVector 
{

public:
	void append(const T& data)
	{
		lock_guard<mutex>lock(the_mutex);
		the_vec.push_back(data);

	}
	vector<T> asVector() 
	{
		lock_guard<mutex>lock(the_mutex);
		return the_vec;
	}
	T operator[](size_t index)
	{
		lock_guard<mutex>lock(the_mutex);
		if (index < the_vex.size())
			return the_vec[index];
	}
	size_t size()
	{
		lock_guard<mutex>lock(the_mutex);
		return the_vec.size();
	}
	vector<T> the_vec;
private:
	
	mutable mutex the_mutex;
};

#endif // !VECTOR_HPP
