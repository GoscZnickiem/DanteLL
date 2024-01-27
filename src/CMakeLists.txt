set(DANTELL_SRC 

	DanteLL.cpp

)

add_library(${PROJECT_NAME} ${DANTELL_SRC})

target_link_libraries(${PROJECT_NAME} PRIVATE DLOG_project_options DLOG_project_warnings)
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include")
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)
# target_compile_definitions(${PROJECT_NAME} PUBLIC SOME_MACROS)
