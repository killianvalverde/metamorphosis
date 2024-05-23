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


target_file::target_file(std::filesystem::path fle_pth, program* prog)
        : orig_fle_pth_(fle_pth)
        , actual_fle_pth_(std::move(fle_pth))
        , new_fle_nme_()
        , prog_(prog)
        , id_(nxt_id_++)
{
}


bool target_file::rename(bool simu)
{
    std::filesystem::path new_fle_pth = actual_fle_pth_;
    target_file* trg_fle;

    new_fle_pth.replace_filename(new_fle_nme_);

    if (actual_fle_pth_ == new_fle_pth)
    {
        print_rename(new_fle_pth, true);
        return true;
    }

    if (prog_->file_exists(new_fle_pth, simu) &&
        ((trg_fle = prog_->get_target_file_from_actual_path(new_fle_pth)) == nullptr ||
         !trg_fle->rename_temporary(simu)) ||
        !raw_rename(actual_fle_pth_, new_fle_pth, simu))
    {
        print_rename(new_fle_pth, false);
        return false;
    }

    print_rename(new_fle_pth, true);
    actual_fle_pth_ = new_fle_pth;

    return true;
}


bool target_file::rename_temporary(bool simu)
{
    std::filesystem::path new_fle_pth = actual_fle_pth_;

    std::string new_fle_nme = "metamorphosis-tmp-file-base_name-";
    new_fle_nme += std::to_string(id_);
    new_fle_pth.replace_filename(new_fle_nme);

    if (prog_->file_exists(new_fle_pth, simu) ||
        !raw_rename(actual_fle_pth_, new_fle_pth, simu))
    {
        print_rename(new_fle_pth, false);
        return false;
    }

    print_rename(new_fle_pth, true);
    actual_fle_pth_ = new_fle_pth;

    return true;
}


bool target_file::simulate_rename()
{
    return false;
}


void target_file::set_new_file_name(std::string new_fle_nme)
{
    std::string extensn = orig_fle_pth_.extension();

    std::transform(extensn.begin(), extensn.end(), extensn.begin(), [](unsigned char c) {
        return std::tolower(c);
    });

    new_fle_nme_ = std::move(new_fle_nme);
    new_fle_nme_ += extensn;
}


void target_file::print_rename(const std::filesystem::path& new_path, bool succs) const
{
    std::cout << spd::ios::set_light_blue_text << "Renaming "
              << spd::ios::set_yellow_text << actual_fle_pth_.filename()
              << spd::ios::set_light_blue_text << " --> "
              << spd::ios::set_yellow_text << new_path.filename()
              << spd::ios::set_light_blue_text << " ...";

    if (succs)
    {
        std::cout << spd::ios::set_light_green_text << "[ok]" << spd::ios::newl;
    }
    else
    {
        std::cout << spd::ios::set_light_red_text << "[fail]" << spd::ios::newl;
    }
}


std::size_t target_file::nxt_id_ = 0;


}
