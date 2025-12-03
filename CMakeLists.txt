cmake_minimum_required(VERSION 4.1.2)
project(contrary VERSION 0.0.0 LANGUAGES CXX ASM_NASM)

set(CMAKE_CXX_FLAGS                 "${CMAKE_CXX_FLAGS} -O2 -fno-exceptions -fno-rtti -ffreestanding -Wall -Wextra -Werror")
set(CMAKE_EXE_LINKER_FLAGS          "-T ${CMAKE_SOURCE_DIR}/targets/x86_64/linker.ld -nostdlib -no-pie")
set(CMAKE_ASM_NASM_OBJECT_FORMAT    "elf64")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_SOURCE_DIR}/targets/x86_64/iso/boot)
set(CMAKE_CXX_STANDARD              26)
set(CMAKE_EXPORT_COMPILE_COMMANDS   ON)
set(CMAKE_POSITION_INDEPENDENT_CODE OFF)

option(GRUB_MKRESCUE "Use grub-mkrescue to create a bootable ISO after compilation" ON)

file(GLOB_RECURSE ASM_SOURCES ${CMAKE_SOURCE_DIR}/kernel/*.asm)
file(GLOB_RECURSE CXX_SOURCES ${CMAKE_SOURCE_DIR}/kernel/*.cpp)

add_executable(${PROJECT_NAME} ${ASM_SOURCES} ${CXX_SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME ${PROJECT_NAME}.bin)
target_compile_definitions(${PROJECT_NAME} PRIVATE PROJECT_VERSION="${PROJECT_VERSION}")

if(GRUB_MKRESCUE)
    add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND}
            -E remove ${CMAKE_SOURCE_DIR}/targets/x86_64/iso/${PROJECT_NAME}.iso
        COMMAND grub-mkrescue
            -o ${CMAKE_SOURCE_DIR}/targets/x86_64/iso/${PROJECT_NAME}.iso
            ${CMAKE_SOURCE_DIR}/targets/x86_64/iso
        COMMENT "Creating bootable ISO with grub-mkrescue..."
    )
endif()
