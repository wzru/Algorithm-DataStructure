/*
    Programed by HarryShaunWang
    Created on 2018.11.12
    Last modified on 2018.11.12
*/
#ifndef QUICK_SORT_HPP
#define QUICK_SORT_HPP

#include <algorithm>

template <typename It>
inline void quickSort (It l, It r)
{
    It i = l, j = r, mid = l + ( (r - l) >> 1);
    while (i <= j)
    {
        while (*i < *mid)
            ++i;
        while (*mid < *j)
            --j;
        if (i <= j)
        {
            std::swap (*i, *j);
            ++i, --j;
        }
        if (l < j)
            quickSort (l, j);
        if (i < r)
            quickSort (i, r);
    }
}

#endif