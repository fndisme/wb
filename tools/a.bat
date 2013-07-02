set PATH=d:\lib\cppcms-thirdlib\debug\bin;%PATH%
cmake -G "NMake Makefiles" -DCMAKE_BUILD_TYPE=Debug -DDISABLE_SHARED=ON -DCMAKE_INCLUDE_PATH=d:/lib/cppcms-thirdlib/debug/include -DCMAKE_LIBRARY_PATH=d:/lib/cppcms-thirdlib/debug/lib -DCMAKE_INSTALL_PREFIX=d:/lib/apps/debug d:/lib/cppcms-1.0.4
nmake
nmake test
nmake install
