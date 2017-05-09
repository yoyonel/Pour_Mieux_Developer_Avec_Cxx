# https://cmake.org/pipermail/cmake/2008-November/025563.html
## Variables:
# 
# OUTPUT_DIRECTORY: Directory where the assemblu file will be placed (For example "/home/manu/listings")
# ASSEMBLY_LISTING_FILE: Assembly listing filename (For example "foo.s")
# SOURCE_FILENAME: Name of the sourcefile being compiled (See bellow). For example "foo", from foo.cpp.
# TARGET: Target being compiled (Mostly an executable target). For example "foo".

include(cmake/parse_arguments.cmake)

# https://gist.githubusercontent.com/Manu343726/64c0a75c089ad96d22cb/raw/4043f4f4532a8e9fa245f8166e950933c188f59e/assembly_out.cmake
macro(AssemblyOut TARGET)
    parse_arguments(${TARGET}
        "OUTPUT_PATH;ASSEMBLY_LISTING_FILE;SOURCE_FILENAME"
        ""
        ${ARGN}
    )
  if(MSVC)
    # Trust me, Microsoft docs suck. 
    target_compile_options(${TARGET} "/Fa${${TARGET}_OUTPUT_PATH}/${ASSEMBLY_LISTING_FILE}" /FA)
  else()
    # The trick is that makefiles generator defines a [sourcefile].s target for each sourcefile of a target to generate the listing 
    # of that file. We hook a command after build to invoke that target and copy the result file to our ourput directory:
    add_custom_command(TARGET ${TARGET}
                       POST_BUILD
                       COMMAND make ARGS ${${TARGET}_SOURCE_FILENAME}.s
                       COMMAND ${CMAKE_COMMAND} -E copy
                           "${CMAKE_BINARY_DIR}/CMakeFiles/${TARGET}.dir/${${TARGET}_SOURCE_FILENAME}.cpp.s"
                           "${${TARGET}_OUTPUT_PATH}/${${TARGET}_ASSEMBLY_LISTING_FILE}"
                       WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
  endif()
endmacro(AssemblyOut TARGET)