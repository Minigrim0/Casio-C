# Configure with [fxsdk build-fx] or [fxsdk build-cg], which provide the
# toolchain file and module path of the fxSDK

cmake_minimum_required(VERSION 3.15)
project(cache_sim)

include(GenerateG1A)
include(GenerateG3A)
include(Fxconv)
find_package(Gint 2.1 REQUIRED)

set(SOURCES
  src/main.c
  # ...
)
# Shared assets, fx-9860G-only assets and fx-CG-50-only assets
set(ASSETS
  # ...
)
set(ASSETS_fx
  assets-fx/c_h.png
  assets-fx/c_v.png
  assets-fx/l_h.png
  assets-fx/l_v.png
  assets-fx/r_h.png
  assets-fx/r_v.png
  assets-fx/font.png
)
set(ASSETS_cg
  assets-cg/example.png
  # ...
)

fxconv_declare_assets(${ASSETS} ${ASSETS_fx} ${ASSETS_cg} WITH_METADATA)

add_executable(cache_sim ${SOURCES} ${ASSETS} ${ASSETS_${FXSDK_PLATFORM}})
target_compile_options(cache_sim PRIVATE -Wall -Wextra -Os)
target_link_libraries(cache_sim Gint::Gint)

if("${FXSDK_PLATFORM_LONG}" STREQUAL fx9860G)
  generate_g1a(TARGET cache_sim OUTPUT "Cache.g1a"
    NAME "Cache" ICON assets-fx/icon.png)
elseif("${FXSDK_PLATFORM_LONG}" STREQUAL fxCG50)
  generate_g3a(TARGET cache_sim OUTPUT "cache_sim.g3a"
    NAME "cache_sim" ICONS assets-cg/icon-uns.png assets-cg/icon-sel.png)
endif()
