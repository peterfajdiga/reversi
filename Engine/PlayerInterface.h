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
     *
     * Game view may access player objects via engine.getPlayer(id).
     *
     */
    class PlayerInterface
    {
    public:
        PlayerInterface();

        virtual ~PlayerInterface();

        virtual void setId(int id);
        virtual int getId() const;

        virtual std::string generateName();
        virtual void setName(const std::string& name);
        virtual std::string getName() const;

        virtual void setScore(int score);
        virtual int getScore() const;

        virtual std::string promptInput(Engine& engine, ViewInterface& view, bool isGameOver = false) = 0;

    private:
        int mId;
        std::string mName;
        int mScore;
    };

}
