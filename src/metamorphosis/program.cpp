/* metamorphosis
 * Copyright (C) 2018-2024 Killian Valverde.
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

/**
 * @file        program.cpp
 * @brief       program class implementation.
 * @author      Killian Valverde
 * @date        2024/05/19
 */

#include <cstdio>
#include <cstdlib>
#include <iostream>

#include "image_utils.hpp"
#include "program.hpp"
#include "sort_strategies.hpp"
#include "target_file.hpp"
#include "target_image.hpp"


namespace metamorphosis {


program::program(program_args prog_args) 
        : prog_args_(std::move(prog_args))
{
    target_file* fle_trg;
    std::size_t wdth;
    std::size_t hght;
    std::size_t digs;

    try
    {
        for (auto& fle : std::filesystem::directory_iterator(prog_args_.trg_dir))
        {
            if (fle.is_regular_file())
            {
                std::filesystem::path fle_pth = fle.path();

                if (!std::regex_match(fle_pth.filename().c_str(), prog_args_.fltr_regx))
                {
                    continue;
                }

                if (fle_pth.filename().c_str()[0] != '.')
                {
                    if ((is_jpeg_extension(fle_pth) || is_png_extension(fle_pth)) &&
                        get_image_size(fle_pth, &wdth, &hght))
                    {
                        fle_trg = new target_image(std::move(fle_pth), &trg_fles_, wdth, hght);
                    }
                    else
                    {
                        fle_trg = new target_file(std::move(fle_pth), &trg_fles_);
                    }

                    trg_fles_.push_back(fle_trg);
                }
            }
        }
    }
    catch (const std::filesystem::filesystem_error& fe)
    {
        std::cerr << spd::ios::set_light_red_text
                  << "Error executing in directory: " << prog_args_.trg_dir
                  << spd::ios::newl;

        exit(-1);
    }

    if (prog_args_.bse_nrs.empty())
    {
        prog_args_.bse_nrs.emplace_back();
    }

    digs = spd::scals::get_n_digits(trg_fles_.size());

    for (auto& bse_nr : prog_args_.bse_nrs)
    {
        bse_nr.set_digits(digs);
    }
}


program::~program()
{
    for (auto& x : trg_fles_)
    {
        delete x;
    }
}


int program::execute()
{
    int retv;

    sort_sources();
    set_new_file_names();
    retv = rename_target_files();

    std::cout << spd::ios::set_default_text;
    
    return retv;
}


void program::sort_sources()
{
    if (prog_args_.srt_polics.is_set(sort_policies::ALPHABETICALLY))
    {
        spd::algo::quicksort(trg_fles_, trg_fles_.size(), sort_alphabeticaly());
    }
    if (prog_args_.srt_polics.is_set(sort_policies::IMAGE_WITH))
    {
        spd::algo::quicksort(trg_fles_, trg_fles_.size(), sort_by_image_with());
    }
    if (prog_args_.srt_polics.is_set(sort_policies::IMAGE_HEIGTH))
    {
        spd::algo::quicksort(trg_fles_, trg_fles_.size(), sort_by_image_height());
    }
    if (prog_args_.srt_polics.is_set(sort_policies::IMAGE_SIZE))
    {
        spd::algo::quicksort(trg_fles_, trg_fles_.size(), sort_by_image_size());
    }
}


void program::set_new_file_names()
{
    std::size_t cur_bse_nme_idx;
    std::size_t cur_bse_nr_idx;
    std::string nme_buildr;
    bool fnd;

    for (auto& trg_fle : trg_fles_)
    {
        cur_bse_nme_idx = 0;
        cur_bse_nr_idx = 0;
        nme_buildr.clear();

        do
        {
            fnd = false;

            if (prog_args_.bse_nms.size() > cur_bse_nme_idx)
            {
                nme_buildr += prog_args_.bse_nms[cur_bse_nme_idx].get_name();
                ++cur_bse_nme_idx;
                fnd = true;
            }
            if (prog_args_.bse_nrs.size() > cur_bse_nr_idx)
            {
                nme_buildr += prog_args_.bse_nrs[cur_bse_nr_idx].get_next_number();
                ++cur_bse_nr_idx;
                fnd = true;
            }

        } while (fnd);

        trg_fle->set_new_file_name(nme_buildr);
    }
}


bool program::rename_target_files()
{
    bool succs = true;

    for (auto& trg_fle : trg_fles_)
    {
        if (!trg_fle->rename())
        {
            succs = false;
        }
    }

    return succs;
}


}
