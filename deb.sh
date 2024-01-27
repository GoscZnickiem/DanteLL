echo ==================================================================
echo ===				   begin GCC Compilation					===
echo ==================================================================
cmake . --preset unixlike-gcc-debug
cd build/unixlike-gcc-debug
ninja
echo ==================================================================
echo ===					  GCC Compilation						===
echo ==================================================================
cd ../..

echo ==================================================================
echo ===				  begin Clang Compilation					===
echo ==================================================================
cmake . --preset unixlike-clang-debug
cd build/unixlike-clang-debug
ninja
echo ==================================================================
echo ===					 Clang Compilation						===
echo ==================================================================
cd ../..

