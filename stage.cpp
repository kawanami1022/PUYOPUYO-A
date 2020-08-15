#include <iostream>
#include <random>
#include <algorithm>
#include <DxLib.h>
#include <EffekseerForDXLib.h>
#include "Vector2.h"
#include "Stage.h"
#include "input/InputID.h"
#include "input/keyInput.h"
#include "input/Pad.h"
#include "input/mouse.h"
#include "_debug/_DebugConOut.h"
#include "PyUpMode/DROP.h"
#include "PyUpMode/ERASE.h"
#include "PyUpMode/PUYON.h"
#include "PyUpMode/MUNYON.h"
#include "PyUpMode/FALL.h"
#include "PyUpMode/GENERATES.h"
#include "PyUpMode/EFFECT.h"
#include "PyInputMode/IpLeft.h"
#include "PyInputMode/IpRight.h"
#include "PyInputMode/IpTurnL.h"
#include "PyInputMode/IpTurnR.h"
#include "PyInputMode/IpUp.h"
#include "PyInputMode/lpDown.h"
#include	"Puyo/nextPuyo.h"
#include "DxLibForHomeBrew/DxLib_Draw.h"

int Stage::stageCount_ = 0;

void Stage::input()
{
	(*controller_)();
	if(stgMode==STG_MODE::DROP)
	{
		for (auto&& data : controller_->GetCntData())
		{
			if (data.second[static_cast<int>(Trg::Now)] == 0 &&
				data.second[static_cast<int>(Trg::Old)] == 1)
			{
				for (int id = 0; id < 2; id++)
				{
					setPermition(puyo_[id]->GetGridPos(), id);
				}
				StgInputFunc[data.first](&(*this));
			}
			if (data.second[static_cast<int>(Trg::Now)] == 1 &&
				data.second[static_cast<int>(Trg::Old)] == 1)
			{
				for (int id = 0; id < 2; id++)
				{
					setPermition(puyo_[id]->GetGridPos(), id);
					puyo_[id]->Down(data.first);
				}
			}
		}
	}
}

int Stage::update()
{
	StgModeFunc[stgMode](&(*this));


	for (int i = 1; i < SetChainCount_; i++)
	{
		obsPuyo_.push_front(ObsPuyo(offset_, Vector2(i, 0)));
	}
	if (stgMode == STG_MODE::GENERATES)
	{return GetChainCount_;}
	return 0;
}

void Stage::draw()
{

	controller_->DebugDrow(id_);


	DrawLine(offset_.x, offset_.y+blockSize*gridCountY,
		offset_.x+gridCountX*blockSize, offset_.y + blockSize * gridCountY,
		0xffffff, false);
	for (auto&& PUYO : puyo_)
	{
		PUYO->draw();
	}
	for (auto&& OBSPUYO : obsPuyo_)
	{
		OBSPUYO.draw();
	}

	for (int y = 0; y < gridCountY; y++)
	{
		for (int x = 0; x < gridCountX; x++)
		{
			if(stgData_[x][y]== PUYO_TYPE::WALL)
			DrawGraph(offset_.x + x * blockSize, offset_.y + y * blockSize,GrHandle_[STCI(PUYO_TYPE::WALL)], true);
		}
	}


	for (auto&& GuidePos : GuidePyPos_)
	{
		DrawGraph(offset_.x + GuidePos.x * blockSize, offset_.y + GuidePos.y * blockSize,
			GrHandle_[8], true);
	}

	DrawBox(nextBoxPos.x + (screenSizeX / 8) * (3 + id_) - blockSize / 2,
		nextBoxPos.y,
		nextBoxPos.x + (screenSizeX / 8) * (3 + id_) + blockSize / 2,
		nextBoxPos.y + blockSize * 2,
		0xffffff, false);

	for (auto&& NEXTPUYO : nextPuyo_)
	{
		NEXTPUYO->draw();
	}
	
	// Effekseerにより再生中のエフェクトを更新する。
	UpdateEffekseer2D();

	// Effekseerにより再生中のエフェクトを描画する。
	DrawEffekseer2D();


	frame++;
}

void Stage::makePuyo()
{

	puyo_.emplace(puyo_.begin(), std::make_unique<Puyo>(
		this->_pos, Vector2(3, 1),nextPuyo_[0]->puyoType_, GrHandle_[STCI(nextPuyo_[0]->puyoType_)]));
	puyo_[0]->setBlockSize(blockSize);
	puyo_.emplace(puyo_.begin() + 1, std::make_unique<Puyo>(
		this->_pos, Vector2(4, 1), nextPuyo_[1]->puyoType_, GrHandle_[STCI(nextPuyo_[1]->puyoType_)]));
	puyo_[1]->setBlockSize(blockSize);
}

