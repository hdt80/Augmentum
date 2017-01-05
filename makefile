# Compilers
CXX = g++
#CXX = clang++
CC = gcc

ARCH := $(shell uname)

# Directories used for input and output
SRCDIR = src/src
BUILDDIR = build
EXEDIR = bin
INCLUDEDIR = src/include
VERBOSE = 0

# Export vars so they can be used in other Makefiles
export SRCDIR
export BUILDDIR
export EXEDIR
export INCLUDEDIR
export VERBOSE
export OUTPUT_NAME

# Running Linux? 
ifeq ($(ARCH), Linux)
	LINKER_FLAGS = -lsfml-graphics -lsfml-window -lsfml-system -llua -Llib -lBox2D
	# Turn to lowercase to ensure the file is found
	ARCH = linux
# Windows?
else
	LINKER_FLAGS = -Llib -lsfml-graphics -lsfml-window -lsfml-system -llua -lbox2d
	ARCH = mingw
endif

export ARCH
export LINKER_FLAGS

# Debug flags
ifeq ($(VERBOSE), 1)
	CXX_FLAGS += -M -MF /dev/stdout
endif

# Enable all warnings but format and unused variables
CXX_FLAGS += -Wall -Wno-format -Wno-unused-variable -Wno-varargs -c -g -O0 -Iinclude -I$(INCLUDEDIR) -fbuiltin -fpermissive -ftemplate-depth=4096 -std=c++14

export CXX_FLAGS
export CXX

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

$(COBJS): $(BUILDDIR)/%.o : $(SRCDIR)/%.c
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
	$(MAKE) -f makefile.$(ARCH) clean
