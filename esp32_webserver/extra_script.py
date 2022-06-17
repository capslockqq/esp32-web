Import("env")
cvars = env.Dictionary()


cmakeListsFileEsp32 = """
# This file was automatically generated for projects\n
# without default 'CMakeLists.txt' file.\n
FILE(GLOB_RECURSE app_sources ${CMAKE_SOURCE_DIR}/src/*.*)\n
list(REMOVE_ITEM app_sources ${CMAKE_SOURCE_DIR}/src/native/main.cpp)\n
list(REMOVE_ITEM app_sources ${CMAKE_SOURCE_DIR}/src/simulation/main.cpp)\n
list(REMOVE_ITEM app_sources ${CMAKE_SOURCE_DIR}/src/simulation/simulation.cpp)\n
list(REMOVE_ITEM app_sources ${CMAKE_SOURCE_DIR}/src/web/echo_server.cpp)\n
idf_component_register(SRCS ${app_sources})"""


cmakeListsFileNative = """
"""

with open('src/CMakeLists.txt', 'w+', encoding='utf8') as fd:
    if cvars['PIOPLATFORM'] == 'espressif32':
        fd.write(cmakeListsFileEsp32)
    if cvars['PIOPLATFORM'] == 'native':
        fd.write(cmakeListsFileNative)
