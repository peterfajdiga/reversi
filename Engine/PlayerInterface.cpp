#include "PlayerInterface.h"


namespace reversi {
	PlayerInterface::PlayerInterface()
	{

	}


	PlayerInterface::~PlayerInterface()
	{

	}


	void PlayerInterface::setId(int id)
	{
		mId = id;
		mName = "Player " + std::to_string(id);
	}


	int PlayerInterface::getId() const
	{
		return mId;
	}


	void PlayerInterface::setName(std::string name)
	{
		mName = name;
	}


	std::string PlayerInterface::getName() const
	{
		return mName;
	}



	void PlayerInterface::setScore(int score)
	{
		mScore = score;
	}


	int PlayerInterface::getScore() const
	{
		return mScore;
	}

}