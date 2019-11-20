#ifndef COLORS_HPP
#define COLORS_HPP

namespace colors {
	const std::string RED      = "\u001b[31m";
	const std::string GREEN    = "\u001b[32m";
	const std::string YELLOW   = "\u001b[33m";
	const std::string PURPLE   = "\u001b[35m";
	const std::string CYAN     = "\u001b[36m";

	const std::string INTCOLOR = RED;
	const std::string EXTCOLOR = GREEN;
	const std::string CONCOLOR = YELLOW;
	const std::string INPUT    = PURPLE;
	const std::string OUTPUT   = CYAN;

	const std::string RESET    = "\u001b[39;49m";
}

#endif
