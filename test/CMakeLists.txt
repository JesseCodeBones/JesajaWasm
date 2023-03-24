file(GLOB test_sources CONFIGURE_DEPENDS ./lexer/*.cpp)
find_package(GTest REQUIRED)
add_executable(
  unit_test
  ${test_sources}
)
target_link_libraries(
  unit_test
  GTest::gtest_main
)
file(GLOB sources CONFIGURE_DEPENDS ../src/**/*.cpp ../src/**/*.hpp)
target_sources(unit_test PUBLIC ${sources})
include(GoogleTest)
gtest_discover_tests(unit_test)