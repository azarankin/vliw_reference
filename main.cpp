#include <iostream>
#include <cstdlib>
int main()
{
	std::cout << "hello world main2\n" ;

	int status = std::system("./main1");
	std::cout << "main1 status was " << status << "\n";
	
	return 0;
}