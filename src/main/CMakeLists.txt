set(METAMORPHOSIS_SOURCE_FILES
        argparse_extension.hpp
        main.cpp
)

add_executable(metamorphosis ${METAMORPHOSIS_SOURCE_FILES})
target_link_libraries(metamorphosis libmetamorphosis)
install(TARGETS metamorphosis DESTINATION bin)
