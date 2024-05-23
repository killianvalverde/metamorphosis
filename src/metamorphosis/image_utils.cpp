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

#include <cstdio>
#include <jpeglib.h>
#include <png.h>

#include <speed/speed.hpp>

#include "image_utils.hpp"


namespace metamorphosis {


const std::unordered_set<std::string> jpeg_exts_ = {".jpeg", ".jpg", ".JPEG", ".JPG"};


const std::unordered_set<std::string> png_exts_ = {".png", ".PNG"};


bool get_image_size(
        const std::filesystem::path& img_pth,
        std::size_t* wdth,
        std::size_t* hght
) noexcept
{
    bool succs = false;

    if (is_jpeg_extension(img_pth))
    {
        if (!(succs = get_jpeg_image_size(img_pth, wdth, hght)))
        {
            std::cout << spd::ios::set_light_red_text << "Error, " << img_pth.filename()
                      << " is not a jpeg image" << spd::ios::newl;
        }
    }
    else if (is_png_extension(img_pth))
    {
        if (!(succs = get_png_image_size(img_pth, wdth, hght)))
        {
            std::cout << spd::ios::set_light_red_text << "Error, " << img_pth.filename()
                      << " is not a png image" << spd::ios::newl;
        }
    }

    return succs;
}


struct jpeg_error
{
    struct jpeg_error_mgr pub;
    jmp_buf setjmp_buffer;
};


METHODDEF(void)
jpeg_error_exit (j_common_ptr cinfo)
{
    auto* myerr = (jpeg_error*)cinfo->err;
    longjmp(myerr->setjmp_buffer, 1);
}


bool get_jpeg_image_size(
        const std::filesystem::path& img_pth,
        std::size_t* wdth,
        std::size_t* hght
) noexcept
{
    jpeg_decompress_struct jpeg_inf {};
    jpeg_error jerr {};
    FILE* ifs;

    if ((ifs = fopen(img_pth.c_str(), "rb")) == nullptr)
    {
        return false;
    }

    jpeg_inf.err = jpeg_std_error(&jerr.pub);
    jerr.pub.error_exit = jpeg_error_exit;
    if (setjmp(jerr.setjmp_buffer))
    {
        jpeg_destroy_decompress(&jpeg_inf);
        fclose(ifs);
        return false;
    }

    jpeg_create_decompress(&jpeg_inf);
    jpeg_stdio_src(&jpeg_inf, ifs);
    jpeg_read_header(&jpeg_inf, TRUE);

    *wdth = jpeg_inf.image_width;
    *hght = jpeg_inf.image_height;

    return true;
}


bool get_png_image_size(
        const std::filesystem::path& img_pth,
        std::size_t* wdth,
        std::size_t* hght
) noexcept
{
    png_structp png_ptr;
    png_infop info_ptr;
    char header[8];
    FILE *ifs;

    if ((ifs = fopen(img_pth.c_str(), "rb")) == nullptr)
    {
        return false;
    }

    fread(header, 1, 8, ifs);
    if (png_sig_cmp((png_bytep)header, 0, 8))
    {
        return false;
    }
    if ((png_ptr = png_create_read_struct(
            PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr)) == nullptr)
    {
        return false;
    }
    if ((info_ptr = png_create_info_struct(png_ptr)) == nullptr)
    {
        return false;
    }
    if (setjmp(png_jmpbuf(png_ptr)))
    {
        return false;
    }

    png_init_io(png_ptr, ifs);
    png_set_sig_bytes(png_ptr, 8);
    png_read_info(png_ptr, info_ptr);

    *wdth = png_get_image_width(png_ptr, info_ptr);
    *hght = png_get_image_height(png_ptr, info_ptr);

    return true;
}


[[nodiscard]] bool is_jpeg_extension(const std::filesystem::path& img_pth) noexcept
{
    return jpeg_exts_.count(img_pth.extension()) > 0;
}


[[nodiscard]] bool is_png_extension(const std::filesystem::path& img_pth) noexcept
{
    return png_exts_.count(img_pth.extension()) > 0;
}


}
