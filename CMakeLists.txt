cmake_minimum_required(VERSION 3.14)
project("priority-queue")
set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_SOURCE_DIR}/p_queue)

set(lib_sources "p_queue/priority_queue.hpp")
add_library(pq_lib INTERFACE ${lib_sources})

# include googletest for testing priority queue
add_subdirectory(3rdparty/gtest)

# add test executable and link with lib
add_executable(pq_test "test/test.cpp")
target_link_libraries(pq_test PUBLIC pq_lib GTest::gtest)

enable_testing()

# copy googletest dll's to executable directory
if(WIN32)
    if(BUILD_SHARED_LIBS)
        add_custom_command(
            TARGET priority-queue POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                $<TARGET_FILE:gtest>
                $<TARGET_FILE:gtest_main>
                $<TARGET_FILE_DIR:priority-queue>
        )
    endif()
endif()

add_test(
    NAME pq_test
    COMMAND pq_test.exe
)
