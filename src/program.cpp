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

#include <cstdio>
#include <cstdlib>
#include <iostream>

#include <speed/speed.hpp>
#include <speed/speed_alias.hpp>

#include <jpeglib.h>
#include <png.h>

#include "program.hpp"


namespace metamorphosis {


program::program(
        std::filesystem::path src_dir,
        std::vector<base_name> bse_nmes,
        std::vector<base_number> bse_nrs,
        std::vector<sort_policie> sort_policies,
        std::regex regx
)
        : src_dir_(std::move(src_dir))
        , bse_nmes_(std::move(bse_nmes))
        , bse_nrs_(std::move(bse_nrs))
        , fles_target_()
        , sort_policies_(std::move(sort_policies))
        , regx_(std::move(regx))
{
    file_target* fle_trg;
    std::size_t wdth;
    std::size_t hght;
    std::size_t digs;
    
    try
    {
        for (auto& x : std::filesystem::directory_iterator(src_dir_))
        {
            if (x.is_regular_file())
            {
                std::filesystem::path fle_pth = x.path();
    
                if (!std::regex_match(fle_pth.filename().c_str(), regx_))
                {
                    continue;
                }
                
                if (fle_pth.filename().c_str()[0] != '.')
                {
                    if ((is_jpeg_extension(fle_pth) || is_png_extension(fle_pth)) &&
                        get_image_size(fle_pth, &wdth, &hght))
                    {
                        fle_trg = new image_target(std::move(fle_pth), &fles_target_, wdth, hght);
                    }
                    else
                    {
                        fle_trg = new file_target(std::move(fle_pth), &fles_target_);
                    }
                    
                    fles_target_.push_back(fle_trg);
                }
            }
        }
    }
    catch (const std::filesystem::filesystem_error& fe)
    {
        std::cerr << spd::ios::set_light_red_text
                  << "Error executing in directory: " << src_dir_
                  << spd::ios::newl;
        
        exit(-1);
    }
    
    if (bse_nrs.empty())
    {
        bse_nrs.emplace_back(1);
    }
    
    digs = spd::scals::get_n_digits(fles_target_.size());
    
    for (auto& x : bse_nrs_)
    {
        x.update_digits(digs);
    }
}


program::~program()
{
    for (auto& x : fles_target_)
    {
        delete x;
    }
}


int program::execute()
{
    int succ;
    
    sort_sources();
    set_new_file_names();
    
    succ = rename_files_target() ? 0 : -1;
    
    std::cout << spd::ios::set_default_text;
    
    return succ;
}


void program::set_new_file_names()
{
    std::size_t cur_bse_nme_idx;
    std::size_t cur_bse_nr_idx;
    std::string nme_buildr;
    bool done;
    
    for (auto& x : fles_target_)
    {
        cur_bse_nme_idx = 0;
        cur_bse_nr_idx = 0;
        nme_buildr.clear();
        
        do
        {
            done = false;
            
            if (bse_nmes_.size() > cur_bse_nme_idx)
            {
                nme_buildr += bse_nmes_[cur_bse_nme_idx].get_name();
                ++cur_bse_nme_idx;
                done = true;
            }
            if (bse_nrs_.size() > cur_bse_nr_idx)
            {
                nme_buildr += bse_nrs_[cur_bse_nr_idx].get_next_number();
                ++cur_bse_nr_idx;
                done = true;
            }
            
        } while (done);
        
        x->set_new_file_name(nme_buildr);
    }
}


void program::sort_sources()
{
    for (auto& x : sort_policies_)
    {
        switch (x)
        {
            case sort_policie::ALPHABETICALLY:
                spd::algo::quicksort(fles_target_, fles_target_.size(), sort_alphabeticaly());
                break;
            
            case sort_policie::IMAGE_WITH:
                spd::algo::quicksort(fles_target_, fles_target_.size(), sort_by_image_with());
                break;
                
            case sort_policie::IMAGE_HEIGTH:
                spd::algo::quicksort(fles_target_, fles_target_.size(), sort_by_image_height());
                break;
            
            case sort_policie::IMAGE_SIZE:
                spd::algo::quicksort(fles_target_, fles_target_.size(), sort_by_image_size());
                break;
        }
    }
}


bool program::rename_files_target()
{
    bool succ = true;
    
    for (auto& x : fles_target_)
    {
        if (x->rename() != 0)
        {
            succ = false;
        }
    }
    
    return succ;
}


bool program::get_image_size(
        const std::filesystem::path& img_pth,
        std::size_t* wdth,
        std::size_t* hght
) const noexcept
{
    bool succ = true;
    
    if (is_jpeg_extension(img_pth))
    {
        if (!(succ = get_jpeg_image_size(img_pth, wdth, hght)))
        {
            std::cout << spd::ios::set_light_red_text << "Error, " << img_pth.filename()
                      << " is not a jpeg image" << spd::ios::newl;
        }
    }
    else if (is_png_extension(img_pth))
    {
        if (!(succ = get_png_image_size(img_pth, wdth, hght)))
        {
            std::cout << spd::ios::set_light_red_text << "Error, " << img_pth.filename()
                      << " is not a png image" << spd::ios::newl;
        }
    }
    
    return succ;
}


struct jpeg_error
{
    struct jpeg_error_mgr pub;
    jmp_buf setjmp_buffer;
};


METHODDEF(void)
jpeg_error_exit (j_common_ptr cinfo)
{
    jpeg_error* myerr = (jpeg_error*)cinfo->err;
    longjmp(myerr->setjmp_buffer, 1);
}


bool program::get_jpeg_image_size(
        const std::filesystem::path& img_pth,
        std::size_t* wdth,
        std::size_t* hght
) const noexcept
{
    jpeg_decompress_struct jpeg_inf;
    struct jpeg_error jerr;
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


bool program::get_png_image_size(
        const std::filesystem::path& img_pth,
        std::size_t* wdth,
        std::size_t* hght
) const noexcept
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
    if ((png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr)) ==
            nullptr)
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


bool program::is_jpeg_extension(const std::filesystem::path& img_pth) const noexcept
{
    return jpeg_exts_.count(img_pth.extension()) > 0;
}


bool program::is_png_extension(const std::filesystem::path& img_pth) const noexcept
{
    return png_exts_.count(img_pth.extension()) > 0;
}


std::unordered_set<std::string> const program::jpeg_exts_ = {".jpeg", ".jpg", ".JPEG", ".JPG"};

std::unordered_set<std::string> const program::png_exts_ = {".png", ".PNG"};


}
