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
EXEC_CLIENT = chatroom
EXEC_SERVEUR = chatserv
DEBUG =
CXXFLAGS = -g 
#SOURCES OBJECTS
SRCDIR = src
SRCDIR_CLIENT = client
SRCDIR_SERVEUR = serveur
OBJDIR = bin
TARGETDIR = target
#LIBS 
LIBS = -Wl,-rpath=./lib   -lncurses -lpanel -lmenu -lform
#INCLUDES
INCLUDES = -L./lib -I./include 
   

#REGLES
SOURCES_CLIENT := $(wildcard $(SRCDIR)/$(SRCDIR_CLIENT)/*.c) $(wildcard $(SRCDIR)/$(SRCDIR_CLIENT)/*/*.c) 
SOURCES_SERVEUR := $(wildcard $(SRCDIR)/$(SRCDIR_SERVEUR)/*.c) $(wildcard $(SRCDIR)/$(SRCDIR_SERVEUR)/*/*.c) 
HEADER := $(wildcard $(SRCDIR)/*.h) $(wildcard $(SRCDIR)/*/*.h) 
OBJECTS_CLIENT := $(SOURCES_CLIENT:.c=.o)
OBJECTS_SERVEUR := $(SOURCES_SERVEUR:.c=.o)

all:$(EXEC_CLIENT) $(EXEC_SERVEUR)	

$(OBJECTS_CLIENT):%.o:%.c %.h
	@$(CXX) -c $(CXXFLAGS)  $<  -o $@  $(LIBS)  $(INCLUDES) 
	@tput setaf $(CYAN) 
	@echo "---> Compilation.. "$<" reussie!"
	@tput sgr0
$(OBJECTS_SERVEUR):%.o:%.c %.h
	@$(CXX) -c $(CXXFLAGS)  $<  -o $@  $(LIBS)  $(INCLUDES) 
	@tput setaf $(CYAN) 
	@echo "---> Compilation.. "$<" reussie!"
	@tput sgr0

# all conditionnel
$(EXEC_CLIENT): $(OBJECTS_CLIENT)
	@$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS) $(INCLUDES) 
	@tput setaf $(GREEN) 
	@echo "=====Linkage CLIENT complet!===== : |"$<"|"
	@tput sgr0

$(EXEC_SERVEUR): $(OBJECTS_SERVEUR)
	@$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS) $(INCLUDES) 
	@tput setaf $(GREEN) 
	@echo "=====Linkage SERVEUR complet!===== : |"$<"|"
	@tput sgr0

%.h:
	@touch $@


run_client:
	./$(EXEC_CLIENT)


run_serveur:
	./$(EXEC_SERVEUR)

  # clean suppression des fichiers temporaires
clean:
	-rm $(EXEC_CLIENT) $(EXEC_SERVEUR)
	-find ./src -name *.o -print0 | xargs -0 rm -rf  
	-find ./src -name *.bak -print0 | xargs -0 rm -rf
# suppression de tous les fichiers, sauf les sources,
# en vue d'une reconstruction complète
mrproper: clean
	rm -rf $(EXEC)
