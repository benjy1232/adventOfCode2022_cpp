SOURCEDIR = src
BUILDDIR = build
SOURCES := $(shell find $(SOURCEDIR) -maxdepth 1 -name '*.cc' -exec basename {} \;)
OBJECTS := $(addprefix $(BUILDDIR)/,$(SOURCES:%.cc=%.o))
BINARY = $(BUILDDIR)/main

all: $(BINARY)

$(BINARY): $(OBJECTS)
	$(CXX) $(CFLAGS) $(LDFLAGS) $(OBJECTS) -o $(BINARY)

$(BUILDDIR)/%.o: $(SOURCEDIR)/%.cc
	$(CXX) $(CFLAGS) $(LDFLAGS) -I. -g -c $< -o $@

clean:
	rm -rf build/*
