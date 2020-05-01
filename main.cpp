
#include <SFML/Graphics/RenderWindow.hpp>
#include <Misc/Level.h>
#include <Utils/ContentManager.h>
#include <Entities/Player.h>
#include <Entities/Enemy.h>
#include <iostream>

using namespace sf;

int main() {
    View view;
    RenderWindow window(VideoMode(640, 480), "VGSGame");
    view.reset(FloatRect(0, 0, 640, 480));

    ContentManager contentManager;
    contentManager.loadTexture("player", "Bob.png");
    contentManager.loadTexture("enemy", "prep.png");
    contentManager.loadTexture("mapTexture", "map3.png");

    Level lvl;
    lvl.loadFromFile("map3.tmx");
    Sprite mapSprite = Sprite(*contentManager.getTexture("mapTexture"));
    auto *playerObj = lvl.getObject("player");
    std::vector<Object*> enemiesObj = lvl.getObjects("Enemy");
    Player player(contentManager.getTexture("player"), "Player1", Vector2f(playerObj->rect.left, playerObj->rect.top), Vector2f(30, 30), lvl);
    std::vector<Enemy> enemies;
    enemies.reserve(enemiesObj.size());
    for (auto & i : enemiesObj)
        enemies.emplace_back(contentManager.getTexture("enemy"), "EasyEnemy", Vector2f(i->rect.left, i->rect.top), Vector2f(30, 30), lvl);
    Clock clock;

    while(window.isOpen()) {
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time / 800;
        Event event{};
        while(window.pollEvent(event)) {
            if(event.type == Event::Closed)
                window.close();
        }
        player.update(time);// Player update function
        for(auto &e : enemies)
            e.update(time);//easyEnemy update function
        if (Keyboard::isKeyPressed(Keyboard::Escape)) {
            window.close();
        }
        view.setCenter(player.getSprite()->getPosition());
        window.setView(view);
        window.clear();
        lvl.draw(window);
        window.draw(*player.getSprite());
        for(auto & e : enemies) {
            window.draw(*e.getSprite());
        }
        window.display();
    }
}



