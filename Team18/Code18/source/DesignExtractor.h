#pragma once

#include <unordered_set>
#include <unordered_map>
#include <string>

class DesignExtractor {
public:
	static void extractDesign();

private:
	//static void extractFollowStar();
	static void extractParentStar();
};