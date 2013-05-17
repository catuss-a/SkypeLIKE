#include <iostream>
#include "NinaError.hpp"

#include "BabelServer.hpp"

static int
usage(int ac, char** av, std::string& port, int& family)
{
	if (ac > 3) {
		std::cout << "Usage : " << av[0] << " [port | service_name] [-6]" << std::endl;
		return -1;
	}
	if (ac == 2 && !strcmp(av[1], "-6"))
		family = AF_INET6;
	else if (ac > 1) {
		port = av[1];
		if (ac == 3 && !strcmp(av[2], "-6"))
			family = AF_INET6;
	}
	return 0;
}

int
main(int ac, char** av)
{
	NINA::Init	startup;

	int	family = AF_INET;
	std::string	port("sip");

	if (usage(ac, av, port, family) < 0)
		return 1;
	try {
		BabelServer	server(port, family);
		server.run();
	}
	catch (NINA::Error::SystemError const& e) {
		std::cerr << "Fatal error : " << e.what() << std::endl;
	}
	return 0;
}
