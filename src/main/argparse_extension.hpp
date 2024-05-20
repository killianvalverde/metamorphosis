/* metamorphosis
 * Copyright (C) 2018-2024 Killian Valverde.
 *
 * This file is part of metamorphosis.
 *
 * metamorphosis is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * metamorphosis is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with metamorphosis. If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * @file        main/argparse_extension.hpp
 * @brief       argparse extension.
 * @author      Killian Valverde
 * @date        2024/05/19
 */

#include <filesystem>
#include <regex>
#include <string>
#include <unordered_set>

#include <speed/speed.hpp>

#include "../metamorphosis/base_name.hpp"
#include "../metamorphosis/base_number.hpp"


std::unordered_set<char> forbidden_file_name_ascii_chars = {
        '<', '>', ':', '"', '/', '\\', '|', '?', '*'
};


namespace speed::type_casting {


template<>
inline bool try_type_cast(
    const std::string& arg,
    metamorphosis::base_name* res,
    std::error_code* err_code
) noexcept
{
    for (auto& ch : arg)
    {
        if (::forbidden_file_name_ascii_chars.count(ch) > 0)
        {
            assign_type_casting_error_code(
                    static_cast<int>(error_codes::OTHER),
                    err_code);

            return false;
        }
    }

    res->set_name(arg);

    return true;
}


template<>
inline bool try_type_cast(
    const std::string& arg,
    metamorphosis::base_number* res,
    std::error_code* err_code
) noexcept
{
    std::size_t nr;

    if (!speed::type_casting::try_type_cast(arg, &nr, err_code))
    {
        return false;
    }

    res->set_number(nr);

    return true;
}


template<>
inline bool try_type_cast(
    const std::string& arg,
    spd::contain::flags<metamorphosis::sort_policies>* res,
    std::error_code* err_code
) noexcept
{
    if (arg == "ALPHABETICALLY")
    {
        res->set(metamorphosis::sort_policies::ALPHABETICALLY);
    }
    else if (arg == "IMAGE_WITH")
    {
        res->set(metamorphosis::sort_policies::IMAGE_WITH);
    }
    else if (arg == "IMAGE_HEIGTH")
    {
        res->set(metamorphosis::sort_policies::IMAGE_HEIGTH);
    }
    else if (arg == "IMAGE_SIZE")
    {
        res->set(metamorphosis::sort_policies::IMAGE_SIZE);
    }
    else
    {
        assign_type_casting_error_code(
                static_cast<int>(error_codes::OTHER),
                err_code);

        return false;
    }

    return true;
}


}

