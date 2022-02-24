import pathlib
Import("env")
cvars = env.Dictionary()


cmakeListsFileEsp32 = """
# This file was automatically generated for projects\n
# without default 'CMakeLists.txt' file.\n
FILE(GLOB_RECURSE app_sources ${CMAKE_SOURCE_DIR}/src/esp32/*.*)\n
idf_component_register(SRCS ${app_sources})"""
cmakeListsFileNative = """
# This file was automatically generated for projects\n
# without default 'CMakeLists.txt' file.\n
FILE(GLOB_RECURSE app_sources ${CMAKE_SOURCE_DIR}/src/native/*.*)\n
idf_component_register(SRCS ${app_sources})"""

with open('src/CMakeLists.txt', 'w+', encoding='utf8') as fd:
    print('cvars!!', cvars['PIOPLATFORM'])
    if cvars['PIOPLATFORM'] == 'espressif32':
        print('LOL ESP32 WOOP WOOP')
        fd.write(cmakeListsFileEsp32)
    if cvars['PIOPLATFORM'] == 'native':
        print('LOL NATIVE WOOP WOOP')
        fd.write(cmakeListsFileNative)
