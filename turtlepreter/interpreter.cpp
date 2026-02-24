#include "interpreter.hpp"
#include "perk.hpp"
#include "turtle.hpp"

#include <iostream>
#include <stdexcept>

#include "heap_monitor.hpp"

namespace turtlepreter
{

    // --------------------------------------------------
    // Node
    // --------------------------------------------------
    Node *Node::createLeafNode(ICommand *command)
    {
        Cursor *cursor = new CursorUp();
        Node *resultNode = new Node(command, cursor);
        cursor->setNode(resultNode);

        return resultNode;
    }

    Node *Node::createSequentialNode()
    {
        Cursor *cursor = new SequentialCursor();
        Node *resultNode = new Node(nullptr, cursor);
        cursor->setNode(resultNode);

        return resultNode;
    }

    Node::Node(ICommand *command, Cursor *cursor)
        : m_parent(nullptr),
          m_subnodes(),
          m_command(command),
          m_cursor(cursor)
    {
    }

    Node::~Node()
    {
        for (Node *sub : m_subnodes)
        {
            delete sub;
        }
        delete m_cursor;
    }

    void Node::addSubnode(Node *subnode)
    {
        if (!subnode)
        {
            return;
        }
        subnode->m_parent = this;
        m_subnodes.push_back(subnode);
    }

    Node *Node::getParent() const
    {
        return m_parent;
    }

    const std::vector<Node *> &Node::getSubnodes() const
    {
        return m_subnodes;
    }

    ICommand *Node::getCommand() const
    {
        return m_command;
    }

    Cursor *Node::getCursor()
    {
        return m_cursor;
    }

    std::string Node::toString() const
    {
        std::string result;

        if (m_command != nullptr)
        {
            result = "Command: " + m_command->toString();
        }
        else
        {
            result = "No command";
        }
        if (m_cursor != nullptr)
        {
            result += " " + m_cursor->toString();
        }
        return result;
    }

    // --------------------------------------------------
    // Cursor
    // --------------------------------------------------
    Cursor::Cursor()
        : m_node(nullptr)
    {
    }

    void Cursor::setNode(Node *node)
    {
        m_node = node;
    }

    // --------------------------------------------------
    // CursorUp
    // --------------------------------------------------
    Node *CursorUp::next()
    {
        return m_node->getParent();
    }

    void CursorUp::reset()
    {
    }

    std::string CursorUp::toString()
    {
        return "Cursor: Up";
    }

    // --------------------------------------------------
    // SequentialCursor
    // --------------------------------------------------
    SequentialCursor::SequentialCursor()
        : m_currentIndex(0)
    {
    }

    Node *SequentialCursor::next()
    {
        const std::vector<Node *> &sons = m_node->getSubnodes();
        if (static_cast<std::size_t>(m_currentIndex) == sons.size())
        {
            return m_node->getParent();
        }
        else
        {
            return sons[m_currentIndex++];
        }
    }

    void SequentialCursor::reset()
    {
        m_currentIndex = 0;
    }

    std::string SequentialCursor::toString()
    {
        std::size_t size = m_node->getSubnodes().size();
        const std::vector<Node *> &sons = m_node->getSubnodes();

        /*
        if (static_cast<std::size_t>(m_currentIndex) == sons.size())
        {
            return "Cursor: Up";
        }
        else
        {
            return "Son " + std::to_string(m_currentIndex + 1) + "/" + std::to_string(size);
        }
        */

        return "Cursor: Up";
    }

    // --------------------------------------------------
    // Interpreter
    // --------------------------------------------------
    Interpreter::Interpreter(Node *root)
        : m_root(root),
          m_current(root),
          m_exeCount(0)
    {
    }

    void Interpreter::interpretAll(Controllable &controllable)
    {
        while (m_current != nullptr)
        {
            interpretStep(controllable);
        }
    }

    void Interpreter::interpretStep(Controllable &controllable)
    {
        if (m_current == nullptr)
        {
            return;
        }

        while (m_current && m_current->getCommand() == nullptr)
        {
            m_current = m_current->getCursor()->next();
        }

        if (m_current == nullptr)
        {
            return;
        }

        if (ICommand *command = m_current->getCommand())
        {
            command->executeSafely(controllable);
            ++m_exeCount;
        }

        m_current = m_current->getCursor()->next();
    }

    Node *Interpreter::getRoot() const
    {
        return m_root;
    }

    void Interpreter::reset()
    {
        m_current = m_root;
        resetSubtreeNodes(m_root);
        m_exeCount = 0;
    }

    void Interpreter::interpterSubtreeNodes(Node *node, Controllable &controllable)
    {
        if (ICommand *command = node->getCommand())
        {
            command->execute(controllable);
        }

        for (Node *subnode : node->getSubnodes())
        {
            interpterSubtreeNodes(subnode, controllable);
        }
    }

    void Interpreter::resetSubtreeNodes(Node *node)
    {
        node->getCursor()->reset();

        for (Node *subnode : node->getSubnodes())
        {
            resetSubtreeNodes(subnode);
        }
    }

    bool Interpreter::wasSomethingExecuted()
    {
        return m_exeCount > 0;
    }

    bool Interpreter::isFinished()
    {
        return m_current == nullptr;
    }

    // --------------------------------------------------
    // ICommand
    // --------------------------------------------------
    bool ICommand::canBeExecuted(Controllable &c)
    {
        return true;
    }

    void ICommand::executeSafely(Controllable &c)
    {
        if (canBeExecuted(c))
        {
            execute(c);
        }
        else
        {
            std::cout << "Can not execute command" << std::endl;
        }
    }

} // namespace turtlepreter
