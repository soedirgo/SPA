#pragma once
#include <string>
#include <vector>

struct VectorHash {
	std::size_t operator()(std::vector<std::string> const& vec) const {
		std::size_t seed = vec.size();
		std::hash<std::string> strHasher;
		for (auto& i : vec) {
			auto a = strHasher(i);
			seed ^= a + 0x9e3779b9 + (seed << 6) + (seed >> 2);
		}
		return seed;
	}
};

struct VectorDoubleStringHash {
	size_t operator()(const std::vector<std::string >& x) const
	{
		std::hash<std::string> strHasher;

		auto a = strHasher(x.front());
		auto b = strHasher(x.back());
		return a >= b ? a * a + a + b : a + b * b;
	}
};

struct VectorSingleStringHash {
	size_t operator()(const std::vector<std::string >& x) const
	{
		std::hash<std::string> strHasher;
		auto a = strHasher(x.front());
		return a;
	}
};


