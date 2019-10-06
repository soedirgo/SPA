#pragma once
#include <string>
#include <vector>

struct VectorHash {
	size_t operator()(const std::vector<std::string >& x) const
	{
		std::hash<std::string> strHasher;

		auto a = strHasher(x.front());
		auto b = strHasher(x.back());
		return a >= b ? a * a + a + b : a + b * b;
	}
};