void Stage::setNextPuyo()
{
	std::random_device seed_gen;
	std::mt19937 random_(seed_gen());
	std::uniform_int_distribution<int> dist(static_cast<int>(PUYO_TYPE::R), static_cast<int>(PUYO_TYPE::P));

	PUYO_TYPE PuyoType= static_cast<PUYO_TYPE>(dist(random_));

	nextPuyo_.clear();
	nextPuyo_.emplace(nextPuyo_.begin(), 
		std::make_unique<nextPuyo>(
			Vector2(nextBoxPos.x +(screenSizeX / 8) * (3 + id_),
				nextBoxPos.y+blockSize/2+ blockSize*0),
				PuyoType,GrHandle_[STCI(PuyoType)]));
	nextPuyo_[0]->setBlockSize(blockSize);

	PuyoType= static_cast<PUYO_TYPE>(dist(random_));
	nextPuyo_.emplace(nextPuyo_.begin() +1,
		std::make_unique<nextPuyo>(
			Vector2(nextBoxPos.x + (screenSizeX / 8) * (3 + id_), 
				nextBoxPos.y + blockSize / 2 + blockSize * 1),
				PuyoType, GrHandle_[STCI(PuyoType)]));
	nextPuyo_[1]->setBlockSize(blockSize);

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
	// puyo
}

void Stage::SetPuyoData()
{
	Vector2 tmp;
	for(auto&& PUYO: puyo_) {
		tmp = PUYO->GetGridPos();
		stgData_[tmp.x][tmp.y] = PUYO->GetPuyoType();
	}
}


