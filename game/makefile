# Compilers
CXX = g++

# Directories used for input and output
SRCDIR = src
BUILDDIR = build
EXEDIR = .
INCLUDEDIR = include

# Name of the output file
OUTPUT_NAME = Augmentum

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

# Warning to use when during compiliation
CXX_WARNS += -Wall -Wextra -Wno-unused-parameter -Wno-format -Wno-varargs \
			 -Wno-unused-variable

# Directories to include during compliation
# NOTE: Only the files included fomr ../lib/include/ are included, not the ones
# 		in the include folder. This is to ensure that everyone is using the same
# 		header files.
# 		The files in include are copies to ../lib/include/ before compiliation
CXX_INCLUDES += -I../lib/include/

# Flags used to compile .cpp files
CXX_FLAGS += $(CXX_WARNS) -c -g -O2 $(CXX_INCLUDES) -std=c++14

# Compiling all the .cpp files into .o files
$(OBJS): $(BUILDDIR)/%.o : $(SRCDIR)/%.cpp
	$(CXX) $(CXX_FLAGS) -o "$@" "$<"

# Building the program and copying all the headers into the lib include folder
.PHONY: build
build: $(OBJS)
	$(CXX) $(LINKER_FLAGS) $^ -o ./$(EXEDIR)/$(OUTPUT_NAME)

# Copy the header files into the ../lib/include/ folder
.PHONY: copy
copy:
	cp -r $(INCLUDEDIR)/* ../lib/include/game/

# Running the program
.PHONY: run
run:
	./$(EXEDIR)/$(OUTPUT_NAME)

# Run test program in gdb
.PHONY: debug
debug:
	gdb ./$(EXEDIR)/$(OUTPUT_NAME)

# Run the test program in valgrind
.PHONY: val
val:
	valgrind ./$(EXEDIR)/$(OUTPUT_NAME)
	
# Cleaning everything up
.PHONY: clean
clean:
	$(MAKE) -f makefile.$(ARCH) clean
