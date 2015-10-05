namespace std {
template <typename C>
auto rbegin(C const& c) -> decltype(c.rbegin()) {
    return c.rbegin();
}

template <typename C>
auto rend(C const& c) -> decltype(c.rend()) {
    return c.rend();
}

}

#include <range/v3/all.hpp>

#include <vector>
#include <cstddef>
#include <random>

#include <celero/Celero.h>

CELERO_MAIN

using namespace std;

constexpr size_t SET_SIZE = 1000000;

vector<int> createData() {
    std::random_device rd;
    std::default_random_engine e1(rd());
    std::uniform_int_distribution<int> uniform_dist(0, SET_SIZE);

    auto myRand = [&]() {
        return uniform_dist(e1);
    };

    vector<int> v = vector<int>(SET_SIZE);
    std::generate(std::begin(v), std::end(v), myRand);
    return v;
}

static vector<int> d1 = createData();
static vector<int> d2 = d1;
static auto d2beg = d2.begin(); static auto d2end = d2.end();
static vector<int> d3 = d1;

BASELINE(SortTest, Baseline_StdSortBeginEnd, 100, 10)
{
    std::sort(std::begin(d1), std::end(d1));
}

BENCHMARK(SortTest, StdSortIters, 100, 10)
{
    std::sort(d2beg, d2end);
}

BENCHMARK(SortTest, Ranges, 100, 10)
{
    ranges::sort(d3);
}
