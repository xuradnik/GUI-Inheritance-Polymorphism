#ifndef TURTLEPRETER_PERK_HPP
#define TURTLEPRETER_PERK_HPP

#include "interpreter.hpp"

#include <imgui/imgui.h>
#include <string>

namespace turtlepreter
{

    // --------------------------------------------------
    // Perk
    // --------------------------------------------------
    class Perk : virtual public Controllable
    {
    public:
        Perk(const std::string &imgPath, float centerX, float centerY, int fullStat);
        void reset() override;

    protected:
        bool hasStat();
        void useStat();

    private:
        int m_stat;
        int m_fullStat;
    };

    // --------------------------------------------------
    // Runner
    // --------------------------------------------------
    class Runner : public Perk
    {
    public:
        Runner(const std::string &imgPath, float centerX, float centerY, int fullStat);

        bool hasStamina();
        void useStamina();
        void reset() override;

        void jump(float x, float y);

    private:
        int m_fullStamina;
        int m_stamina;
    };

    // --------------------------------------------------
    // Swimmer
    // --------------------------------------------------
    class Swimmer : public Perk
    {
    public:
        Swimmer(const std::string &imgPath, float centerX, float centerY, int fullStat);

        bool hasOxygen();
        void useOxygen();
        void reset() override;

        void jump(float x, float y);

    private:
        int m_fullOxygen;
        int m_oxygen;
    };

    // --------------------------------------------------
    // CommandRun
    // --------------------------------------------------
    class CommandRun : public ICommand
    {
    public:
        CommandRun(ImVec2 dest);

        void execute(Controllable &controllable) override;
        std::string toString() override;
        bool canBeExecuted(Controllable &controllable) override;

    private:
        ImVec2 m_dest;
    };

    // --------------------------------------------------
    // CommandSwim
    // --------------------------------------------------
    class CommandSwim : public ICommand
    {
    public:
        CommandSwim(ImVec2 dest);

        void execute(Controllable &controllable) override;
        std::string toString() override;
        bool canBeExecuted(Controllable &controllable) override;

    private:
        ImVec2 m_dest;
    };

} // namespace turtlepreter

#endif
