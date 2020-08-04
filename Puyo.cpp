#include <random>
#include <iostream>
#include <DxLib.h>
#include "Stage.h"
#include "Puyo.h"
#include "input/controller.h"
#include "_debug/_DebugConOut.h"


Puyo::Puyo(Vector2& fieldPos, Vector2 GridPos)
{
    
    Init(fieldPos, GridPos);
}

Puyo::~Puyo()
{
}

void Puyo::update()
{

}

void Puyo::draw()
{
    DrawOval(pos_.x, pos_.y+ ROffPos_.y,
        radious.x,radious.y, color[static_cast<int>(puyoType)], 1, 1);
    
    if (munyonBox_.perBit.u == 1)
    {
        DrawBox(pos_.x - blockSize / 2, pos_.y -radious.y + ROffPos_.y,
            pos_.x + blockSize / 2, pos_.y + ROffPos_.y,
            color[static_cast<int>(puyoType)], true);
    }
    
    if (munyonBox_.perBit.d == 1)
    {
        DrawBox(pos_.x - blockSize / 2, pos_.y + ROffPos_.y,
            pos_.x + radious.x, pos_.y + radious.y + ROffPos_.y,
            color[static_cast<int>(puyoType)], true);
    }

    if (munyonBox_.perBit.r == 1)
    {
        DrawBox(pos_.x, pos_.y - radious.y + ROffPos_.y,
            pos_.x + blockSize/2, pos_.y + radious.y + ROffPos_.y,
            color[static_cast<int>(puyoType)], true);
    }

    if (munyonBox_.perBit.l == 1)
    {
        DrawBox(pos_.x - blockSize / 2, pos_.y - radious.y + ROffPos_.y,
            pos_.x, pos_.y + radious.y + ROffPos_.y,
            color[static_cast<int>(puyoType)], true);
    }
   // DrawCircle(pos_.x, pos_.y,
   //     2, 0xffffff, 1, 1);
   //DrawCircle(GetGridPos().x* blockSize + offsetPos_.x+blockSize/2,
   //    GetGridPos().y * blockSize + offsetPos_.y + blockSize / 2,
   //    3,0xffffff,1,1);
}

void Puyo::setBlockSize(int size)
{
    blockSize = size;
}

bool Puyo::drop()
{
    if (dirPer_.perBit.d == 0)
    {
        pos_.y+= 1;
        return true;
    }
    return false;
}

bool Puyo::DeletePuyo()
{
    // remove_if‚ðŽg‚Á‚Ä‚¯‚·
    return false;
}

void Puyo::SetMatchGrid(Vector2&& Pos)
{
    pos_ = Pos + offsetPos_-blockSize/2;
}

void Puyo::Down(InputID id)
{
    if (id == InputID::Down)
    {
        pos_.y += 6;
    }
}


Vector2 Puyo::GetGridPos()
{
    return Vector2((pos_.x - offsetPos_.x - blockSize / 2) / blockSize, (pos_.y - offsetPos_.y - blockSize / 2) / blockSize);
}

PUYO_TYPE Puyo::GetPuyoType()
{
    return puyoType;
}

bool Puyo::GetAlive()
{
    return alive_;
}

void Puyo::SetAlive(bool aliveFlag)
{
    alive_ = aliveFlag;
}

bool Puyo::Init(Vector2& stagePos, Vector2& GridPos)
{
    std::random_device seed_gen;
    std::mt19937 random_(seed_gen());
    std::uniform_int_distribution<int> dist(static_cast<int>(PUYO_TYPE::R), static_cast<int>(PUYO_TYPE::P));
    dirPer_.perBit = { 0,0,0,0 };
    munyonBox_.perBit = { 0,0,0,0 };
    ROffPos_ = Vector2(0, 0);
    radious = Vector2(15, 15);
    blockSize = 32;
    pos_ = stagePos;
    offsetPos_ = pos_;
    pos_.x += blockSize / 2 + blockSize*GridPos.x;
    pos_.y += blockSize / 2 + blockSize*GridPos.y;
    speed = 2;
    puyoState = PUYO_STATE::MOVE;
    puyoType = static_cast<PUYO_TYPE>(dist(random_));
    alive_ = true;
    return true;
}
