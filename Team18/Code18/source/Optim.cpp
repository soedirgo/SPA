#include "Optim.h"
#include "Result.h"
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
            id[jRep] = iRep;
        }
    }

    vector<vector<Result>> group(vector<Result> results,
                                 vector<string> selSyns) {
        // separate result tables with no synonym
        vector<Result> noSynGroup;
        vector<Result> resultsWithSynonyms;
        for (auto& result : results) {
            if (result.getSynonyms().size())
                resultsWithSynonyms.push_back(result);
            else
                noSynGroup.push_back(result);
        }
        if (!noSynGroup.size())
            noSynGroup = { Result(true, {}, {}) };

        // get all synonyms
        unordered_map<string, int> synonyms;
        for (auto& result : resultsWithSynonyms) {
            for (auto& syn : result.getSynonyms())
                if (!synonyms.count(syn.first))
                    synonyms[syn.first] = synonyms.size();
        }

        // initialize synonym connections
        for (size_t i = 0; i < synonyms.size(); ++i) {
            id[i] = i;
        }

        // build synonym connections
        if (selSyns[0] != "BOOLEAN")
            for (auto& syn : selSyns) {
                ufUnion(synonyms[selSyns[0]], synonyms[syn]);
            }
        for (auto& result : resultsWithSynonyms) {
            vector<string> resultSynonyms;
            for (auto& syn : result.getSynonyms()) {
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
        for (auto it : id) {
            if (it.first == ufFind(it.first)) {
                synToGroup[it.first] = synToGroup.size();
                groups.push_back({});
            }
        }
        for (auto& result : resultsWithSynonyms) {
            string syn = result.getSynonyms().begin()->first;
            int groupIdx = synToGroup[ufFind(synonyms[syn])];
            groups[groupIdx].push_back(result);
        }

        return groups;
    }

    void sort(vector<Result>& results) {
    }
} // namespace Evaluator
