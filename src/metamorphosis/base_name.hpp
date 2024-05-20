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
 * @file        metamorphosis/base_name.hpp
 * @brief       base_name header.
 * @author      Killian Valverde
 * @date        2018/07/20
 */

#ifndef METAMORPHOSIS_BASE_NAME_HPP
#define METAMORPHOSIS_BASE_NAME_HPP

#include <string>


namespace metamorphosis {


class base_name
{
public:
    explicit base_name() noexcept
            : nme_()
            , beg_(0)
            , peri_(0)
            , prio_(0)
    {
    }

    [[nodiscard]] inline size_t get_beginning() const noexcept
    {
        return beg_;
    }
    
    [[nodiscard]] inline const std::string& get_name() const noexcept
    {
        return nme_;
    }
    
    [[nodiscard]] inline size_t get_period() const noexcept
    {
        return peri_;
    }
    
    [[nodiscard]] inline size_t get_priority() const noexcept
    {
        return prio_;
    }

    inline void set_beginning(size_t beg) noexcept
    {
        beg_ = beg;
    }

    inline void set_name(std::string nme) noexcept
    {
        nme_ = std::move(nme);
    }

    inline void set_period(size_t peri) noexcept
    {
        peri_ = peri;
    }

    inline void set_priority(size_t prio) noexcept
    {
        prio_ = prio;
    }

private:
    std::string nme_;

    std::size_t beg_;
    
    std::size_t peri_;
    
    std::size_t prio_;
};


}


#endif
