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

#include <speed/speed.hpp>
#include <speed/speed_alias.hpp>

#include "file_target.hpp"


namespace metamorphosis {


file_target::file_target(std::filesystem::path fle_pth, std::vector<file_target*>* fles_target)
        : fle_pth_(std::move(fle_pth))
        , new_fle_nme_()
        , dne_(false)
        , visitd_(false)
        , id_(nxt_id_++)
        , fles_target_(fles_target)
{
}


int file_target::rename() noexcept
{
    std::filesystem::path new_fle_pth = fle_pth_;
    int res;
    
    if (dne_)
    {
        return 0;
    }
    else if (visitd_)
    {
        std::string new_fle_nme = "metamorphosis-tmp-file-name-";
        new_fle_nme += std::to_string(id_);
        new_fle_pth.replace_filename(new_fle_nme);
    }
    else
    {
        new_fle_pth.replace_filename(new_fle_nme_);
        new_fle_pth += fle_pth_.extension();
    
        visitd_ = true;
    
        if (fle_pth_ !=  new_fle_pth &&
            std::filesystem::exists(new_fle_pth))
        {
            for (auto& x : *fles_target_)
            {
                if (x->fle_pth_ == new_fle_pth)
                {
                    if (x->rename() != 0)
                    {
                        dne_ = true;
                        return -1;
                    }
                    
                    break;
                }
            }
        }
        
        dne_ = true;
    }
    
    std::cout << spd::ios::set_light_blue_text << "Renaming "
              << spd::ios::set_yellow_text << fle_pth_.filename()
              << spd::ios::set_light_blue_text << " --> "
              << spd::ios::set_yellow_text << new_fle_pth.filename()
              << spd::ios::set_light_blue_text << " ...";
              
    if ((res = ::rename(fle_pth_.c_str(), new_fle_pth.c_str())) == 0)
    {
        fle_pth_ = new_fle_pth;
        
        std::cout << spd::ios::set_light_green_text << "[ok]" << spd::ios::newl;
    }
    else
    {
        std::cout << spd::ios::set_light_red_text << "[fail]" << spd::ios::newl;
    }
    
    return res;
}


bool sort_alphabeticaly::operator()(file_target* rhs, file_target* lhs) const
{
    if (rhs->get_file_path().empty())
    {
        return !lhs->get_file_path().empty();
    }
    else if (lhs->get_file_path().empty())
    {
        return false;
    }
    
    return rhs->get_file_path().filename().string().compare(
            lhs->get_file_path().filename().string()) < 0;
}


std::size_t file_target::nxt_id_ = 0;


}
