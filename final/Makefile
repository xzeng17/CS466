EXE = main
TEST = test

EXE_OBJ = main.o 
OBJS = main.o

# Additional executables


# Override "default" rule provided by the Makefile template
all: $(EXE) $(EXE_BFS)

# Remove additional executables during `make clean`
CLEAN_RM = $(EXE_BFS) 

# Use the CS 225 Makefile template
include cs225/make/cs225.mk

# Assignment-specific compiler config
# Note that due to how make processes Makefiles, these flags will even apply
# to the targets inside the included Makefile template
CXXFLAGS += -Wno-delete-non-virtual-dtor

# Dependencies for additional executables
#OBJS_BFS      = $(OBJS_DIR)/testBFS.o $(OBJS_DIR)/testBFS.o

# OBJS_PROVIDED = $(OBJS_DIR)/cs225/PNG.o $(OBJS_DIR)/cs225/lodepng/lodepng.o $(OBJS_DIR)/cs225/HSLAPixel.o $(OBJS_DIR)/vector2.o $(OBJS_DIR)/line.o

$(EXE_BFS): $(OBJS_BFS)
	$(LD) $^ $(LDFLAGS) -o $@


