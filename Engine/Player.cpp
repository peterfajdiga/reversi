#include "Player.h"


namespace reversi {

	int Player::sIdCounter = 1;


	Player::Player()
	{
		using namespace std;

		mId = sIdCounter++;
		mName = "Player " + to_string(mId);
		mType = HUMAN;
		mScore = 0;
	}


	Player::Player(std::string name)
	{
		using namespace std;

		mId = sIdCounter++;
		mName = name;
		mType = HUMAN;
		mScore = 0;
	}


	Player::~Player()
	{

	}


	int Player::getId() const
	{
		return mId;
	}


	// mName is mutable
	void Player::setName(std::string name) const
	{
		mName = name;
	}


	std::string Player::getName() const
	{
		return mName;
	}


	// mType is mutable
	void Player::setType(PlayerType type) const
	{
		mType = type;
	}


	Player::PlayerType Player::getType() const
	{
		return mType;
	}

	void Player::setScore(int score)
	{
		mScore = score;
	}


	int Player::getScore() const
	{
		return mScore;
	}

}