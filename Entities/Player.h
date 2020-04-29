//
// Created by kgbcomrade on 4/29/20.
//

#ifndef FP2_PLAYER_H
#define FP2_PLAYER_H


#include "Entity.h"

class Player : public Entity {
private:
    enum { left, right, up, down, jump, stay } state;//��������� ��� ������������ - ��������� �������
    int playerScore;
public:
    void control();
    void update(float dt) override;
};


#endif //FP2_PLAYER_H
