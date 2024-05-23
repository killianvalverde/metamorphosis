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
 * @file        metamorphosis/base_number.hpp
 * @brief       base_number header.
 * @author      Killian Valverde
 * @date        2018/07/21
 */

#ifndef METAMORPHOSIS_BASE_NUMBER_HPP
#define METAMORPHOSIS_BASE_NUMBER_HPP

#include <string>


namespace metamorphosis {


class base_number
{
public:
    explicit base_number() noexcept
            : nr_(1)
            , cur_nr_(1)
            , digs_(0)
            , inc_nr_(1)
            , prio_(0)
    {
    }

    [[nodiscard]] std::string get_next_number();

    inline void set_digits(std::size_t digs) noexcept
    {
        if (digs_ == 0)
        {
            digs_ = digs;
        }
    }

    inline void set_number(std::size_t nr) noexcept
    {
        nr_ = nr;
        cur_nr_ = nr;
    }

private:
    std::size_t nr_;
    
    std::size_t cur_nr_;

    std::size_t digs_;
    
    std::size_t inc_nr_;
    
    std::size_t prio_;
};


}


#endif
