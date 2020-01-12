#include "Solution.h"


int main()
{
	Solution solution("tsp1000.txt");
	std::cout << solution.getResult() << std::endl;
}