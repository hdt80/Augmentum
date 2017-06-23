# Compilers
CXX = g++
CC = gcc

# Directories used for input and output
SRCDIR = src/src
BUILDDIR = build
EXEDIR = bin
INCLUDEDIR = src/include

OUTPUT_NAME = Augmentum

# Export vars so they can be used in other Makefiles
export SRCDIR
export BUILDDIR
export EXEDIR
export INCLUDEDIR
export OUTPUT_NAME

ARCH := $(shell uname)

# System dependent flags
ifeq ($(ARCH), Linux)
	ARCH = linux
else
	ARCH = mingw
endif

# Enable all warnings but format and unused variables

CXX_WARNS = -Wall -Wextra -Wno-unused-parameter -Wno-format \
			-Wno-unused-variable -Wno-varargs

# Where the sources are located
SRCS = $(wildcard $(SRCDIR)/*.cpp)
SRCS += $(wildcard $(SRCDIR)/*/*.cpp)

CSRCS = $(wildcard $(SRCDIR)/*.c)

# Where the compiled objects are located
OBJS = $(patsubst $(SRCDIR)/%.cpp, $(BUILDDIR)/%.o, $(SRCS))
COBJS = $(patsubst $(SRCDIR)/%.c, $(BUILDDIR)/%.o, $(CSRCS))

CXX_FLAGS += $(CXX_WARNS) -MMD -MP -c -g -O2 -Ilib/include -I$(INCLUDEDIR) \
			 -std=c++14

# Libraries used to compile this program. System libraries go before the -L.
# User libraries go after the -L, which all of which should be found in the lib/
# folder
CXX_LIBS += -llua -lbox2d \
			-Llib -lAG-Logger

# Enable and use dependency files
DEPS := $(OBJS:.o=.d)

-include $(DEPS)

# Linking all the .o files into a single executable along with the library files
build: $(OBJS) $(COBJS)
	$(CXX) $^ $(LINKER_FLAGS) $(CXX_LIBS) -o ./bin/$(OUTPUT_NAME)

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
