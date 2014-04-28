# Delete build files
find . -name "cmake_install.cmake" -exec rm {} \;
find . -name "CMakeCache.txt" -exec rm {} \;
rm -rf CMakeFiles

# Install to /usr
cmake -DCMAKE_INSTALL_PREFIX=/usr . && make all install

# Test local installation
cmake . && make DESTDIR=tmp install

# Use debug build
cmake -DCMAKE_BUILD_TYPE=Debug .

# Use Clang with address sanitizer
CC=/usr/bin/clang CXX=/usr/bin/clang++ cmake -DCMAKE_BUILD_TYPE=Debug .

