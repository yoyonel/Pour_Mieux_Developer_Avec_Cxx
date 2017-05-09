cmake_minimum_required(VERSION 2.8.8)
set(PROJECT_NAME_STR LES_TEMPLATES)
project(${PROJECT_NAME_STR} C CXX)

if(CMAKE_COMPILER_IS_GNUCXX)
    add_definitions(-Wall -ansi -Wno-deprecated -pthread)
endif()

if(MSVC)
    #vc 2012 fix for vararg templates
    set(MSVC_COMPILER_DEFS "-D_VARIADIC_MAX=10")
endif() 


add_executable(
    parametrer_une_classe_avec_les_templates
    src/parametrer_une_classe_avec_les_templates.cpp
)

add_executable(
    contraintes_imposees_au_typ_du_parametre
    src/contraintes_imposees_au_type_du_parametre.cpp
)

add_executable(
    fonctions_template
    src/fonctions_template.cpp
)

add_executable(
    fonctions-membres_template
    src/fonctions-membres_template.cpp
)

# erreurs de compilation
# add_executable(
#     fonctions-membres_template_virtual
#     src/fonctions-membres_template_virtual.cpp
# )

add_executable(
    specialiser_un_template
    src/specialiser_un_template.cpp
)

# url: http://stackoverflow.com/questions/10851247/how-to-activate-c-11-in-cmake
# specialiser_un_template.cpp:104:45: warning: variadic templates only available with -std=c++11 or -std=gnu++11
#
# target_compile_features(specialiser_un_template PRIVATE cxx_range_for)
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
if(COMPILER_SUPPORTS_CXX11)
    set_property(TARGET specialiser_un_template PROPERTY CXX_STANDARD 11)
else()
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()


include(cmake/assembly_out.cmake)
# assembly_out(
#     ASSEMBLY_LISTING_FILE specialiser_un_template.s
#     )
# include(cmake/parse_arguments.cmake)

AssemblyOut(specialiser_un_template
    OUTPUT_PATH listing
    ASSEMBLY_LISTING_FILE specialiser_un_template.s
    SOURCE_FILENAME src/specialiser_un_template
    )

add_executable(
    variables_statiques_template
    src/variables_statiques_template.cpp
)

add_executable(
    declarations_templates_d_amitie
    src/declarations_templates_d_amitie.cpp
)
if(COMPILER_SUPPORTS_CXX11)
    set_property(TARGET declarations_templates_d_amitie PROPERTY CXX_STANDARD 11)
else()
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()
