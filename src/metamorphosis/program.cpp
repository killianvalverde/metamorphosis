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

#include <algorithm>
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
    std::size_t wdth;
    std::size_t hght;
    std::size_t digs;

    try
    {
        for (auto& fle : std::filesystem::directory_iterator(prog_args_.trg_dir))
        {
            const auto& fle_pth = fle.path();

            if (!fle.is_regular_file() ||
                !std::regex_match(fle_pth.filename().c_str(), prog_args_.fltr_regx) ||
                fle_pth.filename().c_str()[0] == '.')
            {
                continue;
            }

            if (get_image_size(fle_pth, &wdth, &hght))
            {
                trg_fles_.push_back(new target_image(fle_pth, this, wdth, hght));
            }
            else
            {
                trg_fles_.push_back(new target_file(fle_pth, this));
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
    
    return !retv;
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
    std::string nme_buildr;
    std::size_t max_sz = std::max(prog_args_.bse_nms.size(), prog_args_.bse_nrs.size());

    for (auto& trg_fle : trg_fles_)
    {
        nme_buildr.clear();

        for (std::size_t idx = 0; idx < max_sz; ++idx)
        {
            if (idx < prog_args_.bse_nms.size())
            {
                nme_buildr += prog_args_.bse_nms[idx].get_name();
            }
            if (idx < prog_args_.bse_nrs.size())
            {
                nme_buildr += prog_args_.bse_nrs[idx].get_next_number();
            }
        }

        trg_fle->set_new_file_name(std::move(nme_buildr));
    }
}


bool program::rename_target_files()
{
    bool succs = true;
    std::string contnue;

    if (!prog_args_.skip_simu)
    {
        std::cout << spd::ios::set_light_green_text
                  << "Starting simulation... "
                  << spd::ios::newl;

        for (auto& trg_fle : trg_fles_)
        {
            trg_fle->rename(true);
        }

        std::cout << "Do you want to continue? [Y/n] " << std::flush;
        spd::ios::fpurge(stdin);
        std::getline(std::cin, contnue);

        if (contnue != "Y" && contnue != "y" && !contnue.empty())
        {
            return false;
        }

        for (auto& trg_fle : trg_fles_)
        {
            trg_fle->reset_rename();
        }
    }

    for (auto& trg_fle : trg_fles_)
    {
        if (!trg_fle->rename(false))
        {
            succs = false;
        }
    }

    return succs;
}


target_file* program::get_target_file_from_original_path(const std::filesystem::path& pth)
{
    for (auto& trg_fle : trg_fles_)
    {
        if (trg_fle->get_original_file_path() == pth)
        {
            return trg_fle;
        }
    }

    return nullptr;
}


target_file* program::get_target_file_from_actual_path(const std::filesystem::path& pth)
{
    for (auto& trg_fle : trg_fles_)
    {
        if (trg_fle->get_actual_file_path() == pth)
        {
            return trg_fle;
        }
    }

    return nullptr;
}


bool program::file_exists(const std::filesystem::path& path, bool simu)
{
    target_file* trg_fle;
    bool exsts = std::filesystem::exists(path);

    if (simu)
    {
        if (get_target_file_from_actual_path(path) != nullptr ||
            (exsts && get_target_file_from_original_path(path) == nullptr))
        {
            return true;
        }

        return false;
    }

    return exsts;
}


}
