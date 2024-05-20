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
 * @date        2018/07/21
 */

#ifndef METAMORPHOSIS_TARGET_FILE_HPP
#define METAMORPHOSIS_TARGET_FILE_HPP

#include <cstdio>
#include <filesystem>
#include <vector>


namespace metamorphosis {


class target_file
{
public:
    target_file(std::filesystem::path fle_pth, std::vector<target_file*>* fles_target);
    
    virtual ~target_file() = default;
    
    bool rename() noexcept;
    
    [[nodiscard]] inline const std::filesystem::path& get_file_path() const noexcept
    {
        return fle_pth_;
    }

    [[nodiscard]] inline const std::string& get_new_file_name() const noexcept
    {
        return new_fle_nme_;
    }
    
    inline void set_new_file_name(std::string new_fle_nme) noexcept
    {
        new_fle_nme_ = std::move(new_fle_nme);
    }

private:
    std::filesystem::path fle_pth_;
    
    std::string new_fle_nme_;

    std::vector<target_file*>* trg_fles_;
    
    std::size_t id_;

    bool dne_;

    bool visitd_;

    static std::size_t nxt_id_;
};


}


#endif
