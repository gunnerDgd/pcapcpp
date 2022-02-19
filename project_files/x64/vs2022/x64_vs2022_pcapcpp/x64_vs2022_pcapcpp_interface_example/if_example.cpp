#include <pcapcpp/interface/interface.hpp>
#include <pcapcpp/interface/enumerator.hpp>

#include <iostream>

int main()
{
	pcapcpp::interface_enumerator	     if_enum;
	std::cout << "Interface Count : " << if_enum.count() << std::endl;

	pcapcpp::network_interface			 if_interface = if_enum[0];
	std::cout << "Interface Name : "  << if_interface.description() << std::endl;
}