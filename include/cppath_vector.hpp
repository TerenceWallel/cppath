//
// Created by wallel on 11/22/20.
//

#ifndef CPPATH_CPPATH_VECTOR_HPP
#define CPPATH_CPPATH_VECTOR_HPP

#include <string>
#include <utility>
#include <vector>
#include <algorithm>
#include <cmath>

#include "cppath_config.h"

namespace cppath
{
    struct PathVector
    {
        explicit PathVector(std::string paths);

        std::string origin_path;
        std::vector<int> cut_position;

        std::vector<std::string> pvector;

        bool operator==(const PathVector &b);
    };

    std::string pathvector2string(PathVector pv, unsigned long n);
}

cppath::PathVector::PathVector(std::string paths)
{
    origin_path = std::move(paths);
    for (const auto &cut : config::cut_definition)
    {
        for (int position = origin_path.find(cut, 0);
             position != std::string::npos;
             position = origin_path.find(cut, position + 1))
        {
            cut_position.push_back(position);
        }
    }
    std::sort(cut_position.begin(), cut_position.end());
    for (int i = 0; i < cut_position.size(); i++)
    {
        if (cut_position[i] == 0)
            continue;
        if (i == 0)
        {
            pvector.push_back(origin_path.substr(1, cut_position[i] - 1));
        }
        else
        {
            pvector.push_back(origin_path.substr(cut_position[i - 1] + 1, cut_position[i] - cut_position[i - 1] - 1));
        }
    }
    if (cut_position[cut_position.size() - 1] != origin_path.length() - 1)
    {
        pvector.push_back(
                origin_path.substr(cut_position[cut_position.size() - 1] + 1,
                                   origin_path.length() - cut_position[cut_position.size() - 1] - 1));
    }
}

bool cppath::PathVector::operator==(const cppath::PathVector &b)
{
    if (pvector.size() != b.pvector.size())
        return false;
    for (int i = 0; i < pvector.size(); i++)
    {
        if (pvector[i] != b.pvector[i])
            return false;
    }
    return true;
}

std::string cppath::pathvector2string(PathVector pv, unsigned long n)
{
    std::string output = "/";
    for (int i = 0; i < std::min(pv.pvector.size(), n); i++)
    {
        output += pv.pvector[i] + "/";
    }
    return output;
}

#endif //CPPATH_CPPATH_VECTOR_HPP
