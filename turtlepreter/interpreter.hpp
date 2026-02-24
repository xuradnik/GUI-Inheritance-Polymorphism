#ifndef TURTLEPRETER_INTERPRETER_HPP
#define TURTLEPRETER_INTERPRETER_HPP

#include "controllable.hpp"

#include <string>
#include <vector>

namespace turtlepreter
{
    class Turtle;
    class Cursor;
    class ICommand;

    // --------------------------------------------------
    // Node
    // --------------------------------------------------
    class Node
    {
    public:
        static Node *createLeafNode(ICommand *command);
        static Node *createSequentialNode();

    public:
        ~Node();

        std::string toString() const;

        void addSubnode(Node *subnode);

        Node *getParent() const;
        const std::vector<Node *> &getSubnodes() const;
        Cursor *getCursor();
        ICommand *getCommand() const;

    private:
        Node *m_parent;
        std::vector<Node *> m_subnodes;

        ICommand *m_command;
        Cursor *m_cursor;

        Node(ICommand *command, Cursor *cursor);
    };

    // --------------------------------------------------
    // ICommand
    // --------------------------------------------------
    class ICommand
    {
    public:
        virtual ~ICommand() = default;

        virtual void execute(Controllable &c) = 0;
        virtual std::string toString() = 0;

        virtual bool canBeExecuted(Controllable &c);

        void executeSafely(Controllable &c);
        virtual void log(std::ostream &ost) const = 0;
    };

    

    

    // --------------------------------------------------
    // Interpreter
    // --------------------------------------------------
    class Interpreter
    {
    public:
        Interpreter(Node *root);

        void interpretAll(Controllable &controllable);

        void interpretStep(Controllable &controllable);

        void reset();

        Node *getRoot() const;

        bool wasSomethingExecuted();
        bool isFinished();

    private:
        Node *m_root;
        Node *m_current;
        int m_exeCount;

        void resetSubtreeNodes(Node *node);
        void interpterSubtreeNodes(Node *node, Controllable &controllable);
    };

    // --------------------------------------------------
    // Cursor
    // --------------------------------------------------
    class Cursor
    {
    public:
        Cursor();
        virtual ~Cursor() = default;

        virtual Node *next() = 0;
        virtual void reset() = 0;

        virtual std::string toString() = 0;
        void setNode(Node *node);

    protected:
        Node *m_node;
    };

    // --------------------------------------------------
    // CursorUp
    // --------------------------------------------------
    class CursorUp : public Cursor
    {
    public:
        Node *next() override;
        void reset() override;
        std::string toString() override;
    };

    // --------------------------------------------------
    // SequentialCursor
    // --------------------------------------------------
    class SequentialCursor : public Cursor
    {
    public:
        SequentialCursor();

        Node *next() override;
        void reset() override;
        std::string toString() override;

    private:
        int m_currentIndex;
    };

} // namespace turtlepreter

#endif
