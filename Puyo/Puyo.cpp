#include <random>
#include <iostream>
#include <DxLib.h>
#include "../Stage.h"
#include "Puyo.h"
#include "../input/controller.h"
#include "../_debug/_DebugConOut.h"
#include "../DxLibForHomeBrew/DxLib_Draw.h"

Puyo::Puyo(Vector2&& Pos)
{
    dirPer_.perBit = { 0,0,0,0 };
    munyonBox_.perBit = { 0,0,0,0 };
    ROffPos_ = Vector2(0, 0);
    radious = Vector2(15, 15);
    blockSize = 32;
    pos_ += blockSize;
    pos_ = Pos;
    offsetPos_ = pos_;
    speed = 2;
    puyoState = PUYO_STATE::MOVE;
    alive_ = true;

}

Puyo::Puyo(Vector2& stagePos, Vector2 GridPos)
{
    
    Init(stagePos, GridPos);
}

Puyo::Puyo(Vector2& stagePos, Vector2 GridPos, PUYO_TYPE puyoType, int GrHandle)
{
    dirPer_.perBit = { 0,0,0,0 };
    munyonBox_.perBit = { 0,0,0,0 };
    ROffPos_ = Vector2(0, 0);
    radious = Vector2(15, 15);
    blockSize = 32;
    pos_ = stagePos;
    offsetPos_ = pos_;
    pos_.x += blockSize * GridPos.x + blockSize / 2;
    pos_.y += blockSize * GridPos.y + blockSize / 2;
    speed = 2;
    puyoState = PUYO_STATE::MOVE;
    puyoType_ = puyoType;
    GrHandle_ = GrHandle;
    alive_ = true;
}

Puyo::~Puyo()
{
}

void Puyo::update()
{

}

void Puyo::draw()
{
    
  
    DrawExtendGraph(pos_.x - radious.x - munyonBox_.perBit.l * 2,
        pos_.y - radious.y + ROffPos_.y - munyonBox_.perBit.u * 2,
        pos_.x + radious.x + munyonBox_.perBit.r * 2,
        pos_.y + radious.y + ROffPos_.y+munyonBox_.perBit.d* 2,
        GrHandle_, true);

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


void Puyo::SetMatchGrid()
{
    //pos_ = Pos + offsetPos_ -blockSize / 2;
    pos_ = GetGridPos()*blockSize+offsetPos_ + blockSize / 2;
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
    return puyoType_;
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
    puyoType_ = static_cast<PUYO_TYPE>(dist(random_));
    alive_ = true;
    return true;
}
