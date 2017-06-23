# Compilers
CXX = g++

### Directory vars, these must match the library it is testing
SRCDIR = src
BUILDDIR = build
EXEDIR = .
INCLUDEDIR = include
LIBDIR = ..

# Output name of the compiled program
OUTPUT_NAME = ag_logger

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

# Linking all the .o files and with the libs
.PHONY: build
build: $(OBJS)
	$(CXX) $^ $(LINKER_FLAGS) -L$(LIBDIR) -lAG-Logger -o ./$(EXEDIR)/$(OUTPUT_NAME)

# Run the generated program
.PHONY: run
run:
	./$(EXEDIR)/$(OUTPUT_NAME)

# Run program in gdb
.PHONY: debug
debug:
	gdb ./$(EXEDIR)/$(OUTPUT_NAME)

# Run the program in valgrind
.PHONY: val
val:
	valgrind ./$(EXEDIR)/$(OUTPUT_NAME)
	
# Cleaning everything up
.PHONY: clean
clean:
	$(MAKE) -f makefile.$(ARCH) clean
