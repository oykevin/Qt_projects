#include "mylistview.h"
#include <QMouseEvent>

MyListView::MyListView(QListView *parent)
    : QListView(parent){

}

MyListView::~MyListView(){

}

void MyListView::mousePressEvent(QMouseEvent *ev){
    QListView::mousePressEvent(ev);
    QModelIndex index = currentIndex();
    if(ev -> button() == Qt::RightButton){
        emit rightClick(index);
    }
    else{
        if(!this -> selectionModel() -> selectedIndexes().empty()){
        emit leftClick(index);
        }
        else{
            return QListView::mousePressEvent(ev);
        }
    }
}
