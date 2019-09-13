#pragma once
#include <string>
#include <vector>
#include <utility>
#include <list>
#include "Query.h"

namespace Evaluator {
	std::list<std::string> evalQuery(Query q);
}
