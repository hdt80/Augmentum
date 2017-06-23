# Compilers
CXX = g++

# Directories used for input and output
SRCDIR = src
BUILDDIR = build
EXEDIR = .
INCLUDEDIR = include
TESTDIR = test

# Output name of the compiled library
OUTPUT_NAME = libAG-Llua
TEST_OUTPUT_NAME = ag_lua

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

# Flags used to compile .cpp files
CXX_FLAGS += $(CXX_WARNS) -c -g -O2 -I$(INCLUDEDIR) -std=c++14

# Compiling all the .cpp files into .o files
$(OBJS): $(BUILDDIR)/%.o : $(SRCDIR)/%.cpp
	$(CXX) $(CXX_FLAGS) -o "$@" "$<"

# Building the library file
.PHONY: build
build: $(OBJS)
	ar rcs $(EXEDIR)/$(OUTPUT_NAME).a $^
	cp $(INCLUDEDIR)/*.h $(TESTDIR)/$(INCLUDEDIR)

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
