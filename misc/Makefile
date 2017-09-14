CXX       := g++
ROOTCLING := rootcling
RM        := rm

CXXFLAGS := -pipe -m64 -Wshadow -Wall -W -Woverloaded-virtual -fsigned-char -fPIC -pthread -std=c++11 -O2 -ggdb3 -Og -DDEBUG

LIBNAME := HDFS
LIB     := $(CMSSW_BASE)/lib/$(SCRAM_ARCH)/lib$(LIBNAME).so
RMF     := $(basename $(LIB)).rootmap
PCM     := $(basename $(LIB))_rdict.pcm

MAKEFILE_DIR := $(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))
ROOT_INCLUDE := $(ROOTSYS)include
ROOT_LIB     := $(ROOTSYS)lib

INPUT          := THDFSFile
HEADERS        := $(MAKEFILE_DIR)/$(INPUT).h $(MAKEFILE_DIR)/LinkDef.h
SRCFILE        := $(MAKEFILE_DIR)/$(INPUT).cxx
SRCFILE_OBJECT := $(patsubst %.cxx,%.o,$(SRCFILE))

RFLX        := $(MAKEFILE_DIR)/G__$(LIBNAME).cxx
RFLX_OBJECT := $(patsubst %.cxx,%.o,$(RFLX))

all: $(LIB)

$(RFLX) $(RMF) $(PCM): $(HEADERS)
	@echo "Generating reflex source, dictionary and rootmap files"
	@$(ROOTCLING) -rootbuild -f $(RFLX) -s $(LIB) -rml $(notdir $(LIB)) -rmf $(RMF) -I$(ROOT_INCLUDE) -I/usr/include -I$(MAKEFILE_DIR) $^

$(SRCFILE_OBJECT): $(SRCFILE)
	@echo "Building source object"
	@$(CXX) -I$(ROOT_INCLUDE) -I$(MAKEFILE_DIR) $(CXXFLAGS) -o $@ -c $<

$(RFLX_OBJECT): $(RFLX)
	@echo "Building reflex object"
	@$(CXX) -I$(ROOT_INCLUDE) $(CXXFLAGS) -o $@ -c $<

$(LIB): $(RFLX_OBJECT) $(SRCFILE_OBJECT)
	@echo "Building the library"
	@$(CXX) $(CXXFLAGS) -Wl,--no-undefined -shared -Wl,-soname,$(notdir $(LIB)) -o $@ $^ -Wl,-rpath,$(dir $(LIB)): -L/usr/lib64 -lhdfs -L$(ROOT_LIB) -lNet -lRIO -lThread -lCore

.PHONY: clean

clean:
	@echo "Removing files"
	@$(RM) -f $(SRCFILE_OBJECT) $(RFLX_OBJECT) $(RFLX) $(PCM) $(RMF) $(LIB)
