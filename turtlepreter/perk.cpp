#include "perk.hpp"

namespace turtlepreter
{

    // --------------------------------------------------
    // Perk
    // --------------------------------------------------
    Perk::Perk(const std::string &imgPath, float centerX, float centerY, int fullStat)
        : Controllable(imgPath, centerX, centerY),
          m_stat(fullStat),
          m_fullStat(fullStat)
    {
    }

    void Perk::reset()
    {
        Controllable::reset();
        m_stat = m_fullStat;
    }

    bool Perk::hasStat()
    {
        return m_stat > 0;
    }

    void Perk::useStat()
    {
        if (m_stat > 0)
        {
            --m_stat;
        }
    }

    // --------------------------------------------------
    // Runner
    // --------------------------------------------------
    Runner::Runner(const std::string &imgPath, float centerX, float centerY, int fullStat)
        : Controllable(imgPath, centerX, centerY),
          Perk(imgPath, centerX, centerY, fullStat),
          m_fullStamina(fullStat),
          m_stamina(fullStat)
    {
    }

    bool Runner::hasStamina()
    {
        return m_stamina > 0;
    }

    void Runner::useStamina()
    {
        if (m_stamina > 0)
        {
            --m_stamina;
        }
    }

    void Runner::jump(float x, float y)
    {
        ImVec2 orig = m_transformation.translation.getValueOrDef();
        ImVec2 dest(x, y);

        m_transformation.translation.setValue(dest);
    }

    void Runner::reset()
    {
        Perk::reset();
        m_stamina = m_fullStamina;
    }

    // --------------------------------------------------
    // Swimmer
    // --------------------------------------------------
    Swimmer::Swimmer(const std::string &imgPath, float centerX, float centerY, int fullStat)
        : Controllable(imgPath, centerX, centerY),
          Perk(imgPath, centerX, centerY, fullStat),
          m_fullOxygen(fullStat),
          m_oxygen(fullStat)
    {
    }

    bool Swimmer::hasOxygen()
    {
        return m_oxygen > 0;
    }

    void Swimmer::useOxygen()
    {
        if (m_oxygen > 0)
        {
            --m_oxygen;
        }
    }

    void Swimmer::jump(float x, float y)
    {
        ImVec2 orig = m_transformation.translation.getValueOrDef();
        ImVec2 dest(x, y);

        m_transformation.translation.setValue(dest);
    }

    void Swimmer::reset()
    {
        Perk::reset();
        m_oxygen = m_fullOxygen;
    }

    // --------------------------------------------------
    // CommandRun
    // --------------------------------------------------
    CommandRun::CommandRun(ImVec2 dest)
        : m_dest(dest)
    {
    }

    void CommandRun::execute(Controllable &c)
    {
        if (auto *runner = dynamic_cast<Runner *>(&c))
        {
            if (runner->hasStamina())
            {
                runner->jump(m_dest.x, m_dest.y);
                runner->useStamina();
            }
        }
        return;
    }

    std::string CommandRun::toString()
    {
        return std::string("Utekaj na (") + std::to_string(m_dest.x) + ";" + std::to_string(m_dest.y) + ")";
    }

    bool CommandRun::canBeExecuted(Controllable &c)
    {
        return dynamic_cast<Runner *>(&c) != nullptr;
    }

    // --------------------------------------------------
    // CommandSwim
    // --------------------------------------------------
    CommandSwim::CommandSwim(ImVec2 dest)
        : m_dest(dest)
    {
    }

    void CommandSwim::execute(Controllable &controllable)
    {
        if (auto *swimmer = dynamic_cast<Swimmer *>(&controllable))
        {
            if (swimmer->hasOxygen())
            {
                swimmer->jump(m_dest.x, m_dest.y);
                swimmer->useOxygen();
            }
        }
    }

    std::string CommandSwim::toString()
    {
        return std::string("Plavaj do (") + std::to_string(m_dest.x) + ";" + std::to_string(m_dest.y) + ")";
    }

    bool CommandSwim::canBeExecuted(Controllable &controllable)
    {
        return dynamic_cast<Swimmer *>(&controllable) != nullptr;
    }

} // namespace turtlepreter
