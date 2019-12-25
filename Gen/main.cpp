#include "Solution.h"


int main()
{
	Solution solution("tsp500.txt");
	std::cout << solution.getResult() << std::endl;
}