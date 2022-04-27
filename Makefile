# compiler

#EXE 	:= main
#INCL    := $(wildcard include/*.h) $(incG3X)
#SRC     := src/main.c $(subst include/,,$(INCL:%.h=src/%.c))
#OBJ     := $(subst src/,,$(SRC:%.c=bin/%.o))
#
#CC 		:= clang
#CFLAGS 	:= -O2 -std=c17
#LIB 	:= $(libG3X) $(DBG_LIB)
#LDFLAGS := -o $(EXE) $(LIB)
#
#$(EXE): $(OBJ)
#	$(CC) $(LDFLAGS) $(OBJ)
#
#bin/%.o : src/%.c include/%.h
#	@$(CC) -c $(CFLAGS) src/$*.c include/$*.h $(INC)
#	@mv $*.o bin/$*.o
#
#bin/main.o: src/main.c
#	$(CC) -c ($CFLAGS) src/main.c
#	@mv main.o bin/main.o
#
#
## informations sur les paramètres de compilation
#? :
#	@echo "---------compilation informations----------"
#	@echo "  processor      : $(PROCBIT)"
#	@echo "  compiler       : $(CC)"
#	@echo "  options        : $(CFLAGS)"
#	@echo "  lib g3Ox/OpenGl : $(libG3X)$(COMP)"
#	@echo "  headers        : $(incG3X)"
#clean :
#	@rm -f *.o $(EXE)



# -------------------------------------------------------------------------

## compiler
#CC = clang
#
#DEBUG = no
#
#ifeq ($(DEBUG),yes)
#  CFLAGS  = -g -Wpointer-arith -Wall -std=c17
#else
#  CFLAGS  = -O2 -std=c17
#endif
#
#lib = $(libG3X) $(DBG_LIB)
#inc = -I./include $(incG3X)
#src = src/
#
## cible pour les binaires (.a,.so)
#bin = .
#
## règle générique de création de xxx.o à partir de src/xxx.c
#%.o : $(src)%.c
#	@echo "module $@"
#	@$(CC) $(CFLAGS) $(inc) -c $< -o $@
#	@echo "------------------------"
#
## règle générique de création de l'executable xxx à partir de src/xxx.c (1 seul module)
#% : %.o
#	@echo "assemblage [$^]->$@"
#	@$(CC) $^ $(lib) -o $@
#	@echo "------------------------"
#
#.PHONY : clean cleanall ?
#
## informations sur les paramètres de compilation
#? :
#	@echo "---------compilation informations----------"
#	@echo "  processor      : $(PROCBIT)"
#	@echo "  compiler       : $(CC)"
#	@echo "  options        : $(CFLAGS)"
#	@echo "  lib g3Ox/OpenGl : $(libG3X)$(COMP)"
#	@echo "  headers        : $(incG3X)"
#clean :
#	@rm -f *.o main



# -------------------------------------------------------------------------

INCL    := $(wildcard include/*.h)
SRC     := src/main.c $(subst include/,,$(INCL:%.h=src/%.c))
OBJ     := $(subst src/,,$(SRC:%.c=bin/%.o))
LIBS    := $(libG3X) $(DBG_LIB)
EXE     := main

CC      := clang
CFLAGS  := -O2 -std=c17
LIBPATH := -L.
LDFLAGS := -o $(EXE) $(LIBPATH) $(LIBS)
RM      := rm -f

all: $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS)

bin/%.o: src/%.c include/%.h
	$(CC) -c $(CFLAGS) src/$*.c include/$*.h $(incG3X)
	@mv $*.o bin/$*.o

bin/main.o: src/main.c
	$(CC) -c $(CFLAGS) src/main.c $(incG3X)
	@mv main.o bin/main.o

$(OBJ): $(INCL)

clean:
	$(RM) $(OBJ) $(INCL:.h=.h.gch)

# -------------------------------------------------------------------------




















## $(BIN) est le nom du binaire généré
#BIN = main
## SRC
#SRC = src/
## INCLUDES
#INC = include/
## FLAG
#FLAGS = -Wall -O3
## INCLUDES
#LIBS = -lsfml-system -lsfml-graphics -lsfml-window -lGL -lGLU -lm
## INCLUDES
#LIBDIR =
## Compilateur
#GCC = clang
#
## $(OBJECTS) sont les objets qui seront générés après la compilation
#OBJECTS = main.o cube.o cylinder.o sphere.o torus.o
#
#default: $(BIN)
#
#all: $(OBJECT)
#
#$(BIN): $(OBJECTS)
#	@echo "**** PHASE DE LIEN ****"
#	$(GCC) $(OBJECTS) $(FLAGS) -o $(BIN) $(LIBDIR) $(LIBS)
#
#main.o: $(SRC)main.c $(INC)main.h
#	@echo "**** $@ ****"
#	$(GCC) -I./$(INC) $(FLAGS) -c $< -o $@
#
#cube.o: $(SRC)cube.c $(INC)cube.h
#	@echo "**** $@ ****"
#	$(GCC) -I./$(INC) $(FLAGS) -c $< -o $@
#
#cylinder.o: $(SRC)cylinder.c $(INC)cylinder.h
#	@echo "**** $@ ****"
#	$(GCC) -I./$(INC) $(FLAGS) -c $< -o $@
#
#sphere.o: $(SRC)sphere.c $(INC)sphere.h
#	@echo "**** $@ ****"
#	$(GCC) -I./$(INC) $(FLAGS) -c $< -o $@
#
#torus.o: $(SRC)torus.c $(INC)torus.h
#	@echo "**** $@ ****"
#	$(GCC) -I./$(INC) $(FLAGS) -c $< -o $@
#
#clean:
#	rm -f *.o $(BIN)
#	find . -name "*~" -exec rm {} \;

