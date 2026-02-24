#include "interpreter.hpp"
#include "turtle.hpp"

#include <imgui/imgui.h>

#include <stdexcept>

#include <cmath>

namespace turtlepreter
{

    // --------------------------------------------------
    // TurtleCommand
    // --------------------------------------------------

    void TurtleCommand::execute(Controllable &c)
    {
        if (canBeExecuted(c))
        {
            Turtle *t_p = dynamic_cast<Turtle *>(&c);
            executeOnTurtle(*t_p);
        }
    }

    bool TurtleCommand::canBeExecuted(Controllable &c)
    {
        if (dynamic_cast<Turtle *>(&c) != nullptr)
        {
            return true;
        }
        return false;
    }

    // +++++++++++++++++++++++++++++++++++++++
    // Turtle
    // +++++++++++++++++++++++++++++++++++++++

    Turtle::Turtle(const std::string &imgPath)
        : Controllable(imgPath), m_color(ImColor(0, 255, 0)), m_path_color()
    {
    }

    Turtle::Turtle(const std::string &imgPath, float centerX, float centerY)
        : Controllable(imgPath, centerX, centerY), m_color(ImColor(0, 255, 0)), m_path_color()
    {
    }

    void Turtle::draw(const friimgui::Region &region)
    {
        const float thickness = 1.0f;
        ImDrawList *drawList = ImGui::GetWindowDrawList();
        const ImVec2 p0 = region.getP0();

        for (size_t i = 0; i < getPathSegmentCount(); i++)
        {
            const ImVec4 lines = getPathSegmentPoints(i);

            drawList->AddLine(
                ImVec2(p0.x + lines.x, p0.y + lines.y),
                ImVec2(p0.x + lines.z, p0.y + lines.w),
                m_path_color.at(i),
                thickness);
        }

        Controllable::draw(region);
    }

    void Turtle::reset()
    {
        Controllable::reset();
        path.clear();
        m_transformation.rotation.resetValue();
        m_path_color.clear();
        m_color = ImColor(0, 255, 0);
    }

    void Turtle::move(float distance)
    {
        ImVec2 orig = m_transformation.translation.getValueOrDef();
        ImVec2 dest(orig.x + distance, orig.y);
        path.push_back(ImVec4(orig.x, orig.y, dest.x, dest.y));
        m_transformation.translation.setValue(dest);
        m_path_color.push_back(m_color);
    }

    void Turtle::jump(float x, float y)
    {
        ImVec2 orig = m_transformation.translation.getValueOrDef();
        ImVec2 dest(x, y);
        path.push_back(ImVec4(orig.x, orig.y, dest.x, dest.y));
        m_transformation.translation.setValue(dest);
        m_path_color.push_back(m_color);
    }

    void Turtle::rotate(float angleRad)
    {
        m_transformation.rotation.setValue(angleRad);
    }

    size_t Turtle::getPathSegmentCount() const
    {
        size_t to_return = path.size();
        return to_return;
    }

    ImVec4 Turtle::getPathSegmentPoints(size_t i) const
    {
        if (getPathSegmentCount() > i)
        {
            ImVec4 to_return = path.at(i);
            return to_return;
        }
        return ImVec4();
    }

    ImColor Turtle::getPathSegmentColor(size_t i) const
    {
        if (getPathSegmentCount() > i)
        {
            ImColor to_return = m_path_color.at(i);
            return to_return;
        }

        return ImColor();
    }

    void Turtle::setColor(ImColor color)
    {
        this->m_color = color;
    }

    // +++++++++++++++++++++++++++++++++++++++
    // Tortoise
    // +++++++++++++++++++++++++++++++++++++++

    Tortoise::Tortoise(const std::string &imgPath)
        : Controllable(imgPath),
          Turtle(imgPath),
          Runner(imgPath, 0, 0, 0)
    {
    }

    Tortoise::Tortoise(const std::string &imgPath, float centerX, float centerY, int fullStat)
        : Controllable(imgPath, centerX, centerY),
          Turtle(imgPath, centerX, centerY),
          Runner(imgPath, centerX, centerY, fullStat)
    {
    }

    void Tortoise::reset()
    {
        Turtle::reset();
        Runner::reset();
    }

    // --------------------------------------------------
    // CommandMove
    // --------------------------------------------------
    CommandMove::CommandMove(float d)
        : m_d(d)
    {
    }

    std::string CommandMove::toString()
    {
        return "Move by " + std::to_string(m_d);
    }

    void CommandMove::executeOnTurtle(Turtle &t)
    {
        t.move(m_d);
    }

    void CommandMove::log(std::ostream &ost) const
    {

        ost << "move(" << std::defaultfloat << m_d << ")\n";
    }

    // --------------------------------------------------
    // CommandRotate
    // --------------------------------------------------
    CommandRotate::CommandRotate(float angle)
        : m_angleRad(angle)
    {
    }

    void CommandRotate::executeOnTurtle(Turtle &t)
    {
        t.rotate(m_angleRad);
    }

    std::string CommandRotate::toString()
    {
        return "Rotate by " + std::to_string(m_angleRad) + " radians";
    }
    void CommandRotate::log(std::ostream &ost) const
    {
        ost << "rotate(" << std::defaultfloat << m_angleRad << ")\n";
    }

    // --------------------------------------------------
    // CommandJump
    // --------------------------------------------------
    CommandJump::CommandJump(float x, float y)
        : m_x(x),
          m_y(y)
    {
    }

    std::string CommandJump::toString()
    {
        return "Jump to [" + std::to_string(m_x) + ";" + std::to_string(m_y) + "]";
    }

    void CommandJump::executeOnTurtle(Turtle &t)
    {
        t.jump(m_x, m_y);
    }

    void CommandJump::log(std::ostream &ost) const
    {

        ost << "jump(" << std::defaultfloat << m_x << "," << m_y << ")\n";
    }

    // --------------------------------------------------
    // CommandSetColor
    // --------------------------------------------------
    CommandSetColor::CommandSetColor(ImColor color) : m_color(color)
    {
    }

    std::string CommandSetColor::toString()
    {
        int r = (int)(m_color.Value.x);
        int g = (int)(m_color.Value.y);
        int b = (int)(m_color.Value.z);
        int a = (int)(m_color.Value.w);

        return ("Set color (" + std::to_string(r) + "," + std::to_string(g) + "," + std::to_string(b) + "," + std::to_string(a) + ")");
    }

    void CommandSetColor::executeOnTurtle(Turtle &turtle)
    {
        turtle.setColor(m_color);
    }

    void CommandSetColor::log(std::ostream &ost) const
    {

        int r = (int)(m_color.Value.x);
        int g = (int)(m_color.Value.y);
        int b = (int)(m_color.Value.z);

        ost << "setColor(" + std::to_string(r) + "," + std::to_string(g) + "," + std::to_string(b) + ")\n";
    }

} // namespace turtlepreter
