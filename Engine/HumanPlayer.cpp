#include "HumanPlayer.h"


namespace reversi {

	HumanPlayer::HumanPlayer()
	{

	}


	HumanPlayer::~HumanPlayer()
	{

	}


	std::string HumanPlayer::promptInput(Engine& engine, ViewInterface& view, bool isGameOver)
	{
		return view.promptInput(engine, isGameOver);
	}

}