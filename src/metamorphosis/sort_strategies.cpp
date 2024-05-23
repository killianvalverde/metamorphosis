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
 * @file        metamorphosis/sort_strategies.cpp
 * @brief       sort_strategies implementation.
 * @author      Killian Valverde
 * @date        2024/05/19
 */

#include "sort_strategies.hpp"


namespace metamorphosis {


bool sort_alphabeticaly::operator()(target_file* rhs, target_file* lhs) const
{
    if (rhs->get_actual_file_path().empty())
    {
        return !lhs->get_actual_file_path().empty();
    }
    else if (lhs->get_actual_file_path().empty())
    {
        return false;
    }

    return rhs->get_actual_file_path().filename().string().compare(
            lhs->get_actual_file_path().filename().string()) < 0;
}


bool sort_by_image_with::operator()(target_file* rhs, target_file* lhs) const
{
    auto* img_rhs = dynamic_cast<target_image*>(rhs);
    auto* img_lhs = dynamic_cast<target_image*>(lhs);

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


bool sort_by_image_height::operator()(target_file* rhs, target_file* lhs) const
{
    auto* img_rhs = dynamic_cast<target_image*>(rhs);
    auto* img_lhs = dynamic_cast<target_image*>(lhs);

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


bool sort_by_image_size::operator()(target_file* rhs, target_file* lhs) const
{
    auto* img_rhs = dynamic_cast<target_image*>(rhs);
    auto* img_lhs = dynamic_cast<target_image*>(lhs);

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
