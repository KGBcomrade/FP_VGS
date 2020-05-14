//
// Created by kgbcomrade on 5/7/20.
//

#ifndef FP2_GRID_H
#define FP2_GRID_H


#include <vector>
#include <SFML/System/Vector2.hpp>
#include <stack>
class Grid {
private:
    size_t mapWidth, mapHeight;
    std::vector<std::vector<bool>> grid;
    ///Player's position in grid
    sf::Vector2i playerPosition, tileSize;

    class Node {
    private:
        sf::Vector2i coordinates;
        float gScore, hScore;
        Node* prev;
        bool obstacle;
    public:

        bool checked;
        Node(sf::Vector2i coordinates, float hScore, bool obstacle);
        void optimize(Node* prevCandidate);
        float getFScore();
        Node* getPrev();
        sf::Vector2i getCoordinates();
        bool isObstacle();
    };


public:
    Grid();
    Grid(size_t width, size_t height, sf::Vector2i tileSize);
    void setObstacle(size_t x, size_t y);
    /***
     * Update player's position in the grid
     * @param position player's position in the world (not in the grid)
     * @return true if position is different from previous one
     */
    bool setPlayerPosition(sf::Vector2f position);
    /**
     * Finds shortest way to player from start position
     * @param position start position
     * @return stack of waypoints which lead to player's position
     */
    std::stack<sf::Vector2f> findPath(sf::Vector2f position);
};


#endif //FP2_GRID_H
