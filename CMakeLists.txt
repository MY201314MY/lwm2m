# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20.0)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(lwm2m_client)

FILE(GLOB app_sources src/*.c)
target_sources(app PRIVATE ${app_sources})

include(${ZEPHYR_BASE}/samples/net/common/common.cmake)

set(gen_dir ${CMAKE_CURRENT_BINARY_DIR}/cert)
zephyr_include_directories(${gen_dir})
generate_inc_file_for_target(
    app
    cert/LeshanServerCertificate.der
    ${gen_dir}/LeshanServerCertificate.der.inc
)