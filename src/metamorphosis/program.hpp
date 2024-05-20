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
 * @file        program.hpp
 * @brief       program class header.
 * @author      Killian Valverde
 * @date        2024/05/19
 */
 
#ifndef METAMORPHOSIS_PROGRAM_HPP
#define METAMORPHOSIS_PROGRAM_HPP

#include <memory>
#include <vector>

#include <speed/speed.hpp>

#include "exception.hpp"
#include "target_file.hpp"
#include "program_args.hpp"


/**
 * @brief       Contians all metamorphosis resources.
 */
namespace metamorphosis {


class program
{
public:
    /**
     * @brief       Constructor with parameters.
     * @param       prog_args : The program arguments.
     */
    explicit program(program_args prog_args);

    /**
     * @brief       Destructor.
     */
    ~program();
    
    /**
     * @brief       Execute the program.
     * @return      The value that represents if the program succeed.
     */
    int execute();

private:
    void sort_sources();

    void set_new_file_names();

    bool rename_target_files();

private:
    /** The program arguments. */
    program_args prog_args_;

    std::vector<target_file*> trg_fles_;
};


}


#endif
