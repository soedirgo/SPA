#pragma once
#include <string>
#include <vector>
namespace std {
    template <>
    struct hash<std::vector<std::string>> {
        size_t operator()(const vector<string>& v) const {
            std::hash<string> hasher;
            size_t seed = 0;
            for (string i : v) {
                seed ^= hasher(i) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            }
            return seed;
        }
    };
}
