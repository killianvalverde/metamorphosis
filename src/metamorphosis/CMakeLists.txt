set(METAMORPHOSIS_LIB_SOURCE_FILES
        base_name.hpp
        base_number.cpp
        base_number.hpp
        exception.hpp
        forward_declarations.hpp
        image_utils.cpp
        image_utils.hpp
        program.cpp
        program.hpp
        program_args.hpp
        sort_policies.hpp
        sort_strategies.cpp
        sort_strategies.hpp
        target_file.cpp
        target_file.hpp
        target_image.cpp
        target_image.hpp
)

add_library(libmetamorphosis STATIC ${METAMORPHOSIS_LIB_SOURCE_FILES})

target_link_libraries(libmetamorphosis
        -ljpeg
        -lpng
        -lspeed
)
