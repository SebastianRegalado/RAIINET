CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD -Werror=vla -g
EXEC = RAIInet
OBJECTS = cell.o abilities.o controller.o grid.o link.o model.o myLink.o enemyLink.o player.o view.o window.o main.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
