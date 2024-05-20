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
 * @file        metamorphosis/sort_policies.hpp
 * @brief       sort_policies header.
 * @author      Killian Valverde
 * @date        2018/07/30
 */

#ifndef METAMORPHOSIS_SORT_POLICIES_HPP
#define METAMORPHOSIS_SORT_POLICIES_HPP


namespace metamorphosis {


enum class sort_policies : std::uint8_t
{
    ALPHABETICALLY = 0x1,
    IMAGE_WITH = 0x2,
    IMAGE_HEIGTH = 0x4,
    IMAGE_SIZE = 0x8,
};


}


#endif
