#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include <boost/utility/string_ref.hpp>

#include <celero/Celero.h>

CELERO_MAIN

using namespace std;

vector<string> split(string const& s, char const delim) {
    vector<string> results {};

    string::size_type previousPosition = 0;
    string::size_type currentPosition = s.find(delim);

    auto more = [&]() { return currentPosition != string::npos; };
    auto addResult = [&](auto start, auto stop) { results.push_back(s.substr(start, stop)); };

    while (more()) {
        addResult(previousPosition, currentPosition - previousPosition);
        previousPosition = ++currentPosition;
        currentPosition = s.find(delim, currentPosition);

        if (!more()) {
            addResult(previousPosition, s.length());
        }
    }
    return results;
}

vector<boost::string_ref> split_ref(string const& s, char const delim) {
    vector<boost::string_ref> results {};
    boost::string_ref sr(s);

    while (sr.length()) {
        auto pos = sr.find(delim);

        if (pos == boost::string_ref::npos) {
            results.push_back(sr);
            break;
        }

        auto substr = sr;
        substr.remove_suffix(sr.length() - pos);
        sr.remove_prefix(pos + 1);

        results.push_back(substr);
    }

    return results;
}

vector<string> split_getline(string const& s, char const delim) {
    std::vector<string> results {};
    std::istringstream split(s);
   for (std::string each; std::getline(split, each, delim); results.push_back(each));
    return results;
}

#include "string_ref_data.hpp"

BASELINE(SplitTest, Baseline, 10, 5)
{
    split_getline(data, ' ');
}

BENCHMARK(SplitTest, StringIters, 100, 10)
{
    split(data, ' ');
}

BENCHMARK(SplitTest, StringRef, 100, 50)
{
    split_ref(data, ' ');
}
