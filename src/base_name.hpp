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
// Created by Killian on 20/07/18.
//

#ifndef METAMORPHOSIS_BASE_NAME_HPP
#define METAMORPHOSIS_BASE_NAME_HPP

#include <string>


namespace metamorphosis {


class base_name
{
public:
    base_name(std::string nme, size_t beg = 0, size_t peri = 0, size_t prio = 0) noexcept
            : nme_(std::move(nme))
            , beg_(beg)
            , peri_(peri)
            , prio_(prio)
    {
    }
    
    inline const std::string& get_name() const noexcept
    {
        return nme_;
    }
    
    inline size_t get_beginning() const noexcept
    {
        return beg_;
    }
    
    inline size_t get_period() const noexcept
    {
        return peri_;
    }
    
    inline size_t get_priority() const noexcept
    {
        return prio_;
    }

private:
    std::string nme_;
    
    std::size_t beg_;
    
    std::size_t peri_;
    
    std::size_t prio_;
};


}


#endif
