# COLORS
RED     := 1
GREEN   := 2
YELLOW  := 3
BLUE    := 4
MAGENTA := 5
CYAN    := 6
WHITE   := 7
# définition des cibles particulières
.PHONY: clean, mrproper
# désactivation des règles implicites
.SUFFIXES:
# définition des variables
CXX = gcc
EXEC = 
DEBUG =
CXXFLAGS = -g
#SOURCES OBJECTS
SRCDIR = src
OBJDIR = bin
TARGETDIR = target
#LIBS 
LIBS = -Wl,-rpath=./lib  
#INCLUDES
INCLUDES = -L./lib -I./include 
   

#REGLES
SOURCES := $(wildcard $(SRCDIR)/*.cpp) $(wildcard $(SRCDIR)/*/*.cpp) 
HEADER := $(wildcard $(SRCDIR)/*.hpp) $(wildcard $(SRCDIR)/*/*.hpp) 
OBJECTS := $(SOURCES:.cpp=.o) 

all:$(EXEC)	

$(OBJECTS):%.o:%.c %.h
	@$(CXX) -c $(CXXFLAGS)  $<  -o $@  $(LIBS)  $(INCLUDES) 
	@tput setaf $(CYAN) 
	@echo "---> Compilation.. "$<" reussie!"
	@tput sgr0
# all conditionnel
$(EXEC): $(OBJECTS)
	@$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS)) $(INCLUDES) 
	@tput setaf $(GREEN) 
	@echo "=====Linkage complet!===== : |"$<"|"
	@tput sgr0
%.hpp:
	@touch


run:
	./$(EXEC)
  
# suppression de tous les fichiers, sauf les sources,
# en vue d'une reconstruction complète
mrproper: clean
	rm -rf $(EXEC)
