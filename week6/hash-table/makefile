args=-Wall -Wextra
out=hash.exe

# source files
cpp=$(wildcard src/*.cpp)
# deps
deps=$(wildcard deps/*.h)

# tests
mydriver=tests/main.cpp
driver=tests/driver.cpp

mt:
	clang++ $(args) $(cpp) $(mydriver) -o my-$(out)

dt:
	clang++ $(args) $(cpp) $(driver) -o driver-$(out)

mr:
	start .\run.bat my-$(out)

dr:
	start .\run.bat driver-$(out)
