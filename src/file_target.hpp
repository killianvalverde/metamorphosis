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

#ifndef METAMORPHOSIS_FILE_TARGET_HPP
#define METAMORPHOSIS_FILE_TARGET_HPP

#include <cstdio>
#include <filesystem>
#include <vector>


namespace metamorphosis {


class file_target
{
public:
    file_target(std::filesystem::path fle_pth, std::vector<file_target*>* fles_target);
    
    virtual ~file_target() = default;
    
    int rename() noexcept;
    
    inline const std::filesystem::path& get_file_path() const noexcept
    {
        return fle_pth_;
    }
    
    inline void set_new_file_name(std::string new_fle_nme)
    {
        new_fle_nme_ = std::move(new_fle_nme);
    }
    
    inline const std::string& get_new_file_name() const noexcept
    {
        return new_fle_nme_;
    }

private:
    std::filesystem::path fle_pth_;
    
    std::string new_fle_nme_;
    
    bool dne_;
    
    bool visitd_;
    
    std::size_t id_;
    
    std::vector<file_target*>* fles_target_;
    
    static std::size_t nxt_id_;
};


struct sort_alphabeticaly
{
    bool operator()(file_target* rhs, file_target* lhs) const;
};


}


#endif
