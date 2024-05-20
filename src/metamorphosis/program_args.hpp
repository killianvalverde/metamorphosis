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
 * @file        program.hpp
 * @brief       program class header.
 * @author      Killian Valverde
 * @date        2024/05/19
 */
 
#ifndef METAMORPHOSIS_PROGRAM_ARGS_HPP
#define METAMORPHOSIS_PROGRAM_ARGS_HPP

#include <regex>
#include <vector>

#include <speed/speed.hpp>

#include "base_name.hpp"
#include "base_number.hpp"
#include "sort_policies.hpp"


namespace metamorphosis {


/**
 * @brief       All the arguments that are forwarded to the program class.
 */
struct program_args
{
    spd::filesystem::rx_directory_path trg_dir;
    std::regex fltr_regx;
    std::vector<base_name> bse_nms;
    std::vector<base_number> bse_nrs;
    spd::contain::flags<sort_policies> srt_polics;
};


}


#endif
