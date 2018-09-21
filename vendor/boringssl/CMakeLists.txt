cmake_minimum_required(VERSION 3.5)

project(external-boringssl)

include(FetchContent)

FetchContent_Declare(
    boringssl
    GIT_REPOSITORY 	https://boringssl.googlesource.com/boringssl
    GIT_TAG		fips-20180730
    # URL https://boringssl.googlesource.com/boringssl/+archive/66005f41fbc3529ffe8d007708756720529da20d.tar.gz
    PREFIX boringssl
)

FetchContent_GetProperties(boringssl)
if(NOT boringssl_POPULATED)
    FetchContent_Populate(boringssl)
    set(OPENSSL_NO_ASM ON)
    set(CMAKE_CXX_FLAGS "-Wno-unused-parameter")
    set(CMAKE_C_FLAGS "-Wno-unused-parameter")
    add_subdirectory(${boringssl_SOURCE_DIR} ${boringssl_BINARY_DIR})
    target_include_directories( ssl INTERFACE ${boringssl_SOURCE_DIR}/include )
endif()