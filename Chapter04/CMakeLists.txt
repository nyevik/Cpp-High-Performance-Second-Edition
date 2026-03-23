cmake_minimum_required(VERSION 3.12)

project(Chapter04-Data_Structures)

set(CHAPTER04_TEST_SOURCES
  cache_thrashing.cpp
  parallel_arrays.cpp
  priority_queues.cpp
  read_file_into_string.cpp
  sum_scores.cpp
  unordered_sets.cpp
  my_cache_thrashing.cpp
  my_vector.cpp
  my_file_basic_string.cpp
)

add_executable(${PROJECT_NAME}
  main.cpp
  ${CHAPTER04_TEST_SOURCES}
)
target_link_libraries(${PROJECT_NAME} PRIVATE GTest::gtest)

foreach(SOURCE_FILE IN LISTS CHAPTER04_TEST_SOURCES)
  get_filename_component(TARGET_SUFFIX "${SOURCE_FILE}" NAME_WE)
  add_executable("Chapter04-${TARGET_SUFFIX}" EXCLUDE_FROM_ALL "${SOURCE_FILE}")
  target_link_libraries("Chapter04-${TARGET_SUFFIX}" PRIVATE GTest::gtest_main)
endforeach()
add_executable(my_vector_test EXCLUDE_FROM_ALL my_vector.cpp)
target_link_libraries(my_vector_test PRIVATE GTest::gtest_main)

add_executable(my_file_basic_string_test EXCLUDE_FROM_ALL my_file_basic_string.cpp)
target_link_libraries(my_file_basic_string_test PRIVATE GTest::gtest_main)
