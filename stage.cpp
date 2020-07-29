#include <iostream>
#include <DxLib.h>
#include "Vector2.h"
#include "Stage.h"
#include "input/InputID.h"
#include "_debug/_DebugConOut.h"
#include "PyUpMode/DROP.h"
#include "PyUpMode/ERASE.h"
#include "PyUpMode/FALL.h"
#include "PyUpMode/GENERATES.h"

int Stage::stageCount_ = 0;

void Stage::input()
{
	(*controller_)();
	if(stgMode==STG_MODE::DROP)
	{
		for (auto data : controller_->GetCntData())
		{
			if (data.second[static_cast<int>(Trg::Now)] == 0 &&
				data.second[static_cast<int>(Trg::Old)] == 1)
			{
				for (int id = 0; id < 2; id++)
				{
					setPermition(puyo_[id]->GetGridPos());
					puyo_[id]->setMovePer(dirPer);
				}
				puyoMove(data.first);
			}
			if (data.second[static_cast<int>(Trg::Now)] == 1 &&
				data.second[static_cast<int>(Trg::Old)] == 1)
			{
				for (int id = 0; id < 2; id++)
				{
					setPermition(puyo_[id]->GetGridPos());
					puyo_[id]->setMovePer(dirPer);
					puyo_[id]->Down(data.first);
				}
			}
		}
	}
}

void Stage::update()
{
	StgModeFunc[stgMode](&(*this));
}

void Stage::draw()
{
	DrawFormatString(0, 0, 0xff0000, "stage");
	

	for (size_t id = 0; id < gridCountX * gridCountY; id++)
	{
		DrawBox(offset_.x + (id % gridCountX) * blockSizeX,
			(offset_.y + (id / gridCountX)) * blockSizeY,
			offset_.x + ((id % gridCountX) * blockSizeX + blockSizeX),
			(offset_.y + (id / gridCountX)) * blockSizeY + blockSizeY,
			0x888888, false);
		DrawFormatString(offset_.x + (id % gridCountX) * blockSizeX,
			(offset_.y + (id / gridCountX)) * blockSizeY, 0xffffff, "%d", stgData_[id % gridCountX][id / gridCountX]);
	}
	for (auto&& PUYO : puyo_)
	{
		PUYO->draw();
	}
	frame++;
}

void Stage::makePuyo()
{
	if (dirPer.perBit.d == 1)
	{
		puyo_.emplace(puyo_.begin(), std::make_unique<Puyo>(this->_pos, Vector2(3, 1)));
		puyo_[0]->setBlockSize(blockSizeX);
		puyo_.emplace(puyo_.begin()+1, std::make_unique<Puyo>(this->_pos, Vector2(4, 1)));
		puyo_[1]->setBlockSize(blockSizeX);
	}
}

void Stage::updtPuyoData()
{
	Vector2 tmp1 = { 1,4 };
	Vector2 tmp2 = { 1,4 };
	Vector2 tmp3 = tmp1 * tmp2;
}

void Stage::SetStageData()
{
	size_t count = 0;
	Vector2 tmp = { 0,0 };
	for (auto Data : stgDataBase_)
	{
		stgData_[count % gridCountX][count / gridCountX] = PUYO_TYPE::NON;
		// x軸の壁をセット
		// y軸の壁をセット
		count++;
	}
	for (size_t y = 0; y < gridCountY; y++)
	{	stgData_[0][y] = PUYO_TYPE::WALL;
		stgData_[gridCountX-1][y] = PUYO_TYPE::WALL;}

	for (size_t x = 0; x < gridCountX; x++)
	{
		stgData_[x][0] = PUYO_TYPE::WALL;
		stgData_[x][gridCountY-1] = PUYO_TYPE::WALL;
	}
	for (auto&& PUYO : puyo_)
	{
		tmp = PUYO->GetGridPos();
		stgData_[tmp.x][tmp.y] = PUYO->GetPuyoType();
	}
}

void Stage::setErasePuyo()
{
	//eraseDataBase_=stgDataBase_;	// 消去用データ
	//if(eraseData_[GridPos.x][GridPos.y])

}

void Stage::SetPuyoData()
{
	Vector2 tmp;
	for(auto&& PUYO: puyo_) {
		tmp = PUYO->GetGridPos();
		stgData_[tmp.x][tmp.y] = PUYO->GetPuyoType();
	}
}


bool Stage::setPermition(Vector2 tmp)
{
	dirPer.perBit.u = stgData_[tmp.x][tmp.y - 1] == PUYO_TYPE::NON ? 0 : 1;
	dirPer.perBit.r = stgData_[tmp.x + 1][tmp.y] == PUYO_TYPE::NON ? 0 : 1;
	dirPer.perBit.d = stgData_[tmp.x][tmp.y + 1] == PUYO_TYPE::NON ? 0 : 1;
	dirPer.perBit.l = stgData_[tmp.x - 1][tmp.y] == PUYO_TYPE::NON ? 0 : 1;
	return true;
}

bool Stage::chErasePuyo(Vector2&& GridPos, Vector2&& chGridPos)
{
	if (ErPyDelPos_.size() < gridCountX * gridCountY)
	{
		// もし、puyoIDが同じだったら
		if (stgData_[GridPos.x][GridPos.y] == stgData_[chGridPos.x][chGridPos.y])
		{
			for(auto&& ErPyDelPos:ErPyDelPos_)
				if (ErPyDelPos == chGridPos)
				{
					return false;
				}
			ErPyDelPos_.emplace_back(Vector2(chGridPos));
			return true;
		}
	}
	return false;
}

