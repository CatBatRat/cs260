cpp=main.cpp ParseTree.cpp
header=ParseTree.h
all=$(header) $(cpp)

CPP=clang++
CFLAGS=-Wall -Wextra -Werror

out=double-link.exe
comp=$(cpp) -o $(out)

tags:
	ctags $(all)

compile: $(cpp)
	$(CPP) $(CFLAGS) $(comp)

run: compile
	./out.bat $(out)
