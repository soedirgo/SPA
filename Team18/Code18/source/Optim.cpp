#include "Optim.h"
#include "Result.h"
#include <algorithm>
#include <limits>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;
namespace Evaluator {
    namespace {
        unordered_map<int, int> id;

        int ufFind(int i) {
            if (i == id[i])
                return i;
            else
                return ufFind(id[i]);
        }

        void ufUnion(int i, int j) {
            int iRep = ufFind(i);
            int jRep = ufFind(j);
            id[max(iRep, jRep)] = min(iRep, jRep);
        }
    }

    vector<vector<Result>> group(vector<Result>& results,
                                 vector<string>& selSyns) {
        // separate result tables with no synonym
        vector<Result> noSynGroup;
        vector<Result> resultsWithSynonyms;
        for (const auto& result : results) {
            if (result.getSynonyms().size())
                resultsWithSynonyms.push_back(result);
            else
                noSynGroup.push_back(result);
        }
        if (!noSynGroup.size())
            noSynGroup = { Result(true, {}, {}) };

        // get all synonyms
        unordered_map<string, int> synonyms;
        for (const auto& result : resultsWithSynonyms) {
            for (const auto& syn : result.getSynonyms())
                if (!synonyms.count(syn.first))
                    synonyms[syn.first] = synonyms.size();
        }

        // initialize synonym connections
        for (size_t i = 0; i < synonyms.size(); ++i) {
            id[i] = i;
        }

        // build synonym connections
        if (selSyns[0] != "BOOLEAN")
            for (const auto& syn : selSyns) {
                ufUnion(synonyms[selSyns[0]], synonyms[syn]);
            }
        for (const auto& result : resultsWithSynonyms) {
            vector<string> resultSynonyms;
            for (const auto& syn : result.getSynonyms()) {
                resultSynonyms.push_back(syn.first);
            }
            if (resultSynonyms.size() == 2)
                ufUnion(synonyms[resultSynonyms[0]], synonyms[resultSynonyms[1]]);
        }

        // break results into groups
        unordered_map<int, int> synToGroup;
        vector<vector<Result>> groups;
        // no synonym results group is the first entry
        synToGroup[-2] = synToGroup.size();
        groups.push_back(noSynGroup);
        // select synonym results group is the second entry
        // if BOOLEAN, add a dummy
        if (selSyns[0] == "BOOLEAN") {
            synToGroup[-1] = synToGroup.size();
            groups.push_back({ Result(true, {}, {}) });
        }
        groups.push_back({});
        // add other groups (including select synonyms group, if not BOOLEAN)
        // assume first group is always select synonyms (if not BOOLEAN)
        for (const auto& it : id) {
            if (it.first == ufFind(it.first)) {
                synToGroup[it.first] = synToGroup.size();
                groups.push_back({});
            }
        }
        for (const auto& result : resultsWithSynonyms) {
            string syn = result.getSynonyms().begin()->first;
            int groupIdx = synToGroup[ufFind(synonyms[syn])];
            groups[groupIdx].push_back(result);
        }

        return groups;
    }

    void sort(vector<Result>& results) {

        vector<Result> temp = results;
        unordered_set<string> currentSynonyms;
        // maps result idx to its merge order, first to last
        unordered_map<int, int> resultOrder;

        // resolve ordering
        for (size_t i = 0; i < results.size(); ++i) {
            size_t nextResultIdx = -1;
            int nextResultNewSynsCount = numeric_limits<int>::max();
            size_t nextResultSize = numeric_limits<int>::max();
            // get best candidate for next result table to merge
            for (size_t j = 0; j < results.size(); ++j) {
                // only consider result tables that hasn't been included
                if (!resultOrder.count(j)) {
                    // get num of new synonyms of candidate
                    int newSynsCount = 0;
                    for (auto& syn : results[j].getSynonyms())
                        if (!currentSynonyms.count(syn.first))
                            ++newSynsCount;
                    // get size of result table of candidate
                    size_t size = results[j].getResults().size();
                    // update if smaller num of new synonyms OR equal
                    // num AND size is smaller
                    if (newSynsCount < nextResultNewSynsCount
                        || (newSynsCount == nextResultNewSynsCount
                            && size < nextResultSize)) {
                        nextResultIdx = j;
                        nextResultNewSynsCount = newSynsCount;
                        nextResultSize = results[j].getResults().size();
                    }
                }
            }
            // add new synonyms to currentSynonyms
            for (auto& syn : results[nextResultIdx].getSynonyms()) {
                currentSynonyms.insert(syn.first);
            }
            // update resultOrder with nextResultIdx
            resultOrder[nextResultIdx] = resultOrder.size();
        }

        // sort results according to ordering
        for (auto& it : resultOrder) {
            results[it.second] = temp[it.first];
        }
    }
} // namespace Evaluator
