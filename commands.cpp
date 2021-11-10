#include "commands.h"

MoveCommand::MoveCommand(QGraphicsItem *movingItem, QGraphicsScene *scene, QPointF &movePos, QUndoCommand *parent)
    : QUndoCommand(parent){
    myItem = movingItem;
    newPos = myItem -> pos();
    oldPos = movePos;
    myScene = scene;
}

void MoveCommand::undo(){
    myItem -> setPos(oldPos);
    myScene -> update();
}

void MoveCommand::redo(){
    myItem -> setPos(newPos);
    myScene -> update();
}

DeleteCommand::DeleteCommand(QGraphicsScene *scene, QUndoCommand *parent)
    : QUndoCommand(parent){
    myScene = scene;
    QList <QGraphicsItem *> itemList = scene -> selectedItems();
    itemList.first() -> setSelected(false);
    myItem = itemList.first();
}

void DeleteCommand::undo(){
    myScene -> addItem(myItem);
    myScene -> update();
}

void DeleteCommand::redo(){
    myScene -> removeItem(myItem);
    myScene -> update();
}

AddPolygonCommand::AddPolygonCommand(QGraphicsScene *scene,
                       QUndoCommand *parent)
    : QUndoCommand(parent){
    int itemCount = 0;
    myScene = scene;
    myPolygonItem = new MyPolygonItem();
    myScene -> update();
    ++itemCount;
}

void AddPolygonCommand::undo(){
    myScene -> removeItem(myPolygonItem);
    myScene -> update();
}

void AddPolygonCommand::redo(){
    myScene -> addItem(myPolygonItem);
    myScene -> clearSelection();
    myScene -> update();
}

AddEllipseCommand::AddEllipseCommand(QGraphicsScene *scene,
                       QUndoCommand *parent)
    : QUndoCommand(parent){
    int itemCount = 0;
    myScene = scene;
    myEllipseItem = new MyEllipseItem();
    myScene -> update();
    ++itemCount;
}

void AddEllipseCommand::undo(){
    myScene -> removeItem(myEllipseItem);
    myScene -> update();
}

void AddEllipseCommand::redo(){
    myScene -> addItem(myEllipseItem);
    myScene -> clearSelection();
    myScene -> update();
}

AddCustomCommand::AddCustomCommand(QGraphicsScene *scene,
                       QUndoCommand *parent)
    : QUndoCommand(parent){
    int itemCount = 0;
    myScene = scene;
    myCustomItem = new MyCustomItem();
    myScene -> update();
    ++itemCount;
}

void AddCustomCommand::undo(){
    myScene -> removeItem(myCustomItem);
    myScene -> update();
}

void AddCustomCommand::redo(){
    myScene -> addItem(myCustomItem);
    myScene -> clearSelection();
    myScene -> update();
}

