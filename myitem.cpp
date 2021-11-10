#include "myitem.h"
#include <QRandomGenerator>
#include <QPainterPath>
#include <QtMath>

MyPolygonItem::MyPolygonItem(QGraphicsItem *parent)
    : QGraphicsPolygonItem(parent){

    int sideLength = 100 + QRandomGenerator::global() -> bounded(300);

    rect << QPointF(200, 200) << QPointF(200 + sideLength, 200)
                      << QPointF(200 + sideLength, 200 + sideLength) << QPointF(200, 200 + sideLength)
                      << QPointF(200, 200);

    QColor color(QRandomGenerator::global()->bounded(256),
                 QRandomGenerator::global()->bounded(256), QRandomGenerator::global()->bounded(256));
    QBrush brush(color);
    setBrush(brush);
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemIsMovable);
    setPolygon(rect);
}

MyEllipseItem::MyEllipseItem(QGraphicsItem *parent)
    : QGraphicsEllipseItem(parent){

    int length = 100 + QRandomGenerator::global() -> bounded(300);
    int width = 50 + QRandomGenerator::global() -> bounded(150);

    QColor color(QRandomGenerator::global() -> bounded(256),
                 QRandomGenerator::global() -> bounded(256), QRandomGenerator::global() -> bounded(256));
    QBrush brush(color);
    setBrush(brush);
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemIsMovable);
    setRect(QRectF(50, 50, length, width));
}

MyCustomItem::MyCustomItem(QGraphicsItem *parent)
    : QGraphicsPathItem(parent){

    QColor color(QRandomGenerator::global()->bounded(256),
                 QRandomGenerator::global()->bounded(256), QRandomGenerator::global()->bounded(256));
    QBrush brush(color);
    setBrush(brush);
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemIsMovable);

    QPainterPath customPath;
    customPath.moveTo(90, 50);
    for (int i = 1; i < 5; ++i) {
        customPath.lineTo(50 + 40 * std::cos(0.8 * i * M_PI),
                        50 + 40 * std::sin(0.8 * i * M_PI));
    }
    customPath.closeSubpath();
    setPath(customPath);
}

