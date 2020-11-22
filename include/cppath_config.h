//
// Created by wallel on 11/21/20.
//

#ifndef CPPATH_CPPATH_CONFIG_H
#define CPPATH_CPPATH_CONFIG_H

#include <vector>
#include <string>
#include <array>

namespace cppath
{
    namespace config
    {
        const int cut_class = 3;
        const std::array<std::string, cut_class> cut_definition = {R"(/)", R"(\)", R"(\\)"};
        const int MAX_PATHLEN = 255;
    }

}

#endif //CPPATH_CPPATH_CONFIG_H
