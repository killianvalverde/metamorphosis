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

#ifndef METAMORPHOSIS_IMAGE_TARGET_HPP
#define METAMORPHOSIS_IMAGE_TARGET_HPP

#include <utility>

#include "file_target.hpp"


namespace metamorphosis {


class image_target : public file_target
{
public:
    image_target(
            std::filesystem::path fle_pth,
            std::vector<file_target*>* fles_target,
            size_t wth,
            size_t hght
    );
    
    inline std::size_t get_with() const noexcept
    {
        return wth_;
    }
    
    inline std::size_t get_height() const noexcept
    {
        return hght_;
    }
    
    inline std::size_t get_size() const noexcept
    {
        return wth_ + hght_;
    }

private:
    std::size_t wth_;

    std::size_t hght_;
};


struct sort_by_image_with
{
    bool operator()(file_target* rhs, file_target* lhs) const;
};


struct sort_by_image_height
{
    bool operator()(file_target* rhs, file_target* lhs) const;
};


struct sort_by_image_size
{
    bool operator()(file_target* rhs, file_target* lhs) const;
};


}


#endif
