set(TEST_NAME "non_reg_test")

add_executable(${TEST_NAME} testRngStream.cpp)

target_link_libraries(${TEST_NAME}
  doctest
  RngStreams
  )

add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