bool Stage::setPermition(Vector2 tmp, int ID)
{
	//puyo_[ID]->dirPer_.perBit.u = stgData_[tmp.x][tmp.y - 1] == PUYO_TYPE::NON ? 0 : 1;
	puyo_[ID]->dirPer_.perBit.r = stgData_[tmp.x + 1][tmp.y] == PUYO_TYPE::NON ? 0 : 1;
	puyo_[ID]->dirPer_.perBit.d = stgData_[tmp.x][tmp.y + 1] == PUYO_TYPE::NON ? 0 : 1;
	puyo_[ID]->dirPer_.perBit.l = stgData_[tmp.x - 1][tmp.y] == PUYO_TYPE::NON ? 0 : 1;
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

void Stage::SetChainCount(int SetChainCount)
{
	SetChainCount_ = SetChainCount;
}

void Stage::SetPuyoGuide()
{
	GuidePyPos_[0] = puyo_[0]->GetGridPos();
	GuidePyPos_[1] = puyo_[1]->GetGridPos();
	int idx = 0;
	for (auto&& GuidePyPos : GuidePyPos_)
	{
		for (int Grid_y = GuidePyPos_[idx].y; Grid_y < gridCountY; Grid_y++)
		{
			if (stgData_[GuidePyPos_[idx].x][Grid_y + 1] != PUYO_TYPE::NON)
			{
				GuidePyPos_[idx].y = Grid_y;
				break;
			}
		}
		idx++;
	}
}

void Stage::ChangeInputMode(ComInputID comInput)
{
	auto func = [&](ComInputID inputID) {
		ContType contTypeTmp = controller_->GetType();

		if (inputID == ComInputID::PG_DOWN)
			contTypeTmp = static_cast<ContType>((STCI(contTypeTmp) - 1) % STCI(ContType::Max));
		if (inputID == ComInputID::PG_UP)
			contTypeTmp = static_cast<ContType>((STCI(contTypeTmp) + 1) % STCI(ContType::Max));

		if (contTypeTmp == ContType::Key)			controller_ = std::make_unique<KeyInput>();
		if (contTypeTmp == ContType::Mouse)		controller_ = std::make_unique<mouse>();
		if (contTypeTmp == ContType::Pad)			controller_ = std::make_unique<Pad>();
		controller_->Setup(id_);
	};
	func(comInput);
}

Vector2 Stage::getChipPos()
{
	return _pos;
}

bool Stage::DeletePuyo()
{

	auto RemovePuyo = std::remove_if(puyo_.begin(), puyo_.end(), [&](auto&& puyo) 
	{
		if(puyo->GetAlive() == false)
		ErPyDel_.emplace_back(puyo);
		return (puyo->GetAlive() == false);
	});

	puyo_.erase(RemovePuyo,puyo_.end());
	ErPyDelPos_.clear();
	return false;
}

std::vector<PUYO_TYPE*> Stage::GetErasePos()
{
	return eraseData_;
}


bool Stage::Init(Vector2& Pos)
{
	frame = 0;
	this->_pos = Pos;

	if (stageCount_ == 0) 
	{ controller_=std::make_unique<KeyInput>(); }
	if(stageCount_==1)
	{ controller_=std::make_unique<KeyInput>(); }

	controller_->Setup(stageCount_);
	id_ = stageCount_;
	stageCount_++;
	color_ = 0x000033 << (16 * stageCount_);

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
	GetChainCount_ = 0;
	SetChainCount_ = 0;
	ObsDropCnt_ = 0;
	GuidePyPos_[0] = { 0,0 };
	GuidePyPos_[1] = { 0,0 };
	stgMode = STG_MODE::GENERATES;
	// frendで関数オブジェクトを呼び出す
	StgModeFunc.try_emplace(STG_MODE::DROP, DROP());
	StgModeFunc.try_emplace(STG_MODE::ERASE, ERASE());
	StgModeFunc.try_emplace(STG_MODE::MUNYON, MUNYOUN());
	StgModeFunc.try_emplace(STG_MODE::PUYON, PUYON());
	StgModeFunc.try_emplace(STG_MODE::FALL, FALL());
	StgModeFunc.try_emplace(STG_MODE::GENERATES, GENERATES());
	StgModeFunc.try_emplace(STG_MODE::EFFECT, EFFECT());

	StgInputFunc.try_emplace(InputID::Up, IpUp());
	StgInputFunc.try_emplace(InputID::Left, IpLeft());
	StgInputFunc.try_emplace(InputID::Down,IpDown());
	StgInputFunc.try_emplace(InputID::Right, IpRight());
	StgInputFunc.try_emplace(InputID::TURN_L, IpTurnL());
	StgInputFunc.try_emplace(InputID::TURN_R,IpTurnR());

	// グラフィックハンドルを用意
	GrHandle_.reserve(STCI(PUYO_TYPE::MAX));
	GrHandle_.emplace_back(textureFactory.GetTexture("")->GetHandle());
	GrHandle_.emplace_back(textureFactory.GetTexture("Image/RED_Puyo.png")->GetHandle());
	GrHandle_.emplace_back(textureFactory.GetTexture("Image/GREEN_Puyo.png")->GetHandle());
	GrHandle_.emplace_back(textureFactory.GetTexture("Image/BLUE_Puyo.png")->GetHandle());
	GrHandle_.emplace_back(textureFactory.GetTexture("Image/PURPLE_Puyo.png")->GetHandle());
	GrHandle_.emplace_back(textureFactory.GetTexture("Image/YELLOW_Puyo.png")->GetHandle());
	GrHandle_.emplace_back(textureFactory.GetTexture("Image/ICE_Puyo.png")->GetHandle());
	GrHandle_.emplace_back(textureFactory.GetTexture("Image/PuyoWall.png")->GetHandle());
	GrHandle_.emplace_back(textureFactory.GetTexture("Image/GuideBlock.png")->GetHandle());
	setNextPuyo();
	efkInit();
	//changeInputType.try_emplace(ContType::Key, [](int x) { return x + 1; });

	return true;
}

bool Stage::efkInit()
{
	EffectHandle_.emplace_back(efkFac_.GetEfkHandle("", 0.f));
	EffectHandle_.emplace_back(efkFac_.GetEfkHandle("Effects/FireBall.efk", 3.f));
	EffectHandle_.emplace_back(efkFac_.GetEfkHandle("Effects/Arrow1.efk", 5.f));
	EffectHandle_.emplace_back(efkFac_.GetEfkHandle("Effects/Benediction.efk", 5.f));
	EffectHandle_.emplace_back(efkFac_.GetEfkHandle("Effects/Blow3.efk", 5.f));
	EffectHandle_.emplace_back(efkFac_.GetEfkHandle("Effects/CosmicMist.efk", 1.f));
	EffectHandle_.emplace_back(efkFac_.GetEfkHandle("Effects/BloodLance.efk", 5.f));
 	return true;
}


Stage::Stage(Vector2 && offset, Vector2&& size) :
							screenSizeX(800), screenSizeY(600),
							blockSize(32),
							gridCountX(8), gridCountY(15)
{
	offset_ = offset;
	size_ = size;
	nextBoxPos = Vector2(50, 100);


	Init(offset_ );
}

Stage::~Stage()
{
	GrHandle_.clear();
	InitGraph();

}
