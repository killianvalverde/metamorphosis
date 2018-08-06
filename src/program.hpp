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

#ifndef METAMORPHOSIS_PROGRAM_HPP
#define METAMORPHOSIS_PROGRAM_HPP

#include <filesystem>
#include <regex>
#include <string>
#include <unordered_set>
#include <vector>

#include "base_name.hpp"
#include "base_number.hpp"
#include "file_target.hpp"
#include "image_target.hpp"
#include "sort_policie.hpp"


namespace metamorphosis {


class program
{
public:
    program(
            std::filesystem::path src_dir,
            std::vector<base_name> bse_nmes,
            std::vector<base_number> bse_nrs,
            std::vector<sort_policie> sort_policies,
            std::regex regx
    );
    
    ~program();
    
    int execute();

private:
    void set_new_file_names();
    
    void sort_sources();
    
    bool rename_files_target();
    
    bool get_image_size(
            const std::filesystem::path& img_pth,
            std::size_t* wdth,
            std::size_t* hght
    ) const noexcept;
    
    bool get_jpeg_image_size(
            const std::filesystem::path& img_pth,
            std::size_t* wdth,
            std::size_t* hght
    ) const noexcept;
    
    bool get_png_image_size(
            const std::filesystem::path& img_pth,
            std::size_t* wdth,
            std::size_t* hght
    ) const noexcept;
    
    bool is_jpeg_extension(const std::filesystem::path& img_pth) const noexcept;
    
    bool is_png_extension(const std::filesystem::path& img_pth) const noexcept;

private:
    std::filesystem::path src_dir_;
    
    std::vector<file_target*> fles_target_;
    
    std::vector<base_name> bse_nmes_;
    
    std::vector<base_number> bse_nrs_;
    
    std::regex regx_;
    
    std::vector<sort_policie> sort_policies_;
    
    static const std::unordered_set<std::string> jpeg_exts_;
    
    static const std::unordered_set<std::string> png_exts_;
};


}


#endif
