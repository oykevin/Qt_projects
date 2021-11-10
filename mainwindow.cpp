#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow){

    this -> setFixedSize(1250,800);
    itemModel = new QStandardItemModel(this);
    fileList.clear();
    scene = new MyScene;
    listView = new MyListView;
    listView -> setModel(itemModel);
    listView -> resize(400,400);
    listView -> setContextMenuPolicy(Qt::CustomContextMenu);

    createUndoStack();

    //createUndoView();
    // This function is only for debug purpose.

    createActions();
    addMenuBar();
    addClickMenu();

    timer = new QTimer(this);  

    view = new QGraphicsView(scene);
    view -> resize(400,400);

    connectSignalsAndSlots();

    QSplitter *splitter = new QSplitter(this);
    splitter -> setGeometry(50,50,1150,700);
    splitter -> addWidget(listView);
    splitter -> addWidget(view);
    splitter -> setStretchFactor(0, 1);
    splitter -> setStretchFactor(1, 3);
    view -> setAlignment(Qt::AlignLeft);
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::connectSignalsAndSlots(){
    connect(listView, SIGNAL(leftClick(QModelIndex)),
            this, SLOT(showImage(QModelIndex)));
    connect(listView, SIGNAL(rightClick(QModelIndex)),
            this, SLOT(onListRightClick(QModelIndex)));

    connect(fileOpen, SIGNAL(triggered()), this, SLOT(openFiles()));
    connect(endLoop, SIGNAL(triggered()), this, SLOT(terminateLoop()));
    connect(fileClose, &QAction::triggered, this, [=](){
        closeFiles(mainIndex);
    });
    connect(fileLoop, &QAction::triggered, this, [=](){
        loopShow(mainIndex);
    });

    connect(addRect, SIGNAL(triggered()), this, SLOT(putRect()));
    connect(addEllipse, SIGNAL(triggered()), this, SLOT(putEllipse()));
    connect(addCustom, SIGNAL(triggered()), this, SLOT(putCustom()));

    connect(scene, &MyScene::itemMovedScene, this, &MainWindow::itemMoved);

    connect(del, SIGNAL(triggered()), this, SLOT(deleteItem()));
}

void MainWindow::createActions(){
    fileOpen = new QAction("Open", this);
    endLoop = new QAction("End Loop Switch", this);
    addRect = new QAction("Add Rectangle", this);
    addEllipse = new QAction("Add Ellipse");
    addCustom = new QAction("Add Custom Graph");
    undo = undoStack -> createUndoAction(this, "Undo");
    undo -> setShortcut(tr("Ctrl+Z"));
    redo = undoStack -> createRedoAction(this, "Redo");
    redo -> setShortcut(tr("Ctrl+Y"));
    del = new QAction("Delete");
    del -> setShortcut(tr("Del"));
}

void MainWindow::addMenuBar(){

    QMenuBar *menuBar = new QMenuBar(this);
    menu = new QMenu("File", this);
    QAction *appExit = new QAction("Exit", this);
    QMenu *undoCommand = new QMenu("Undo", this);
    menu -> addAction(fileOpen);
    subMenu = menu -> addMenu("Add Graphs");
    menu -> addAction(endLoop);
    menu -> addAction(appExit);

    connect(appExit, SIGNAL(triggered()), qApp, SLOT(quit()));

    subMenu -> addAction(addRect);
    subMenu -> addAction(addEllipse);
    subMenu -> addAction(addCustom);

    undoCommand -> addAction(undo);
    undoCommand -> addAction(redo);
    undoCommand -> addAction(del);

    menuBar -> addMenu(menu);
    menuBar -> addMenu(undoCommand);
}

void MainWindow::addClickMenu(){

    clickMenu = new QMenu(this);
    fileClose = new QAction("Close", this);
    fileLoop = new QAction("Start Loop Switch", this);
    clickMenu -> addAction(fileOpen);
    clickMenu -> addAction(fileClose);
    subClickMenu = clickMenu -> addMenu("Add Graphs");
    clickMenu -> addAction(fileLoop);
    clickMenu -> addAction(endLoop);

    subClickMenu -> addAction(addRect);
    subClickMenu -> addAction(addEllipse);
    subClickMenu -> addAction(addCustom);
}

