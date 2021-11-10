#ifndef COMMANDS_H
#define COMMANDS_H

#include "headers.h"
#include "myitem.h"
#include "myscene.h"

class MoveCommand : public QUndoCommand{
public:
    MoveCommand(QGraphicsItem *myItem, QGraphicsScene *myScene, QPointF &movePos, QUndoCommand *parent = 0);

    void undo() override;
    void redo() override;

private:
    QGraphicsItem *myItem;
    QPointF oldPos;
    QPointF newPos;
    QGraphicsScene *myScene;
};

class DeleteCommand : public QUndoCommand{
public:
    DeleteCommand(QGraphicsScene *scene, QUndoCommand *parent = 0);

    void undo() override;
    void redo() override;

private:
    QGraphicsItem *myItem;
    QGraphicsScene *myScene;
};

class AddPolygonCommand : public QUndoCommand{
public:
    AddPolygonCommand(QGraphicsScene *scene,
               QUndoCommand *parent = 0);

    void undo() override;
    void redo() override;

private:
    MyPolygonItem *myPolygonItem;
    QGraphicsScene *myScene;
};

class AddEllipseCommand : public QUndoCommand{
public:
    AddEllipseCommand(QGraphicsScene *scene,
               QUndoCommand *parent = 0);

    void undo() override;
    void redo() override;

private:
    MyEllipseItem *myEllipseItem;
    QGraphicsScene *myScene;
};

class AddCustomCommand : public QUndoCommand{
public:
    AddCustomCommand(QGraphicsScene *scene,
               QUndoCommand *parent = 0);

    void undo() override;
    void redo() override;

private:
    MyCustomItem *myCustomItem;
    QGraphicsScene *myScene;
};

#endif // COMMANDS_H
