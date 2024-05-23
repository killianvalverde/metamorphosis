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

#include "forward_declarations.hpp"
#include "program.hpp"


namespace metamorphosis {


class target_file
{
public:
    target_file(std::filesystem::path fle_pth, program* prog);

    virtual ~target_file() = default;

    bool rename(bool simu);

    bool rename_temporary(bool simu);

    inline static bool raw_rename(
            const std::filesystem::path& src,
            const std::filesystem::path& trg,
            bool simu
    )
    {
        return simu || (::rename(src.c_str(), trg.c_str()) == 0);
    }

    inline void reset_rename()
    {
        actual_fle_pth_ = orig_fle_pth_;
    }

    bool simulate_rename();

    [[nodiscard]] inline const std::filesystem::path& get_original_file_path() const noexcept
    {
        return orig_fle_pth_;
    }
    
    [[nodiscard]] inline const std::filesystem::path& get_actual_file_path() const noexcept
    {
        return actual_fle_pth_;
    }
    
    void set_new_file_name(std::string new_fle_nme);

    [[nodiscard]] inline bool original_and_actual_file_path_equal() const noexcept
    {
        return orig_fle_pth_ == actual_fle_pth_;
    }

    void print_rename(const std::filesystem::path& new_path, bool succs) const;

private:
    std::filesystem::path orig_fle_pth_;

    std::filesystem::path actual_fle_pth_;
    
    std::string new_fle_nme_;

    program* prog_;
    
    std::size_t id_;

    static std::size_t nxt_id_;
};


}


#endif
