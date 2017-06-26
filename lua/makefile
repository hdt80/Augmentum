# Compilers
CXX = g++

# Directories used for input and output
SRCDIR = src
BUILDDIR = build
EXEDIR = .
INCLUDEDIR = include
TESTDIR = test

# Output name of the compiled library
OUTPUT_NAME = libAG-Lua
TEST_OUTPUT_NAME = ag_lua

# Name to store under the root directory's include folder
LIB_NAME = lua

# Export variables used in other makefiles (cleaning, testing programs)
export BUILDDIR
export EXEDIR
export OUTPUT_NAME

ARCH := $(shell uname)

# Check what architecture this is being built for
ifeq ($(ARCH), Linux)
	ARCH = linux
else
	ARCH = mingw
endif

# Where the sources are located
SRCS = $(wildcard $(SRCDIR)/*.cpp)
SRCS += $(wildcard $(SRCDIR)/*/*.cpp)

# Where the compiled objects are located
OBJS = $(patsubst $(SRCDIR)/%.cpp, $(BUILDDIR)/%.o, $(SRCS))

# Enable all warnings but format and unused variables
CXX_WARNS += -Wall -Wextra -Wno-unused-parameter -Wno-format \
			 -Wno-unused-variable -Wno-varargs

# Directories to include during compliation
CXX_INCLUDES += -I$(INCLUDEDIR) -I../lib/include/

# Libraries to link to
CXX_LIBS += -llua

# Flags used to compile .cpp files
CXX_FLAGS += $(CXX_WARNS) -c -g -O2 $(CXX_INCLUDES) -std=c++14 \
			 -ftemplate-depth=4096

# Compiling all the .cpp files into .o files
$(OBJS): $(BUILDDIR)/%.o : $(SRCDIR)/%.cpp
	$(CXX) $(CXX_FLAGS) -o "$@" "$<"

# Real building target, done this way to compiling doesn't depend on copy
.PHONY: build
build: compile copy

# Building the library file
.PHONY: compile
compile: $(OBJS)
	ar rcs $(EXEDIR)/$(OUTPUT_NAME).a $^

# Copy the header files into the ../lib/include/ folder
.PHONY: copy
copy:
	cp $(INCLUDEDIR)/*.h $(TESTDIR)/$(INCLUDEDIR)
	cp $(INCLUDEDIR)/*.h ../lib/include/$(LIB_NAME)
	cp $(EXEDIR)/$(OUTPUT_NAME).a ../lib/

# Run the test program
.PHONY: run
run:
	./$(TESTDIR)/$(EXEDIR)/$(TEST_OUTPUT_NAME)

# Run test program in gdb
.PHONY: debug
debug:
	gdb ./$(TESTDIR)/$(EXEDIR)/$(TEST_OUTPUT_NAME)

# Run the test program in valgrind
.PHONY: val
val:
	valgrind ./$(TESTDIR)/$(EXEDIR)/$(TEST_OUTPUT_NAME)

# Building test program
.PHONY: test
test: build
	$(MAKE) -C $(TESTDIR) -f makefile build
	
# Cleaning everything up
.PHONY: clean
clean:
	$(MAKE) -f makefile.$(ARCH) clean
	$(MAKE) -C $(TESTDIR) -f makefile clean
