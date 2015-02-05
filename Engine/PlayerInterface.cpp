#include "PlayerInterface.h"


namespace reversi {

	int PlayerInterface::sIdCounter = 1;


	PlayerInterface::PlayerInterface()
	{
		using namespace std;

		mId = sIdCounter++;
		mName = "Player " + to_string(mId);
		mScore = 0;
	}


	PlayerInterface::PlayerInterface(std::string name)
	{
		using namespace std;

		mId = sIdCounter++;
		mName = name;
		mScore = 0;
	}


	PlayerInterface::~PlayerInterface()
	{

	}


	int PlayerInterface::getId() const
	{
		return mId;
	}


	void PlayerInterface::setName(std::string name) const
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