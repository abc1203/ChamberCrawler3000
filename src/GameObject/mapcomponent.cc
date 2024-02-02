#include "mapcomponent.h"

MapComponent::MapComponent(int row, int col, ObjectType type): GameObject{row,col,type} {
    if(type == ObjectType::HWall) { playerAccess = 0; enemyAccess = 0; }
    else if(type == ObjectType::VWall) { playerAccess = 0; enemyAccess = 0; }
    else if(type == ObjectType::Door) { playerAccess = 1; enemyAccess = 0; }
    else if(type == ObjectType::Passage) { playerAccess = 1; enemyAccess = 0; }
    else if(type == ObjectType::Tile) { playerAccess = 1; enemyAccess = 1; }
    else if(type == ObjectType::Stairs) { playerAccess = 1; enemyAccess = 0; }
    else std::cerr << "incorrect mapcomponent " << row << " " << col << " " << type << std::endl;
}

MapComponent::~MapComponent(){}

void MapComponent::notify(Subject &whoFrom) {
    setRow(whoFrom.getRow());
    setCol(whoFrom.getCol());
}

