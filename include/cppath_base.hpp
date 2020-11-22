//
// Created by wallel on 11/21/20.
//

#ifndef CPPATH_CPPATH_BASE_HPP
#define CPPATH_CPPATH_BASE_HPP

#ifdef CPPATH_DEBUG

#include <iostream>

#endif

#include <unistd.h>
#include <string>
#include <vector>
#include <array>
#include <algorithm>
#include <limits>

#include "cppath_config.h"
#include "cppath_vector.hpp"

namespace cppath
{
    bool workdir(std::string &s, int maxlen = config::MAX_PATHLEN);

    bool abspath(std::string &output, const std::string &input, int maxlen = config::MAX_PATHLEN);

    void basename(std::string &output, const std::string &input);

    void commonprefix(std::string &output, const std::vector<std::string> &list);

    void dirname(std::string &output, const std::string &input);

    bool exist(const std::string &input);

    bool getmtime(long &output, const std::string &input);

    bool getsize(int &output, const std::string &input);

    bool isabs(const std::string &input);

    bool isfile(const std::string &input);

    bool isdir(const std::string &input);

    bool islink(const std::string &input);

    bool ismount(const std::string &input);

    void join(std::string &output, std::vector<std::string> input);
}

bool cppath::workdir(std::string &s, int maxlen)
{
    char path[maxlen];
    bool flag = getcwd(path, sizeof(path));
    if (flag)
        s = std::string(path);
    return flag;
}

bool cppath::abspath(std::string &output, const std::string &input, int maxlen)
{
    char path[maxlen];
    auto flag = realpath(input.c_str(), path);
    if (flag == nullptr)
    {
        output = std::string(path);
        return true;
    }
    else return false;
}

void cppath::basename(std::string &output, const std::string &input)
{
    PathVector pv(input);
    output = pv.pvector[pv.pvector.size() - 1];
}

void cppath::commonprefix(std::string &output, const std::vector<std::string> &path_list)
{
    std::vector<PathVector> pv_list;
    output = "/";
    for (const auto &path : path_list)
    {
        pv_list.emplace_back(path);
    }
    for (int i = 0;; i++)
    {
        bool end_flag = false;
        std::string compare_key;
        for (const auto &pv : pv_list)
        {
            if (pv.pvector.size() <= i)
            {
                end_flag = true;
                break;
            }
            if (compare_key.empty())
            {
                compare_key = pv.pvector[i];
            }
            else if (compare_key != pv.pvector[i])
            {
                end_flag = true;
                break;
            }
        }
        if (end_flag)
            break;
        output += compare_key + '/';
    }
}

void cppath::dirname(std::string &output, const std::string &input)
{
    PathVector pv(input);
    output = pathvector2string(pv, pv.pvector.size() - 1);
}

bool cppath::exist(const std::string &input)
{
    int access_flag = access(input.c_str(), F_OK);
    if (access_flag == -1)
        return false;
    else return true;
}

bool cppath::isabs(const std::string &input)
{
    std::string abs_string;
    abspath(abs_string, input);
    PathVector origin_pv(input), abs_pv(abs_string);
    return origin_pv == abs_pv;
}

#endif //CPPATH_CPPATH_BASE_HPP
