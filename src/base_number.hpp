/* metamorphosis
 * Copyright (C) 2018-2023 Killian Valverde.
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

//
// Created by Killian on 21/07/18.
//

#ifndef METAMORPHOSIS_BASE_NUMBER_HPP
#define METAMORPHOSIS_BASE_NUMBER_HPP

#include <cstdlib>
#include <string>


namespace metamorphosis {


class base_number
{
public:
    base_number(
            std::size_t nr,
            std::size_t digs = 0,
            std::size_t inc_nr = 0,
            std::size_t beg = 0,
            std::size_t peri = 0,
            std::size_t prio = 0
    ) noexcept
            : nr_(nr)
            , cur_nr_(nr)
            , digs_(digs)
            , inc_nr_(inc_nr)
            , beg_(beg)
            , peri_(peri)
            , prio_(prio)
    {
        if (inc_nr_ == 0)
        {
            inc_nr_ = 1;
        }
    }
    
    std::string get_next_number();
    
    inline void update_digits(std::size_t digs) noexcept
    {
        if (digs_ == 0)
        {
            digs_ = digs;
        }
    }

private:
    std::size_t nr_;
    
    std::size_t cur_nr_;

    std::size_t digs_;
    
    std::size_t inc_nr_;
    
    std::size_t beg_;
    
    std::size_t peri_;
    
    std::size_t prio_;
};


}


#endif
