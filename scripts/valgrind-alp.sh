cmake --build /Users/apetrusca/alpine/alpine-lang/cmake-build-debug --target alp -j 10 &&
leaks --atExit --  /Users/apetrusca/alpine/alpine-lang/cmake-build-debug/alp multi-line.alp