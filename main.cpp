
#include <SFML/Graphics/RenderWindow.hpp>
#include <Misc/Level.h>
#include <Utils/ContentManager.h>
#include <Entities/Player.h>
#include <Entities/Enemy.h>
#include "view.h" //TODO delete

using namespace sf;

int main() {
    RenderWindow window(VideoMode(640, 480), "VGSGame");
    view.reset(FloatRect(0, 0, 640, 480));

    Level lvl;
    lvl.loadFromFile("map.tmx");
    Sprite mapSprite = Sprite(*contentManagerLoadTexture("map3.png"));
    Object playerObj = lvl.getObject("player");
    std::vector<Object> enemiesObj = lvl.getObjects("EasyEnemy");

    Player player(contentManagerLoadTexture("bob.png"), "Player1", Vector2f(playerObj.rect.left, playerObj.rect.top), Vector2f(30, 30), lvl);
    std::vector<Enemy> enemies;
    for (auto &i : enemiesObj)
        enemies.emplace_back(contentManagerLoadTexture("prep,png"), "EasyEnemy", Vector2f(playerObj.rect.left, playerObj.rect.top), Vector2f(30, 30), lvl);
    Clock clock;
    while(window.isOpen()) {
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time / 800;
        Event event;
        player.update(time);// Player update function
        for(auto & e : enemies) {
            e.update(time);//easyEnemy update function
            window.draw(e.getSprite());
        }
        if (Keyboard::isKeyPressed(Keyboard::Escape)) {
            window.close();
        }
        window.setView(view);
        window.clear();
        lvl.draw(window);
        window.draw(player.getSprite());
        window.display();
    }
}



