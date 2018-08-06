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

#include <speed/speed.hpp>
#include <speed/speed_alias.hpp>

#include "program.hpp"


int main(int argc, char* argv[])
{
    spd::ap::arg_parser ap("metamorphosis");
    ap.add_help_text("Rename a set of files following a specified patern.\n");
    ap.add_key_value_arg({"--base-names", "-bnm"}, "Base names for file targets.",
                         {spd::ap::avt_t::STRING}, 1u, ~0u,
                         spd::ap::af_t::DEFAULT_ARG_FLAGS | spd::ap::af_t::ALLWAYS_REQUIRED);
    ap.add_key_value_arg({"--base-numbers", "-bnr"}, "Base numbers for file targets.",
                         {spd::ap::avt_t::UINT64}, 1u, ~0u,
                         spd::ap::af_t::DEFAULT_ARG_FLAGS | spd::ap::af_t::ALLWAYS_REQUIRED);
    ap.add_key_arg({"--sort-alphabetically", "-sa"},
                   "Sort alphabetically file targets before rename.");
    ap.add_key_arg({"--sort-by-image-size", "-siz"},
                   "Sort by image size file targets before rename.");
    ap.add_key_value_arg({"--regex", "-reg"}, "Regex that all file targets have to match.");
    ap.add_help_arg({"--help"}, "Display this help and exit.");
    ap.add_gplv3_version_arg({"--version"}, "Output version information and exit", "1.0.0", "2023",
                             "Killian Valverde");
    ap.add_keyless_arg("DIR", "Directory", "", {spd::ap::avt_t::RWX_DIR});
    ap.parse_args((unsigned int)argc, argv);
    
    std::vector<metamorphosis::base_name> bse_names;
    std::vector<metamorphosis::base_number> bse_numbers;
    std::vector<metamorphosis::sort_policie> sort_polcs;
    std::regex regx(ap.get_front_arg_value_as<std::string>("--regex", ".*"));
    
    for (auto& x : ap.get_arg_values_as<std::string>("--base-names"))
    {
        bse_names.emplace_back(x);
    }
    for (auto& x : ap.get_arg_values_as<std::size_t>("--base-numbers"))
    {
        bse_numbers.emplace_back(x);
    }
    if (ap.arg_found("--sort-alphabetically"))
    {
        sort_polcs.push_back(metamorphosis::sort_policie::ALPHABETICALLY);
    }
    if (ap.arg_found("--sort-by-image-size"))
    {
        sort_polcs.push_back(metamorphosis::sort_policie::IMAGE_SIZE);
    }
    
    metamorphosis::program prog(
            ap.get_front_arg_value_as<std::filesystem::path>("DIR"),
            std::move(bse_names),
            std::move(bse_numbers),
            std::move(sort_polcs),
            std::move(regx));
    
    return prog.execute();
}
