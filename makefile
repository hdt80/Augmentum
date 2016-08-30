# Compilers
CXX = g++
#CXX = clang++
CC = gcc

UNAME := $(shell uname)

# Directories used for input and output
SRCDIR = src/src
BUILDDIR = build
EXEDIR = bin
INCLUDEDIR = src/include

# Running Linux? 
ifeq ($(UNAME), Linux)
	LINKER_FLAGS = -lsfml-graphics -lsfml-window -lsfml-system -llua -lbox2d
# Windows?
else
	LINKER_FLAGS = -Llib -lsfml-graphics -lsfml-window -lsfml-system -llua -lbox2d
endif

# Enable all warnings but format and unused variables
CXX_FLAGS = -Wall -Wno-format -Wno-unused-variable -Wno-varargs -c -g -O0 -fbuiltin -fpermissive -std=c++14 -I include -I $(INCLUDEDIR)

OUTPUT_NAME = Augmentum

# Where the sources are located
SRCS = $(wildcard $(SRCDIR)/*.cpp)
SRCS += $(wildcard $(SRCDIR)/*/*.cpp)

CSRCS = $(wildcard $(SRCDIR)/*.c)

# Where the compiled objects are located
OBJS = $(patsubst $(SRCDIR)/%.cpp, $(BUILDDIR)/%.o, $(SRCS))
COBJS = $(patsubst $(SRCDIR)/%.c, $(BUILDDIR)/%.o, $(CSRCS))

# Linking all the .o files and with the libs
build: $(OBJS) $(COBJS)
	$(CXX) $^ $(LINKER_FLAGS) -o ./bin/$(OUTPUT_NAME)

# Compiling all the .cpp files into .o files
$(OBJS): $(BUILDDIR)/%.o : $(SRCDIR)/%.cpp
	$(CXX) $(CXX_FLAGS) -o "$@" "$<"

$(COBJS): $(BUILDDIRT)/%.o : $(SRCDIR)/%.c
	$(CC) $(CC_FLAGS) -o "$@" "$<"

# Running the created exe
.PHONY: run
run:
	./$(EXEDIR)/$(OUTPUT_NAME)

# Run gdb
.PHONY: debug
debug:
	gdb ./$(EXEDIR)/$(OUTPUT_NAME)

# Run valgrind
.PHONY: val
val:
	valgrind ./$(EXEDIR)/$(OUTPUT_NAME)
	
# Cleaning everything up
.PHONY: clean
clean:
	rm $(BUILDDIR)/*.o && rm $(EXEDIR)/$(OUTPUT_NAME)
