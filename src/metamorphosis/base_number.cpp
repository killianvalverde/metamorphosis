/* metamorphosis
 * Copyright (C) 2018-2024 Killian Poulaud.
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
 * along with speed. If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * @file        metamorphosis/base_number.cpp
 * @brief       base_number implementation.
 * @author      Killian Valverde
 * @date        2018/07/30
 */

#include <sstream>
#include <iomanip>

#include "base_number.hpp"


namespace metamorphosis {


std::string base_number::get_next_number()
{
    std::stringstream sstr;
    
    sstr.fill('0');
    sstr << std::setw(digs_) << cur_nr_;
    cur_nr_ += inc_nr_;
    
    return sstr.str();
}


}
