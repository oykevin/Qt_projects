#ifndef MYSCENE_H
#define MYSCENE_H
#include "headers.h"
#include <QGraphicsScene>
#include "myitem.h"

class MyScene : public QGraphicsScene{
    Q_OBJECT
public:
    explicit MyScene(QGraphicsScene *parent = 0);

signals:
    void itemMovedScene(QGraphicsItem *movingItem, QPointF &movePos);
    void itemShow(QGraphicsItem *movingItem);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *ev) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *ev) override;

private:
    QPointF oldPos;
    QPointF newPos;
    QGraphicsItem *movingItem;
};

#endif // MYSCENE_H
