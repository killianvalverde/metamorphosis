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
 * @date        2018/08/06
 */

#include <speed/speed.hpp>

#include "target_file.hpp"


namespace metamorphosis {


target_file::target_file(std::filesystem::path fle_pth, std::vector<target_file*>* fles_target)
        : fle_pth_(std::move(fle_pth))
        , new_fle_nme_()
        , trg_fles_(fles_target)
        , id_(nxt_id_++)
        , dne_(false)
        , visitd_(false)
{
}


bool target_file::rename() noexcept
{
    std::filesystem::path new_fle_pth = fle_pth_;
    int res;
    
    if (dne_)
    {
        return true;
    }
    else if (visitd_)
    {
        std::string new_fle_nme = "metamorphosis-tmp-file-base_name-";
        new_fle_nme += std::to_string(id_);
        new_fle_pth.replace_filename(new_fle_nme);
    }
    else
    {
        new_fle_pth.replace_filename(new_fle_nme_);
        new_fle_pth += fle_pth_.extension();
    
        visitd_ = true;
    
        if (fle_pth_ != new_fle_pth &&
            std::filesystem::exists(new_fle_pth))
        {
            for (auto& trg_fle : *trg_fles_)
            {
                if (trg_fle->fle_pth_ == new_fle_pth)
                {
                    if (trg_fle->rename() != 0)
                    {
                        dne_ = true;
                        return false;
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
    
    return res == 0;
}


std::size_t target_file::nxt_id_ = 0;


}
