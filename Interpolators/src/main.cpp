#include <iostream>
#include <Interpolator.h>	
#include <Vector3.h>	

template<typename T>
void print(T && arg)
{
	std::cout << arg << std::endl;
}


int main()
{

	aux::CosineInterpolator<double, Vector3> intr;

	intr.add(1, { 1,1,1 });
	intr.add(2, { 1,5,1 });
	intr.add(3, { 10,1,1 });

	auto current_vector = intr.get(2.5);


	aux::CosineInterpolator<int,double> interpolator;
	interpolator.add(1, 1);
	interpolator.add(3, 4);
	interpolator.add(5, 8);

	interpolator.validate();

	auto value = interpolator.get(2);
	print(value);

	value= interpolator.get(-1);
	print(value);

	value = interpolator.get(3);
	print(value);

	value = interpolator.get(4);
	print(value);

}

