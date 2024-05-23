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
 * @file        main/main.hpp
 * @brief       metamorphosis entry point.
 * @author      Killian Valverde
 * @date        2024/05/19
 */

#include <speed/speed.hpp>

#include "../metamorphosis/program.hpp"
#include "argparse_extension.hpp"


int main(int argc, char* argv[])
{
    std::string messge;
    int retv;
    
    try 
    {
        metamorphosis::program_args prog_args;
        spd::ap::arg_parser ap("metamorphosis");
        
        ap.add_help_menu()
                .description("Rename a set of files following a specified patern.")
                .epilogue("$ metamorphosis \"./\" -rx \".*(jpeg|jpg|png).*\" -nm \"Blue - \" \\\n"
                          "    -sr ALPHABETICALLY IMAGE_SIZE")
                .print_commands(true);

        ap.add_key_value_arg("--regex", "-rx")
                .description("Regex that all the files have to match in order to be considered.")
                .values_names("REGEX")
                .store_into(&prog_args.fltr_regx)
                .mandatory(true);

        ap.add_key_value_arg("--names", "-nm")
                .description("Names to set.")
                .values_names("STRING")
                .minmax_values(1, ~0ull)
                .store_into(&prog_args.bse_nms)
                .mandatory(true);

        ap.add_key_value_arg("--numbers", "-nr")
                .description("Numbers to set.")
                .values_names("INTEGER")
                .minmax_values(1, ~0ull)
                .store_into(&prog_args.bse_nrs)
                .mandatory(true)
                .values_with_prefix(true);

        ap.add_key_value_arg("--sort", "-sr")
                .description("Sort in a specified way. "
                             "(ALPHABETICALLY | IMAGE_WITH | IMAGE_HEIGHT | IMAGE_SIZE)")
                .values_names("POLICY")
                .minmax_values(1, ~0ull)
                .store_into(&prog_args.srt_polics);

        ap.add_keyless_arg("DIR")
                .description("Directory in which perform the operation.")
                .store_into(&prog_args.trg_dir);
                
        ap.add_help_arg("--help", "-h")
                .description("Display this help and exit.");
                
        ap.add_version_arg("--version", "-v")
                .description("Output version information and exit.")
                .gplv3_version_information("0.1.0", "2024", "Killian Valverde");

        ap.parse_args(argc, argv);
        
        metamorphosis::program prog(std::move(prog_args));

        return prog.execute();
    }
    catch (const metamorphosis::exception_base& e)
    {
        messge = e.what();
        retv = 1;
    }
    catch (const std::exception& e)
    {
        messge = e.what();
        retv = -1;
    }
    catch (...)
    {
        messge = "Unknown error";
        retv = -1;
    }
    
    std::cerr << spd::ios::newl
              << spd::ios::set_light_red_text << "count_kbhit: "
              << spd::ios::set_default_text << messge
              << std::endl;

    return retv;
}
