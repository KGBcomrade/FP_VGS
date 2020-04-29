#include <iostream> 
#include <SFML/Graphics.hpp>
#include "map.h"
#include "view.h"
#include <sstream>
#include <algorithm>
#include <vector>
#include <string>

using namespace sf;
using namespace std;

vector<string> math_q1 = { "aaa", "bbb", "ccc", "ddd", "eee" };

class Player { 
private:
	float x, y = 0;
public:
	float dx, dy, speed; //���������� ������ � � �
	int dir, health, w, h, score;
	bool life;
	String File;
	Image image;
	Texture texture;
	Sprite sprite;

	Player(String F, float X, float Y, int W, int H) {
		dir = 0; speed = 0; health = 100, score = 0;
		life = true;
		File = F;//��� �����
		image.loadFromFile(File);
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		x = X; y = Y, h = H, w = W;//���������� ��������� �������
		
	}

	void Random(vector<string> m) {
		srand(time(0));
		random_shuffle(m.begin(), m.end());
		for (int i = 0; i < 4; i++) {
			cout << m[i] << endl;
		}
	}

	void update(float time) {
		switch (dir)
		{
		case 0: dx = speed; dy = 0;   break;
		case 1: dx = -speed; dy = 0;   break;
		case 2: dx = 0; dy = speed;   break;
		case 3: dx = 0; dy = -speed;   break;
		}

		x += dx * time;
		y += dy * time;

		speed = 0;
		sprite.setPosition(x, y); 
		interactionWithMap();
		if (health <= 0) {
			life = false;
		}
	}

	float GetCoX() {
		return x;
	}
	float GetCoY() {
		return y;
	}

	void interactionWithMap()//�-��� �������������� � ������
	{

		for (int i = y / 32; i < (y + h) / 32; i++)//���������� �� ��������, �������������� � �������, �� ���� �� ���� ����������� ������� 32*32, ������� �� ���������� � 9 �����. ��� ������� ������� ����.
			for (int j = x / 32; j < (x + w) / 32; j++)//��� ����� �� 32, ��� ����� �������� ����� ���������, � ������� �������� �������������. (�� ���� ������ ������� 32*32, ������� ����� ������������ ������ �� ���������� ���������). � j<(x + w) / 32 - ������� ����������� ��������� �� ����. �� ���� ���������� ������ ������� ��������, ������� ������������� � ����������. ����� ������� ���� � ����� ����� ������� �� ����, ������� �� �� ������ �������� (���������������� � ������), �� ������� �������� (���������������� � ������)
			{
				if (TileMap[i][j] == '0')//���� ��� ��������� ������������� ������� 0 (�����), �� ��������� "����������� ��������" ���������:
				{
					if (dy > 0)//���� �� ��� ����,
					{
						y = i * 32 - h;//�� �������� ���������� ����� ���������. ������� �������� ���������� ������ ���������� �� �����(�����) � ����� �������� �� ������ ������� ���������.
					}
					if (dy < 0)
					{
						y = i * 32 + 32;//���������� � ������� �����. dy<0, ������ �� ���� ����� (���������� ���������� ������)
					}
					if (dx > 0)
					{
						x = j * 32 - w;//���� ���� ������, �� ���������� � ����� ����� (������ 0) ����� ������ ���������
					}
					if (dx < 0)
					{
						x = j * 32 + 32;//���������� ���� �����
					}
				}

				if (TileMap[i][j] == 's') { 
					Random(math_q1);
					TileMap[i][j] = ' ';
				}

				if (TileMap[i][j] == 'f') {
					health -= 40;
					TileMap[i][j] = ' ';
				}

				if (TileMap[i][j] == 'h') {
					health += 20;
					TileMap[i][j] = ' ';
				}
			}
	}

};


int main() {
	RenderWindow window(sf::VideoMode(640, 480), "VGSGame");
	view.reset(sf::FloatRect(0, 0, 640, 480));

	Font font;
	font.loadFromFile("CyrilicOld.ttf");
	Text text("", font, 20);
	text.setFillColor(Color::Red);
	text.setStyle(Text::Bold);

	Image map_image;//������ ����������� ��� �����
	map_image.loadFromFile("map.png");//��������� ���� ��� �����
	Texture map;//�������� �����
	map.loadFromImage(map_image);//�������� �������� ���������
	Sprite s_map;//������ ������ ��� �����
	s_map.setTexture(map);//�������� �������� ��������


	Clock clock;

	Player student_1("Bob.png", 250, 250, 10, 10);

	while (window.isOpen()) {

		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 800;

		sf::Event event;
		
		if (Keyboard::isKeyPressed(Keyboard::Escape)) {
			window.close();
		}

		if (student_1.life) {
			if ((Keyboard::isKeyPressed(Keyboard::Left) || (Keyboard::isKeyPressed(Keyboard::A)))) {
				student_1.dir = 1; student_1.speed = 0.1;
			}

			if ((Keyboard::isKeyPressed(Keyboard::Right) || (Keyboard::isKeyPressed(Keyboard::D)))) {
				student_1.dir = 0; student_1.speed = 0.1;
			}

			if ((Keyboard::isKeyPressed(Keyboard::Up) || (Keyboard::isKeyPressed(Keyboard::W)))) {
				student_1.dir = 3; student_1.speed = 0.1;
			}

			if ((Keyboard::isKeyPressed(Keyboard::Down) || (Keyboard::isKeyPressed(Keyboard::S)))) {
				student_1.dir = 2; student_1.speed = 0.1;
			}
		}

		setPlayerCoordinateForView(student_1.GetCoX(), student_1.GetCoY());
		student_1.update(time);

		window.setView(view);
		window.clear();

		/////////////////////////////������ �����/////////////////////
		for (int i = 0; i < HEIGHT_MAP; i++)
			for (int j = 0; j < WIDTH_MAP; j++)
			{
				if (TileMap[i][j] == ' ')  s_map.setTextureRect(IntRect(0, 0, 32, 32)); 
				if (TileMap[i][j] == 's')  s_map.setTextureRect(IntRect(32, 0, 32, 32));
				if ((TileMap[i][j] == '0')) s_map.setTextureRect(IntRect(64, 0, 32, 32));
				if ((TileMap[i][j] == 'f')) s_map.setTextureRect(IntRect(96, 0, 32, 32));
				if ((TileMap[i][j] == 'h')) s_map.setTextureRect(IntRect(128, 0, 32, 32));


				s_map.setPosition(j * 32, i * 32);//�� ���� ����������� ����������, ��������� � �����. �� ���� ������ ������� �� ��� �������. ���� ������, �� ��� ����� ���������� � ����� �������� 32*32 � �� ������ ���� �������

				window.draw(s_map);//������ ���������� �� �����
			}

		std::ostringstream numScore;
		numScore << student_1.score;
		text.setString("������� ������: " + numScore.str());
		text.setPosition(view.getCenter().x - 165, view.getCenter().y - 200);

		window.draw(student_1.sprite);
		window.draw(text);
		window.display();
	}

	return 0;
}



