#ifndef MYITEM_H
#define MYITEM_H

#include <QGraphicsItem>
#include <QGraphicsPolygonItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsScene>
#include <QPointF>

class MyPolygonItem : public QGraphicsPolygonItem{
public:
    explicit MyPolygonItem(QGraphicsItem *parent = 0);

private:
    QPolygonF rect;
};

class MyEllipseItem : public QGraphicsEllipseItem{
public:

    explicit MyEllipseItem(QGraphicsItem *parent = 0);

private:
    QGraphicsEllipseItem ellipse;
};

class MyCustomItem : public QGraphicsPathItem{
public:
    explicit MyCustomItem(QGraphicsItem *parent = 0);

private:
    QGraphicsPathItem custom;
};
#endif // MYITEM_H
