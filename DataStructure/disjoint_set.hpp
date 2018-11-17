/*
    Programed by HarryShaunWang
    Created on 2018.11.1
    Last modified on 2018.11.12
*/
#ifndef DISJOINT_SET_HPP
#define DISJOINT_SET_HPP

#include <iostream>
#include <vector>

class DisjointSet
{
public:
    DisjointSet() = default;
    DisjointSet (int size);
    ~DisjointSet() = default;
    int getSize();
    void resize (int size);
    bool areDisjoint (int x, int y);
    void unite (int x, int y);

private:
    int size_;
    std::vector<int> Father_, Rank_;

    int find (int x);
    int doFind (int x);
};

DisjointSet::DisjointSet (int size) : size_ (size), Father_ (size + 1), Rank_ (size + 1, 1)
{
    for (int i = 1; i <= size; ++i)
        Father_[i] = i;
}

int DisjointSet::getSize()
{
    return size_;
}

void DisjointSet::resize (int size)
{
    if (size > size_)
    {
        Father_.resize (size + 1);
        Rank_.resize (size + 1);
        for (int i = size_ + 1; i <= size; ++i)
            Father_[i] = i, Rank_[i] = 1;
    }
    size_ = size;
}

int DisjointSet::find (int x)
{
    if (x > size_)
        resize (x);
    return doFind (x);
}

bool DisjointSet::areDisjoint (int x, int y)
{
    return find (x) == find (y);
}

void DisjointSet::unite (int x, int y)
{
    int fx = find (x), fy = find (y);
    if (fx != fy)
    {
        if (Rank_[fx] < Rank_[fy])
            std::swap (fx, fy);
        Rank_[fx] += Rank_[fy];
        Father_[fy] = fx;
    }
    else
    {
        std::cerr << "ERROR:" << x << " and " << y << " are in the SAME set!" << std::endl;
    }
}

int DisjointSet::doFind (int x)
{
    return x == Father_[x] ? x : Father_[x] = doFind (Father_[x]);
}

#endif
