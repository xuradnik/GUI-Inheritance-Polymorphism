#ifndef TURTLEPRETER_CONTROLLABLE_HPP
#define TURTLEPRETER_CONTROLLABLE_HPP


#include "libfriimgui/types.hpp"
#include "libfriimgui/types.hpp"
#include "libfriimgui/image.hpp"


#include <string>

namespace turtlepreter
{

    class Controllable
    {
    public:
        Controllable(const std::string &imgPath);
        Controllable(const std::string &imgPath, float centerX, float centerY);
        virtual ~Controllable() = default;

        virtual void draw(const friimgui::Region &region);
        virtual void reset();

        friimgui::Transformation &getTransformation();

    protected:
        friimgui::Transformation m_transformation;

    private:
        friimgui::Image m_image;
        ImVec2 m_initialTranslation;
    };

} // namespace turtlepreter

#endif
