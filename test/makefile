CC=gcc

GAME = Tomogashi_Island

# Repertoires SDL (a initialiser avec un $path= sur de la SDL)
SDL_DIR=${HOME}/SDL2
SDLLIB_DIR=${SDL_DIR}/lib
SDLINC_DIR=${SDL_DIR}/include

# Repertoires du programme
BINDIR = ../bin
SRCDIR = ../src
OBJDIR = ../obj
INCDIR = ../include
TESTDIR = ../test/src
TESTOBJDIR = ../test/obj

LIBS=-L${SDLLIB_DIR} -lSDL2 -lSDL2_ttf -lSDL2_image -LSDL2_mixer -lcunit
INCLUDES=-I${SDLINC_DIR} -I${INCDIR}

OBJS := $(filter-out main.o, $(SRCS:.c=.o))
 
all: test_outWindow test_outMap test_LoadSave 


${OBJDIR}/%.o: ${SRCDIR}/%.c
	${CC} -c $< -o $@ ${INCLUDES} 


# Construction des objets des scriptes des tests
${TESTOBJDIR}/test_LoadSave.o: ${TESTDIR}/test_LoadSave.c
	${CC} -c $< -o $@ ${INCLUDES} 

${TESTOBJDIR}/test_outWindow.o: ${TESTDIR}/test_outWindow.c
	${CC} -c $< -o $@ ${INCLUDES} 

${TESTOBJDIR}/test_outMap.o: ${TESTDIR}/test_outMap.c
	${CC} -c $< -o $@ ${INCLUDES} 



# Construction des executables des tests
test_LoadSave: ${OBJS} ${TESTOBJDIR}/test_LoadSave.o
	${CC} $^ -o $@ ${LIBS} ${INCLUDES}

test_outWindow: ${OBJS} ${TESTOBJDIR}/test_outWindow.o
	${CC} $^ -o $@ ${LIBS} ${INCLUDES}

test_outMap: ${OBJS} ${TESTOBJDIR}/test_outMap.o
	${CC} $^ -o $@ ${LIBS} ${INCLUDES}

