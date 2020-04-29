#include <SFML/Graphics.hpp>
#include "view.h"
#include <iostream>
#include <sstream>
#include "level.h"
#include <vector>
#include <list>
#include "Entities/Entity.h"

using namespace sf;
////////////////////////////////////����� ����� ��������//////////////////////////

////////////////////////////////////////////////////����� ������////////////////////////
class Player :public Entity {
	enum { left, right, up, down, jump, stay } state;//��������� ��� ������������ - ��������� �������
	int playerScore;//��� ���������� ����� ���� ������ � ������
public:
	Player(Image& image, String Name, Level &lev, float X, float Y, int W, int H) :Entity(image, Name, X, Y, W, H) {
		playerScore = 0; state = stay; obj = lev.GetAllObjects();
		if (name == "Player1") {
			sprite.setTextureRect(IntRect(4, 19, w, h));
		}
	}
	void control() {
		if (Keyboard::isKeyPressed) {//���� ������ �������
			if ((Keyboard::isKeyPressed(Keyboard::Left) || (Keyboard::isKeyPressed(Keyboard::A)))) {
				state = left; speed = 0.2;
			}
			if ((Keyboard::isKeyPressed(Keyboard::Right) || (Keyboard::isKeyPressed(Keyboard::D)))) {
				state = right; speed = 0.2;
			}
			if ((Keyboard::isKeyPressed(Keyboard::Up) || (Keyboard::isKeyPressed(Keyboard::W)))) {//���� ������ ������� ����� � �� �� �����, �� ����� �������
				state = up; speed = 0.2;//�������� ������ ������
			}
			if ((Keyboard::isKeyPressed(Keyboard::Down) || (Keyboard::isKeyPressed(Keyboard::S)))) {
				state = down; speed = 0.2;
			}
		}
	}
	void checkCollisionWithMap(float Dx, float Dy)//� ��� �������� ������������ � ������
	{
		for (int i = 0; i < obj.size(); i++) {
			if (getRect().intersects(obj[i].rect)) {
				if (obj[i].name == "solid") {
					if (Dy > 0) { y = obj[i].rect.top - h; dy = 0; }
					if (Dy < 0) { y = obj[i].rect.top + obj[i].rect.height; dy = 0; }
					if (Dx > 0) { x = obj[i].rect.left - w; }
					if (Dx < 0) { x = obj[i].rect.left + obj[i].rect.width; }
				}
			}
		}
	}
	void update(float time)
	{
		control();//������� ���������� ����������
		switch (state)//��� �������� ��������� �������� � ����������� �� ���������
		{
		case right: dx = speed; dy = 0; break;//��������� ���� ������
		case left: dx = -speed; dy = 0; break;//��������� ���� �����
		case up: dx = 0; dy = -speed; break;//����� ��������� �������� ������ (�������� �� ��������)
		case down: dx = 0; dy = speed; break;//����� ��������� �� ����� ������ ��������� (�������� �� ��������)
		case stay: break;//� ����� ����		
		}
		x += dx * time;
		checkCollisionWithMap(dx, 0);//������������ ������������ �� �
		y += dy * time;
		checkCollisionWithMap(0, dy);//������������ ������������ �� Y
		sprite.setPosition(x + w / 2, y + h / 2); //������ ������� ������� � ����� ��� ������
		if (health <= 0) { life = false; }
		if (!isMove) { speed = 0; }
		//if (!onGround) { dy = dy + 0.0015*time; }//������� � ����� ������ ����������� � �����
		if (life) { setPlayerCoordinateForView(x, y); }
		//dy = dy + 0.0015 * time;//��������� ������������� � �����
	}
};
class Enemy :public Entity {
public:
	Enemy(Image& image, String Name, Level &lvl, float X, float Y, int W, int H) :Entity(image, Name, X, Y, W, H) {
		obj = lvl.GetObjects("solid");
		if (name == "EasyEnemy") {
			sprite.setTextureRect(IntRect(0, 0, w, h));
			dx = 0.2;//���� ��������.���� ������ ������ ���������
		}
	}
	void checkCollisionWithMap(float Dx, float Dy)//� ��� �������� ������������ � ������
	{
		for (int i = 0; i < obj.size(); i++) {
			if (getRect().intersects(obj[i].rect)) {
				if (obj[i].name == "solid") {
					if (Dy > 0) { y = obj[i].rect.top - h; dy = 0; }
					if (Dy < 0) { y = obj[i].rect.top + obj[i].rect.height; dy = 0; }
					if (Dx > 0) { x = obj[i].rect.left - w; dx = -0.1; sprite.scale(-1, 1); }
					if (Dx < 0) { x = obj[i].rect.left + obj[i].rect.width; dx = 0.1; sprite.scale(-1, 1); }
				}
			}
		}
	}
	void update(float time)
	{
		if (name == "EasyEnemy") {//��� ��������� � ����� ������ ������ ����� �����
		//moveTimer += time;if (moveTimer>3000){ dx *= -1; moveTimer = 0; }//������ ����������� �������� ������ 3 ���
			checkCollisionWithMap(dx, 0);//������������ ������������ �� �
			x += dx * time;
			sprite.setPosition(x + w / 2, y + h / 2); //������ ������� ������� � ����� ��� ������
			if (health <= 0) { life = false; }
		}
	}
};
int main()
{
	RenderWindow window(VideoMode(640, 480), "VGSGame");
	view.reset(FloatRect(0, 0, 640, 480));

	Level lvl;
	lvl.LoadFromFile("map.tmx");

	Image map_image;
	map_image.loadFromFile("map3.png");
	Texture map;
	map.loadFromImage(map_image);
	Sprite s_map;
	s_map.setTexture(map);
	Image heroImage;
	heroImage.loadFromFile("Bob.png");
	Image easyEnemyImage;
	easyEnemyImage.loadFromFile("Bob.png");
	easyEnemyImage.createMaskFromColor(Color(255, 0, 0));//������� ����� �� �����.�� ����� ���������� ����� ���������� ��������

	Object player = lvl.GetObject("player");
	Object easyEnemyObject = lvl.GetObject("Enemy"); 


	Player p(heroImage, "Player1", lvl, player.rect.left, player.rect.top, 20, 20);//������ ������ ������
	Enemy easyEnemy(easyEnemyImage, "EasyEnemy", lvl, easyEnemyObject.rect.left, easyEnemyObject.rect.top, 30, 30);

	Clock clock;
	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 800;
		Event event;
		p.update(time);// Player update function	
		easyEnemy.update(time);//easyEnemy update function
		if (Keyboard::isKeyPressed(Keyboard::Escape)) {
			window.close();
		}
		window.setView(view);
		window.clear();
		lvl.Draw(window);
		window.draw(easyEnemy.sprite);
		window.draw(p.sprite);
		window.display();
	}
	return 0;
}