add_executable(test test.cpp)

target_link_libraries(test PRIVATE DanteLL DLOG_project_options DLOG_project_warnings)
target_include_directories(test PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include")
target_compile_features(test PUBLIC cxx_std_20)

# target_compile_definitions(${PROJECT_NAME} PUBLIC SOME_MACROS)
