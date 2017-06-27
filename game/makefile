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
# NOTE: Only the files included from ../lib/include/ are included, not the ones
# 		in the include folder. This is to ensure that everyone is using the same
# 		header files.
# 		The files in include are copies to ../lib/include/ before compiliation
CXX_INCLUDES += -I../lib/include/

# Libraries to link against. Libraries provided by the system go before the line
# break, while user libraries come after
CXX_LIBS += -llua -ldl -lsfml-graphics -lsfml-window -lsfml-system \
			-L../lib -lAG-Logger -lAG-Lua -lAG-Util -lBox2D

# Flags used to compile .cpp files
CXX_FLAGS += $(CXX_WARNS) -c -g -O2 $(CXX_INCLUDES) -std=c++14

################################################################################
### Targets
################################################################################

################################################################################
# Compiling all the .cpp files into .o files
################################################################################
$(OBJS): $(BUILDDIR)/%.o : $(SRCDIR)/%.cpp
	$(CXX) $(CXX_FLAGS) -o "$@" "$<"

################################################################################
# Build the program completely, generating an executable and copying the header
# files into the correct location. The copy must be done first as compile
# depends on the header files placed by copy. compile does not call copy as the
# special variable $^ will match copy if it is a target
################################################################################
.PHONY: build
build: copy compile

################################################################################
# Link the program all together, using the object files created from $(OBJS)
################################################################################
.PHONY: compile
compile: $(OBJS)
	$(CXX) $^ $(CXX_LIBS) -o ./$(EXEDIR)/$(OUTPUT_NAME)

################################################################################
# Copy the headers used to compile into ../lib/include, where all the includes
# are located at. When compiling, the include/ folder will not be used,
# ../lib/include/ will be used instead. This is to ensure consistent header 
# files across all libraries
################################################################################
.PHONY: copy
copy:
	find ../lib/include/game/ -type f -name \*.h -exec rm {} +
	cp -r $(INCLUDEDIR)/* ../lib/include/game/

################################################################################
# Run the program
################################################################################
.PHONY: run
run:
	./$(EXEDIR)/$(OUTPUT_NAME)

################################################################################
# Run program in gdb
################################################################################
.PHONY: debug
debug:
	gdb ./$(EXEDIR)/$(OUTPUT_NAME)

################################################################################
# Run the program in valgrind
################################################################################
.PHONY: val
val:
	valgrind ./$(EXEDIR)/$(OUTPUT_NAME)
	
################################################################################
# Clean all the files created during building. This is done by calling the
# makefile for the proper environment
################################################################################
.PHONY: clean
clean:
	$(MAKE) -f makefile.$(ARCH) clean
