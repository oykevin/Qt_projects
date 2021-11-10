#include "myscene.h"
#include <QGraphicsSceneMouseEvent>


MyScene::MyScene(QGraphicsScene *parent)
    : QGraphicsScene(parent){
    movingItem = 0;
}

void MyScene::mousePressEvent(QGraphicsSceneMouseEvent *ev){
    QPointF mousePos(ev -> buttonDownScenePos(Qt::LeftButton).x(),
                     ev -> buttonDownScenePos(Qt::LeftButton).y());
    const QList <QGraphicsItem *> itemList = items(mousePos);
    if(!itemList.isEmpty()){
        movingItem = itemList.first();
    }
    if(movingItem != nullptr){
        oldPos = movingItem -> pos();
    }
    clearSelection();
    return QGraphicsScene::mousePressEvent(ev);
}

void MyScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *ev){
    if(movingItem == nullptr) return QGraphicsScene::mouseReleaseEvent(ev);
    if(movingItem -> pos() != oldPos){
        emit itemMovedScene(movingItem, oldPos);
    }
    return QGraphicsScene::mouseReleaseEvent(ev);
}
