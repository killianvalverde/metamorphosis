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
// Created by Killian on 06/08/18.
//

#include "image_target.hpp"


namespace metamorphosis {


image_target::image_target(
        std::filesystem::path fle_pth,
        std::vector<file_target*>* fles_target,
        size_t wth,
        size_t hght
)
        : file_target(std::move(fle_pth), fles_target)
        , wth_(wth)
        , hght_(hght)
{
}


bool sort_by_image_with::operator()(file_target* rhs, file_target* lhs) const
{
    image_target* img_rhs = dynamic_cast<image_target*>(rhs);
    image_target* img_lhs = dynamic_cast<image_target*>(lhs);
    
    if (img_rhs == nullptr)
    {
        return img_lhs != nullptr;
    }
    else if (img_lhs == nullptr)
    {
        return true;
    }
    
    return img_rhs->get_with() > img_lhs->get_with() ||
           img_rhs->get_with() == img_lhs->get_with();
}


bool sort_by_image_height::operator()(file_target* rhs, file_target* lhs) const
{
    image_target* img_rhs = dynamic_cast<image_target*>(rhs);
    image_target* img_lhs = dynamic_cast<image_target*>(lhs);
    
    if (img_rhs == nullptr)
    {
        return img_lhs != nullptr;
    }
    else if (img_lhs == nullptr)
    {
        return true;
    }
    
    return img_rhs->get_height() > img_lhs->get_height() ||
           img_rhs->get_height() == img_lhs->get_height();
}


bool sort_by_image_size::operator()(file_target* rhs, file_target* lhs) const
{
    image_target* img_rhs = dynamic_cast<image_target*>(rhs);
    image_target* img_lhs = dynamic_cast<image_target*>(lhs);
    
    if (img_rhs == nullptr)
    {
        return img_lhs == nullptr;
    }
    else if (img_lhs == nullptr)
    {
        return true;
    }
    
    return img_rhs->get_size() > img_lhs->get_size() ||
           img_rhs->get_size() == img_lhs->get_size();
}


}
