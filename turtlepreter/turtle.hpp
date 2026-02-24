#ifndef TURTLEPRETER_TURTLE_HPP
#define TURTLEPRETER_TURTLE_HPP

#include "controllable.hpp"
#include "perk.hpp"

#include <vector>
#include <imgui/imgui.h>

namespace turtlepreter
{

    // --------------------------------------------------
    // TurtleCommand
    // --------------------------------------------------
    class TurtleCommand : public ICommand
    {
    protected:
        void execute(Controllable &c) final;
        bool canBeExecuted(Controllable &c) override;
        virtual void executeOnTurtle(Turtle &t) = 0;
    };

    class Turtle : virtual public Controllable
    {
    public:
        Turtle(const std::string &imgPath);
        Turtle(const std::string &imgPath, float centerX, float centerY);

        void draw(const friimgui::Region &region);
        void reset();

        void move(float distance);
        void jump(float x, float y);
        void rotate(float angleRad);

        size_t getPathSegmentCount() const;
        ImVec4 getPathSegmentPoints(size_t i) const;
        ImColor getPathSegmentColor(size_t i) const;
        void setColor(ImColor color);

    private:
        std::vector<ImVec4>     path;
        ImColor                 m_color;
        std::vector<ImColor>    m_path_color;
    };

    class Tortoise : public Turtle, public Runner
    {
    public:
        Tortoise(const std::string &imgPath);
        Tortoise(const std::string &imgPath, float centerX, float centerY, int fullStat);

        void reset() override;
    };

    // --------------------------------------------------
    // CommandMove
    // --------------------------------------------------
    class CommandMove : public TurtleCommand
    {
    public:
        CommandMove(float d);
        std::string toString() override;
        void executeOnTurtle(Turtle &t) override;
        void log(std::ostream &ost) const override;

    private:
        float m_d;
    };

    // --------------------------------------------------
    // CommandJump
    // --------------------------------------------------
    class CommandJump : public TurtleCommand
    {
    public:
        CommandJump(float x, float y);
        std::string toString() override;
        void executeOnTurtle(Turtle &t) override;
        void log(std::ostream &ost) const override;

        

    private:
        float m_x;
        float m_y;
    };

    // --------------------------------------------------
    // CommandRotate
    // --------------------------------------------------
    class CommandRotate : public TurtleCommand
    {
    public:
        CommandRotate(float angle);
        std::string toString() override;
        void executeOnTurtle(Turtle &t) override;
        void log(std::ostream &ost) const override;

    private:
        float m_angleRad;
    };


    // --------------------------------------------------
    // CommandSetColor
    // --------------------------------------------------
    class CommandSetColor : public TurtleCommand
    {
    public:
        CommandSetColor(ImColor color);
        std::string toString() override;
        void executeOnTurtle(Turtle &turtle) override;
        void log(std::ostream &ost) const override;

    private:
        ImColor m_color;
    };
} // namespace turtlepreter

#endif
