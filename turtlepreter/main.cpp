#include "interpreter.hpp"
#include "turtle.hpp"
#include "turtle_gui.hpp"

#include <libfriimgui/window.hpp>

#include <imgui/imgui.h>

#include <iostream>

#include "heap_monitor.hpp"

int main() {
    namespace tp = turtlepreter;

    const int cCenterX = 320;
    const int cCenterY = 320;

    friimgui::Window *window = friimgui::Window::initializeWindow(1024, 720);

    tp::Turtle turtle("turtlepreter/resources/turtle.png", cCenterX, cCenterY);

    tp::CommandJump cmdJump1(cCenterX, cCenterY - 100);
    tp::CommandSetColor cmdColor(ImColor(255, 0, 0));
    tp::CommandJump cmdJump2(cCenterX - 100, cCenterY - 100);
    tp::CommandJump cmdJump3(cCenterX - 100, cCenterY);
    tp::CommandRotate cmdRotate(1.57);

    cmdJump1.log(std::cout);
    cmdColor.log(std::cout);
    cmdJump2.log(std::cout);
    cmdJump3.log(std::cout);
    cmdRotate.log(std::cout);

    tp::Node *nodeRoot = tp::Node::createSequentialNode();
    tp::Node *nodeJump1 = tp::Node::createLeafNode(&cmdJump1);
    tp::Node *nodeColor = tp::Node::createLeafNode(&cmdColor);
    tp::Node *nodeJump2 = tp::Node::createLeafNode(&cmdJump2);
    tp::Node *nodeJump3 = tp::Node::createLeafNode(&cmdJump3);
    tp::Node *nodeRotate = tp::Node::createLeafNode(&cmdRotate);

    nodeRoot->addSubnode(nodeJump1);
    nodeRoot->addSubnode(nodeColor);
    nodeRoot->addSubnode(nodeJump2);
    nodeRoot->addSubnode(nodeJump3);
    nodeRoot->addSubnode(nodeRotate);

    tp::Interpreter interpreter(nodeRoot);
    tp::TurtleGUI turtleGUI(&turtle, &interpreter);

    window->setGUI(&turtleGUI);
    window->run();
    friimgui::Window::releaseWindow();

    if (turtle.getPathSegmentCount() ) {
        (void)turtle.getPathSegmentPoints(0);
        (void)turtle.getPathSegmentColor(0);
        turtle.setColor(ImColor(0,0,0));
    }

    delete nodeRoot;
}
