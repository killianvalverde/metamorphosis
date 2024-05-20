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
 * @file        metamorphosis/image_utils.hpp
 * @brief       image_utils header.
 * @author      Killian Valverde
 * @date        2024/05/20
 */

#ifndef METAMORPHOSIS_IMAGE_UTILS_HPP
#define METAMORPHOSIS_IMAGE_UTILS_HPP

#include <filesystem>
#include <unordered_set>


namespace metamorphosis {


bool get_image_size(
        const std::filesystem::path& img_pth,
        std::size_t* wdth,
        std::size_t* hght
) noexcept;


bool get_jpeg_image_size(
        const std::filesystem::path& img_pth,
        std::size_t* wdth,
        std::size_t* hght
) noexcept;


bool get_png_image_size(
        const std::filesystem::path& img_pth,
        std::size_t* wdth,
        std::size_t* hght
) noexcept;


[[nodiscard]] bool is_jpeg_extension(const std::filesystem::path& img_pth) noexcept;


[[nodiscard]] bool is_png_extension(const std::filesystem::path& img_pth) noexcept;


}


#endif