void MainWindow::addItemMenu(){
    itemMenu = new QMenu(this);
    del = new QAction("Delete", this);
    itemMenu -> addAction(del);
}

void MainWindow::openFiles(){
    QStringList openFileList = QFileDialog::getOpenFileNames
            (this, tr("Open File"), "", tr("JPG (*.jpg *.jpeg);;PNG (*.png);;BMP(*.bmp)"));
    if(openFileList.length() == 0){
        return;
    }
    else{
        addFiles(openFileList);
    }
}

void MainWindow::addFiles(QStringList list){
    int prevLength = fileList.length();
    for(int i=0; i<list.length(); i++){
        qint8 flag = true;
        for(int j=0; j<prevLength; j++){
            QString existingFile = fileList[j];
            QString newFile = list[i];
            if(existingFile == newFile){
                QString curFileName = QFileInfo(newFile).fileName();
                QString showString = tr("The item : ") + curFileName + tr(" has already been added");
                QMessageBox::warning(0, "Warning!", showString);
                flag = false;
                break;
            }
        }
        if(flag){
            QStandardItem *item = new QStandardItem(QFileInfo(list[i]).fileName());
            fileList.append(list[i]);
            itemModel -> appendRow(item);
            fileList.sort();
            itemModel -> sort(0);
        }
    }
    list.clear();
}

void MainWindow::closeFiles(QModelIndex index){
    if(loopIndex != -1){
        QMessageBox::warning(0,"Warning!", "Please first end a loop!");
        return;
    }
    fileList.takeAt(index.row());
    itemModel -> removeRow(index.row());
}

void MainWindow::showImage(QModelIndex index){
    QString tempString = fileList[index.row()];
    QImage image(tempString);
    scene -> addPixmap(QPixmap::fromImage(image));
    view -> setScene(scene);
    view -> fitInView(scene -> itemsBoundingRect(), Qt::KeepAspectRatio);
}

void MainWindow::onListRightClick(QModelIndex index){
    if(listView -> selectionModel() -> selectedIndexes().empty() || !index.isValid()){
        menu -> exec(QCursor::pos());
        return;
    }
    mainIndex = index;
    clickMenu -> exec(QCursor::pos());
}

void MainWindow::loopShow(QModelIndex index){
    loopIndex = index.row();
    connect(timer, SIGNAL(timeout()), this, SLOT(updateTimer()));
    timer -> start(3000);
}

void MainWindow::terminateLoop(){
    if(loopIndex == -1){
        QMessageBox::warning(0,"Warning!", "You have not started a loop!");
        return;
    }
    timer -> stop();
    loopIndex = -1;
}

void MainWindow::updateTimer(){
    if(loopIndex == fileList.length()-1){
        loopIndex = 0;
    }
    else loopIndex++;

    QModelIndex loopModelIndex = itemModel -> index(loopIndex,0);
    listView -> clicked(loopModelIndex);
    listView -> setCurrentIndex(loopModelIndex);

    QString tempString = fileList[loopIndex];
    QImage image(tempString);
    scene -> addPixmap(QPixmap::fromImage(image));
    view -> setScene(scene);
    view -> fitInView(scene -> itemsBoundingRect(), Qt::KeepAspectRatio);
}

void MainWindow::createUndoStack(){
    undoStack = new QUndoStack(this);
}

void MainWindow::createUndoView(){
    undoView = new QUndoView(undoStack);
    undoView -> show();
}

void MainWindow::putRect(){
    addCommand = new AddPolygonCommand(scene);
    undoStack->push(addCommand);
}

void MainWindow::putEllipse(){
    addCommand = new AddEllipseCommand(scene);
    undoStack -> push(addCommand);
}

void MainWindow::putCustom(){
    addCommand = new AddCustomCommand(scene);
    undoStack -> push(addCommand);
}

void MainWindow::deleteItem(){
    if(scene -> selectedItems().isEmpty()){
        return;
    }
    deleteCommand = new DeleteCommand(scene);
    undoStack -> push(deleteCommand);
}

void MainWindow::itemMoved(QGraphicsItem *movingItem, QPointF &movePos){
    moveCommand = new MoveCommand(movingItem, scene, movePos);
    undoStack -> push(moveCommand);
}

