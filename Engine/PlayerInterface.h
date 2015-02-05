#pragma once

#include <string>
#include "ViewInterface.h"

namespace reversi {

	class Engine; // forward declaration

	/**
	 * PlayerInterface
	 *
	 * Abstract class to organize player data.
	 *
	 * Concrete player classes must implement the promptInput method.
	 * HumanPlayer is implemented and is the initial player type.
	 * Use dynamic_cast to change a player's type (from human to computer, etc.)
	 *
	 * Game view may access player objects via engine.getPlayer(id).
	 * View may get the player id and score, and may set the player name.
	 *
	 */
	class PlayerInterface
	{
	public:
		PlayerInterface();
		PlayerInterface(std::string name);

		virtual ~PlayerInterface();

		virtual int getId() const;

		virtual void setName(std::string name) const;
		virtual std::string getName() const;

		virtual void setScore(int score);
		virtual int getScore() const;

		virtual std::string promptInput(Engine& engine, ViewInterface& view, bool isGameOver = false) = 0;

	private:
		static int sIdCounter;

		int mId;
		mutable std::string mName;
		int mScore;
	};

}