CC=gcc

GAME = Tomogashi_Island

# Repertoires SDL (a initialiser avec un $path= sur de la SDL)
SDL_DIR=${HOME}/SDL2
SDLLIB_DIR=${SDL_DIR}/lib
SDLINC_DIR=${SDL_DIR}/include

# Repertoires du programme
BINDIR = bin
SRCDIR = src
OBJDIR = obj
INCDIR = include
TESTDIR = test

LIBS=-L${SDLLIB_DIR} -lSDL2 -lSDL2_ttf -lSDL2_image -lSDL2_mixer
INCLUDES=-I${SDLINC_DIR} -I${INCDIR}

PROG=${BINDIR}/${GAME}

# Liste de tous les fichiers source
SRCS := $(wildcard ${SRCDIR}/*.c)

# Générer la liste des fichiers objets en remplaçant le chemin de src par obj
OBJS := $(patsubst ${SRCDIR}/%.c, ${OBJDIR}/%.o, ${SRCS})

${PROG}: ${OBJS}
	${CC} $^ -g -o $@ ${LIBS} ${INCLUDES}

${OBJDIR}/%.o: ${SRCDIR}/%.c
	${CC} -c $< -o $@ ${INCLUDES} 

.PHONY: clean
clean: 
	rm -f ${PROG}
	rm -f ${OBJDIR}/*.o