bool Stage::ErasePuyo(Vector2&& GridPos)
{
	Vector2 OldPos = {0,0};

	chPuyo_ = [&](Vector2&& tmp,Vector2&& oldPos) {
		if (oldPos != Vector2(tmp.x, tmp.y - 1))
		{
			if (chErasePuyo(Vector2(tmp.x, tmp.y), Vector2(tmp.x, tmp.y - 1)))
			chPuyo_(Vector2(tmp.x, tmp.y - 1),std::move(tmp));
		}
		if (oldPos != Vector2(tmp.x + 1, tmp.y))
		{
			if (chErasePuyo(Vector2(tmp.x, tmp.y), Vector2(tmp.x + 1, tmp.y)))
			chPuyo_(Vector2(tmp.x + 1, tmp.y), std::move(tmp));
		}
		if (oldPos != Vector2(tmp.x, tmp.y + 1))
		{
			if (chErasePuyo(Vector2(tmp.x, tmp.y), Vector2(tmp.x, tmp.y + 1)))
			chPuyo_(Vector2(tmp.x, tmp.y + 1), std::move(tmp));
		}
		if (oldPos != Vector2(tmp.x - 1, tmp.y))
		{
			if (chErasePuyo(Vector2(tmp.x, tmp.y), Vector2(tmp.x - 1, tmp.y)))
			chPuyo_(Vector2(tmp.x - 1, tmp.y), std::move(tmp));
		}
	};
	ErPyDelPos_.emplace_back(Vector2(GridPos));
	chPuyo_(std::move(GridPos),std::move(GridPos));

	//trace("%d\n", erpydelpos_.size())
	//trace("------------------------------\n")
	if (PUYO_DELETE_NUM > ErPyDelPos_.size())
	{
		ErPyDelPos_.clear();
		return false;
	}
	if (ErPyDelPos_.size() >= PUYO_DELETE_NUM)
		for (auto&& Puyo : puyo_)
		{
			for (auto&& ErasePuyo : ErPyDelPos_)
			{
				if (ErasePuyo == Puyo->GetGridPos())
				{
					Puyo->SetAlive(false);
				}
			}
		}
	return true;
}

bool Stage::puyoMove(InputID inputID)
{

	auto RotatePuyo = [&]() {};

	switch (inputID)
	{
	case InputID::Up:
		//if (dirPer_.perBit.u == 0)pos_.y--;
		break;
	case InputID::Down:
		break;
	case InputID::Left:
		if (puyo_[0]->dirPer_.perBit.l == 0)
		{
			puyo_[0]->pos_.x -= puyo_[0]->blockSize;
			puyo_[1]->pos_.x -= puyo_[1]->blockSize;
		}
		break;
	case InputID::Right:
		if (puyo_[1]->dirPer_.perBit.r == 0)
		{
			puyo_[0]->pos_.x += puyo_[0]->blockSize;
			puyo_[1]->pos_.x += puyo_[1]->blockSize;
		}
		break;
	case InputID::Btn1:

		break;
	case InputID::Btn2:
		break;
	case InputID::Max:
		break;
	default:
		break;
	}
	return true;
}


Vector2 Stage::getChipPos()
{
	return _pos;
}

bool Stage::DeletePuyo()
{
	//TRACE("%d\n",ErPyDelPos_.size())
	//for (auto&& ErPyDelPos : ErPyDelPos_)
	//{
	//	TRACE("(%d,%d)\n", ErPyDelPos.x,ErPyDelPos.y)
	//}
	//TRACE("------------------------------\n")


	auto RemovePuyo = std::remove_if(puyo_.begin(), puyo_.end(), [&](auto&& puyo) 
	{
		return (puyo->GetAlive() == false);
	});

	puyo_.erase(RemovePuyo,puyo_.end());
	ErPyDelPos_.clear();

	SetPuyoData();
	return false;
}

std::vector<PUYO_TYPE*> Stage::GetErasePos()
{
	return eraseData_;
}


bool Stage::Init(Vector2& Pos)
{
	dirPer = { 1,1,1,1 };
	frame = 0;
	this->_pos = Pos;

	if (stageCount_ == 0) 
	{ controller_=std::make_unique<KeyInput>(); }
	if(stageCount_==1)
	{ controller_=std::make_unique<Pad>(); }

	controller_->Setup(stageCount_);
	stageCount_++;
	color_ = 0x000033 << (16 * stageCount_);

	//puyo_.emplace_back(new Puyo(this->_pos));
	//puyo_[0]->setBlockSize(blockSizeX);

	stgDataBase_.resize(gridCountX * gridCountY);
	for(int no=0;no<gridCountX;no++)
	{stgData_.emplace_back(&stgDataBase_[no * gridCountY]);}
	SetStageData();

	eraseDataBase_.resize(gridCountX * gridCountY);
	for (int no = 0; no < gridCountX; no++)
	{eraseData_.emplace_back(&eraseDataBase_[no * gridCountY]);}
	SetStageData();

	_checkGridCount = 0;

	stgMode = STG_MODE::GENERATES;
	GrHandle = MakeScreen(gridCountX * blockSizeX, gridCountY * blockSizeY, false);
	// frendで関数オブジェクトを呼び出す
	StgModeFunc.try_emplace(STG_MODE::DROP, DROP());
	StgModeFunc.try_emplace(STG_MODE::ERASE, ERASE());
	StgModeFunc.try_emplace(STG_MODE::FALL, FALL());
	StgModeFunc.try_emplace(STG_MODE::GENERATES, GENERATES());
	return true;
}


Stage::Stage(Vector2 && offset, Vector2&& size) :blockSizeX(30), blockSizeY(30),
							gridCountX(8), gridCountY(15)
{
	offset_ = offset;
	size_ = size;

	Init(offset_ );
}

Stage::~Stage()
{
	DeleteGraph(GrHandle);
}
