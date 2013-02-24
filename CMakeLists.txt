cmake_minimum_required(VERSION 2.6)
project (Image-Sequence-Parser)

set(SRCS
    Main.cpp
)

find_package(Boost)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

add_definitions(-DBOOST_TEST_DYN_LINK)

include_directories(${INCLUDE_DIRECTORIES} ${Boost_INCLUDE_DIRS})

link_directories(${LINK_DIRECTORIES} ${Boost_LIBRARY_DIRS})

add_executable(Image-Sequence-Parser ${SRCS})

target_link_libraries(Image-Sequence-Parser
    ${Boost_LIBRARIES}

    -lboost_system
    -lboost_iostreams
    -lboost_filesystem
)