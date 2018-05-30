#pragma once

#include <string>
#include "ViewInterface.h"
#include "constants.h"

namespace reversi {

    class Engine; // forward declaration

    /**
     * PlayerInterface
     *
     * Abstract class to organize player data.
     *
     * Concrete player classes must implement the promptInput method.
     * HumanPlayer is implemented and is the initial player type.
     *
     * Game view may access player objects via engine.getPlayer(id).
     *
     */
    class PlayerInterface
    {
        friend class Engine;

    public:
        PlayerInterface();

        PlayerInterface(const std::string& name);

        virtual ~PlayerInterface();

        virtual id getId() const;

        virtual void setScore(score s);
        virtual score getScore() const;

        virtual std::string promptInput(Engine& engine, ViewInterface& view, bool isGameOver = false) = 0;

        const std::string name;

    private:
        id mId;
        score mScore;
    };

}
