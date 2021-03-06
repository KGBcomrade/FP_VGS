//
// Created by kgbcomrade on 5/7/20.
//

#include "Grid.h"
#include <cmath>
#include <Utils/Utils.h>
#include <climits>

Grid::Grid(size_t width, size_t height, sf::Vector2i tileSize) {
    mapWidth = width;
    mapHeight = height;
    grid = std::vector<std::vector<bool>>(width, std::vector<bool>(height, false));
    this->tileSize = tileSize;
}

void Grid::setObstacle(size_t x, size_t y) {
    grid[x][y] = true;
}

bool Grid::setPlayerPosition(sf::Vector2f position) {
    auto newPlayerPosition = sf::Vector2i(position.x / tileSize.x, position.y / tileSize.y);
    if(newPlayerPosition == playerPosition)
        return false;
    playerPosition = newPlayerPosition;
    return true;
}

std::stack<sf::Vector2f> Grid::findPath(sf::Vector2f position) {
    std::vector<std::vector<Node*>> nodes(mapWidth, std::vector<Node*>(mapHeight));
    for(size_t x = 0; x < mapWidth; x++)
        for(size_t y = 0; y < mapHeight; y++) {
            nodes[x][y] = new Node(sf::Vector2i(x, y), vectorLen(playerPosition - sf::Vector2i(x, y)), grid[x][y]);
        }

    Node* start = nodes[position.x / tileSize.x][position.y / tileSize.y];
    std::vector<Node*> toCheck(1, start);
    start->optimize(nullptr);
    while(!toCheck.empty()) {
        Node* current = toCheck[0];

        for(auto &i : toCheck)
            if(i->getFScore() < current->getFScore())
                current = i;

         for(auto i = toCheck.begin(); i < toCheck.end(); i++)
             if(*i == current)
                 toCheck.erase(i);


        if(current->getCoordinates() == playerPosition)
            break;
        int x = current->getCoordinates().x, y = current->getCoordinates().y;
        if(x > 0)
            if(!nodes[x - 1][y]->checked && !nodes[x - 1][y]->isObstacle()){
                nodes[x - 1][y]->optimize(current);
                toCheck.push_back(nodes[x - 1][y]);
            }
        if(x < mapWidth - 1)
            if(!nodes[x + 1][y]->checked && !nodes[x + 1][y]->isObstacle()){
                nodes[x + 1][y]->optimize(current);
                toCheck.push_back(nodes[x + 1][y]);
            }
        if(y < mapHeight - 1)
            if(!nodes[x][y + 1]->checked && !nodes[x][y + 1]->isObstacle()){
                nodes[x][y + 1]->optimize(current);
                toCheck.push_back(nodes[x][y + 1]);
            }
        if(y > 0)
            if(!nodes[x][y - 1]->checked && !nodes[x][y - 1]->isObstacle()){
                nodes[x][y - 1]->optimize(current);
                toCheck.push_back(nodes[x][y - 1]);
            }
        current->checked = true;


    }
    if(nodes[playerPosition.x][playerPosition.y]->getFScore() == INT_MAX)
        return std::stack<sf::Vector2f>();
    else {
        std::stack<sf::Vector2f> res;
        Node* node = nodes[playerPosition.x][playerPosition.y];
        while(node != nullptr) {
            res.push(sf::Vector2f(node->getCoordinates().x * tileSize.x, node->getCoordinates().y * tileSize.y));
            node = node->getPrev();
        }
        for(auto &i : nodes)
            for(auto &j : i)
                delete j;
        return res;
    }

}

Grid::Grid() : Grid::Grid(0, 0, sf::Vector2i(0, 0)) {

}

Grid::Node::Node(sf::Vector2i coordinates, float hScore, bool obstacle) {
    this->coordinates = coordinates;
    this->hScore = hScore;
    this->obstacle = obstacle;
    this->gScore = INT_MAX;
    this->prev = nullptr;
    this->checked = false;
}

void Grid::Node::optimize(Grid::Node *prevCandidate) {
    if(prevCandidate == nullptr) {
        gScore = 0;
        return;
    }
    float newGScore = prevCandidate->gScore + vectorLen<int>(coordinates - prevCandidate->coordinates);
    if (newGScore < gScore) {
        gScore = newGScore;
        this->prev = prevCandidate;
    }

}

float Grid::Node::getFScore() {
    return gScore + hScore;
}

Grid::Node *Grid::Node::getPrev() {
    return prev;
}

sf::Vector2i Grid::Node::getCoordinates() {
    return coordinates;
}

bool Grid::Node::isObstacle() {
    return obstacle;
}

