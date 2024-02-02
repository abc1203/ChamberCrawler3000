CXX = g++
CXXFLAGS = -std=c++14 -g -Wall -Werror=vla -MMD
OBJECTS = ./GameObject/compass.o ./GameObject/Potion/PH.o ./GameObject/Potion/BD.o ./GameObject/Potion/WD.o ./GameObject/Potion/WA.o ./GameObject/Potion/BA.o ./GameObject/Potion/RH.o ./GameObject/character.o ./GameObject/barriersuit.o ./GameObject/MapComponent/door.o ./GameObject/MapComponent/passage.o ./GameObject/MapComponent/stairs.o ./GameObject/MapComponent/vwall.o ./GameObject/MapComponent/hwall.o ./GameObject/MapComponent/tile.o ./GameObject/treasure.o ./GameObject/mapcomponent.o ./GameObject/Character/Enemy/phoenix.o ./GameObject/Character/Enemy/werewolf.o ./GameObject/Character/Enemy/dragon.o ./GameObject/Character/Enemy/troll.o ./GameObject/Character/Enemy/merchant.o ./GameObject/Character/Enemy/vampire.o ./GameObject/Character/Enemy/goblin.o ./GameObject/Character/playerrace.o ./GameObject/Character/PlayerRace/human.o ./GameObject/Character/PlayerRace/dwarf.o ./GameObject/Character/PlayerRace/orc.o ./GameObject/Character/PlayerRace/elves.o ./GameObject/Character/enemy.o ./GameObject/potion.o ./game.o ./gameobject.o ./main.o ./floor.o ./textdisplay/textdisplay.o ./subject.o ./enum.o ./GameObject/Character/PlayerRace/god.o

DEPENDS = ${OBJECTS:.o=.d}
EXEC = cc3k

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

clean :
	rm ${DEPENDS} ${OBJECTS} ${EXEC}

-include ${DEPENDS} # reads the .d files and reruns dependencies