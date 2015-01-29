#pragma once

#include <string>


/**
 * Player
 *
 * Simple class to organize player data.
 *
 * Game view may access player objects via engine.getPlayer(id).
 * View may get the player id and score, and may get and set the
 * player name and type.
 *
 */
class Player
{
public:
	Player();
	Player(std::string name);

	virtual ~Player();

	enum PlayerType
	{
		HUMAN,
		COMPUTER_EASY,		// computer players enumerated for a future version
		COMPUTER_MEDIUM,	// and are not yet implemented
		COMPUTER_HARD
	};

	virtual int getId() const;

	virtual void setName(std::string name) const;
	virtual std::string getName() const;

	virtual void setType(PlayerType type) const;
	virtual PlayerType getType() const;

	virtual void setScore(int score);
	virtual int getScore() const;

private:
	static int sIdCounter;

	int mId;
	mutable std::string mName;
	mutable PlayerType mType;
	int mScore;
};
