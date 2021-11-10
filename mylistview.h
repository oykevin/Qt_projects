#ifndef MYLISTVIEW_H
#define MYLISTVIEW_H

#include <QListView>
#include <QMouseEvent>
#include <QModelIndex>

class MyListView : public QListView{
    Q_OBJECT

public:
    explicit MyListView(QListView *parent = 0);
    ~MyListView();

signals:
    void leftClick(QModelIndex index);
    void rightClick(QModelIndex index);

protected:
    void mousePressEvent(QMouseEvent *ev) override;

};

#endif // MYLISTVIEW_H
