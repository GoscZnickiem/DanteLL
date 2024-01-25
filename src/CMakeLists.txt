set(DANTELL_SRC 

	DanteLL.cpp

)

add_library(DanteLL ${DANTELL_SRC})

target_include_directories(DanteLL PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include")

target_compile_features(DanteLL PUBLIC cxx_std_20)
# target_compile_definitions(DanteLL PUBLIC SOME_MACROS)
