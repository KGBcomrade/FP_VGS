#include <SFML/Graphics/RenderWindow.hpp>
#include <Misc/Level.h>
#include <Utils/ContentManager.h>
#include <Entities/Player.h>
#include <Entities/Enemy.h>
#include <iostream>

using namespace sf;

std::string RandomKey(std::map<std::string, int> a) {
    srand(time(0));
    auto it = a.begin();
    std::advance(it, rand() % a.size());
    std::string random_key = it->first;
    return random_key;
}



int RandomQuestions(std::map<std::string, int> a) {
    int b, res = 0;
    for (int i = 0; i < 3; i++) {
        std::string key = RandomKey(a);
        std::cout << key + "\n";
        std::cin >> b;
        if (b == a[key]) {
            std::cout << "GOOD\n";
        }
        else {
            res++;
            std::cout << "BAD\n";
        }
    }
    return res;
}
int main() {
    setlocale(LC_ALL, "Russian");
    View view;
    RenderWindow window(VideoMode(640, 480), "VGSGame");

    ContentManager contentManager;
    contentManager.loadTexture("player", "Bob.png");
    contentManager.loadTexture("enemy", "prep.png");
    contentManager.loadTexture("mapTexture", "map3.png");
    contentManager.loadTexture("heart", "heart.png");
    contentManager.loadTexture("crystal", "crystal.png");

    sf::Font font;

    if(!font.loadFromFile("CyrilicOld.TTF"))
        return 1;

    std::map<std::string, int> m = {
            {"Чему равен объем тетраэдра с площадью основания 6 и высотой 4 ", 8 },
            {"cos(60)*tg(45)/(sin(30)^2", 2},
            {"Вторая производная от 6x^2+155x+288", 12},
            {"Сколькими способами можно разместить 5 космонавтов по 2 планетам, если на каждой планете могут находиться сколько угодно человек?", 32},
            {"Найдите сумму первых ста целых чисел", 5050},
            {"(1/9)^(x-13) = 9. Найдите x, если ^-возведение в степень  ", 12},
            {"Первые два часа автомобиль ехал со скоростью 50 км/ч, а следующие 2 часа со скоростью 150 км/ч. Найдите среднюю скорость автомобиля на всем пути", 100},
            {"В подъезде Влада 8 квартир, а сам он живет в 87 квартире. На каком этаже живет Влад?", 11},
            {"В прямоугольном треугольнике два катета равны 12 и 5. Чему равна гипотенуза?", 13},
            {"Найдите наибольший корень уравнения: x^2-5x+4 = 0", 4},
    };

    std::map<std::string, int> p = {
            {"Чему равно мощность, выделяющаяся на 2 последовательно соединенных резисторах с R = 5 Ом, если напряжение равна 10 В?", 1},
            {"Свет падает из воздуха под углом 30 градусов. Чему равен угол преломления в среде с показателем преломления n = 1?", 30},
            {"Во сколько раз увеличится температура тела, если его изобарически уменьшить в 25 раз?", 25},
            {"Земля притягивает к себе подброшенный мячик с силой 5 Н. С какой силой этот мяч притягивает к себе Землю?", 5},
            {"Чему равно сопротивление цепи, состоящее из 100 соединенных параллельных резисторов, сопротивление каждого из которых равно 100 Ом?", 1},
            {"Тело нагрелось 5 К, поглотив 10 кДж теплоты. Чему равна его теплоемкость в Дж/К?", 2000},
            { "Во сколько раз увеличится период математического маятника, если его массу увеличить в 4 раза?", 9 },
            { "Определить вес человека массой 70 кг в лифте, опускающемся равнозамедленно с ускорением 1 м/с^2?", 770 },
            { "Во сколько раз увеличится сила взаимодействия двух зарядов, если увеличить заряд каждого в 2 раза?", 4 },
            { "Во сколько раз изменится длина волны света при переходе из среды с показателем преломления n = 2 в вакуум?", 2 }
    };

    //map init
    Level lvl("map3.tmx");
    Sprite mapSprite = Sprite(*contentManager.getTexture("mapTexture"));
    auto *playerObj = lvl.getObject("player");
    std::vector<Object*> enemiesObj = lvl.getObjects("Enemy"), crystalObjs = lvl.getObjects("Crystal");
    Player player(contentManager.getTexture("player"), "Player1", Vector2f(playerObj->rect.left, playerObj->rect.top), Vector2f(32, 32), lvl);
    std::vector<Enemy> enemies;
    enemies.reserve(enemiesObj.size());
    for (auto & i : enemiesObj)
        enemies.emplace_back(contentManager.getTexture("enemy"), "EasyEnemy", Vector2f(i->rect.left, i->rect.top), Vector2f(32, 32), lvl, &player, i->type);

    std::vector<Entity*> crystals;
    crystals.reserve(crystalObjs.size());

    for(auto & i : crystalObjs)
        crystals.emplace_back(new Entity(contentManager.getTexture("crystal"), "Crystal", Vector2f(i->rect.left, i->rect.top), Vector2f(20, 32), lvl));
    int maxScore = crystals.size();


    Clock clock;


    //interface elements
    sf::Sprite crystalSprite(*contentManager.getTexture("crystal"));
    crystalSprite.scale(1.3, 1.3);

    sf::Text scoreDisplay;
    scoreDisplay.setFont(font);
    scoreDisplay.setCharacterSize(26);
    scoreDisplay.setStyle(sf::Text::Regular);
    scoreDisplay.setOutlineColor(sf::Color::Black);
    scoreDisplay.setOutlineThickness(.8);
    scoreDisplay.setFillColor(sf::Color::White);


    while(window.isOpen()) {
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time / 800;
        Event event{};
        while(window.pollEvent(event)) {
            if(event.type == Event::Closed)
                window.close();
        }

        if(!player.isAlive()) {
            window.close();
            std::cout << "You lose!" << std::endl;
            break;
        }

        if(player.getScore() == maxScore) {
            window.close();
            std::cout << "You won!" << std::endl;
            break;
        }

        player.update(time);// Player update function
        bool updatePaths = lvl.grid.setPlayerPosition(player.getPosition());
        for(auto &e : enemies) {
            if(e.isChecked())
                continue;
            if(updatePaths && e.isTriggered())
                e.setNodeStack(lvl.grid.findPath(e.getCurrentGoal()));
            e.update(time);//easyEnemy update function
            if(player.getRect().intersects(e.getRect())) {
                player.damage(RandomQuestions(e.getType() == "m" ? m : p));
                e.setChecked();
                clock.restart();
            }
        }

        view.setCenter(player.getPosition());
        view.setSize((Vector2f) window.getSize());
//        view.zoom(.5);
        window.setView(view);
        window.clear();
        lvl.draw(window);
        window.draw(*player.getSprite());
        for(auto & e : enemies) {
            window.draw(*e.getSprite());
        }

        for(auto c = crystals.begin(); c < crystals.end(); c++) {
            window.draw(*(*c)->getSprite());

            if(player.getRect().intersects((*c)->getRect())) {
                delete *c;
                crystals.erase(c);
                player.incrementScore();
            }
        }


        crystalSprite.setPosition(view.getCenter() - (Vector2f)(window.getSize() / 2u) + Vector2f(20, 60));
        window.draw(crystalSprite);

        scoreDisplay.setString(std::to_string(player.getScore()) + "/" + std::to_string(maxScore));
        scoreDisplay.setPosition(view.getCenter() - (Vector2f) (window.getSize() / 2u) + Vector2f(50, 60));
        window.draw(scoreDisplay);


        for(int i = 0; i < player.getHealth(); i++) {
            Sprite heartSprite(*contentManager.getTexture("heart"));
            heartSprite.setPosition(view.getCenter() - (Vector2f) (window.getSize() / 2u) + Vector2f(20 + i * 35, 20));
            window.draw(heartSprite);
        }

        window.display();
    }

    return 0;
}




