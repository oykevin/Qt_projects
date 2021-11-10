#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "commands.h"
#include "headers.h"
#include "mylistview.h"
#include "myitem.h"
#include "myscene.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;
    void addFiles(QStringList list);
    void createActions();
    void addMenuBar();
    void addClickMenu();
    void createClickActions();
    void createUndoStack();
    void connectSignalsAndSlots();
    void addItemMenu();
    void createUndoView();

signals:
    void createContext(QModelIndex index);

public slots:
    void openFiles();
    void showImage(QModelIndex index);
    void onListRightClick(QModelIndex index);
    void loopShow(QModelIndex index);
    void closeFiles(QModelIndex index);
    void updateTimer();
    void terminateLoop();
    void putRect();
    void putEllipse();
    void putCustom();
    void deleteItem();
    void itemMoved(QGraphicsItem *movingItem, QPointF &movePos);

private:
    Ui::MainWindow *ui;

    MyScene *scene;
    MyListView *listView;
    QStringList fileList;
    QStandardItemModel *itemModel;
    QModelIndex mainIndex;
    QGraphicsView *view;

    QAction *fileOpen;
    QAction *fileClose;
    QAction *fileLoop;
    QAction *endLoop;
    QAction *addRect;
    QAction *addEllipse;
    QAction *addCustom;
    QAction *undo;
    QAction *redo;
    QAction *del;

    QMenu *clickMenu;
    QMenu *menu;
    QMenu *subMenu;
    QMenu *subClickMenu;
    QMenu *itemMenu;

    QUndoStack *undoStack;
    QUndoCommand *addCommand;
    QUndoCommand *moveCommand;
    QUndoCommand *deleteCommand;
    QUndoView *undoView;

    QTimer *timer;
    int loopIndex = -1;

protected:
};
#endif // MAINWINDOW_H
