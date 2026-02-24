#include "controllable.hpp"

namespace turtlepreter
{
    Controllable::Controllable(const std::string &imgPath)
        : m_transformation(),
          m_image(friimgui::Image::createImage(imgPath))
    {
    }

    Controllable::Controllable(const std::string &imgPath, float centerX, float centerY)
        : Controllable(imgPath)
    {
        m_transformation.translation.setValue({centerX, centerY});
        m_initialTranslation = {centerX, centerY};
    }

    void Controllable::draw(const friimgui::Region &region)
    {
        m_image.draw(region, m_transformation);
    }

    void Controllable::reset()
    {
        m_transformation.reset();
        m_transformation.translation.setValue(m_initialTranslation);
        m_transformation.rotation.resetValue();
    }

    friimgui::Transformation &Controllable::getTransformation()
    {
        return m_transformation;
    }

}
