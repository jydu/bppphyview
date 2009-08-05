#include "PhyView.h"

#include <QApplication>
#include <QtGui>

#include <Bpp/Qt/QtGraphicDevice.h>

#include <Phyl/trees>
#include <Phyl/iotree>
#include <Phyl/PhylogramPlot.h>

using namespace bpp;
    

PhyView::PhyView()
{
  setAttribute(Qt::WA_DeleteOnClose);
  createActions_();
  createMenus_();
  createStatusBar_();
  treePanel_ = new TreeCanvas;
  treePanel_->setTreeDrawing(new PhylogramPlot());
  treePanel_->setMinimumSize(400,400);
  treePanelScrollArea_ = new QScrollArea;
  treePanelScrollArea_->setWidget(treePanel_);

  controlPanel_ = new QWidget(this);
  treeControlers_ = new TreeCanvasControlers(treePanel_);
  
  QGroupBox* drawingOptions = new QGroupBox;
  drawingOptions->setTitle(tr("Drawing"));
  QVBoxLayout* drawingLayout = new QVBoxLayout;
  drawingLayout->addWidget(treeControlers_->getControlerById(TreeCanvasControlers::ID_DRAWING_CTRL));
  drawingLayout->addWidget(treeControlers_->getControlerById(TreeCanvasControlers::ID_ORIENTATION_CTRL));
  drawingLayout->addWidget(treeControlers_->getControlerById(TreeCanvasControlers::ID_WIDTH_CTRL));
  drawingLayout->addWidget(treeControlers_->getControlerById(TreeCanvasControlers::ID_HEIGHT_CTRL));
  drawingOptions->setLayout(drawingLayout);

  QGroupBox* displayOptions = new QGroupBox;
  displayOptions->setTitle(tr("Display"));
  QVBoxLayout* displayLayout = new QVBoxLayout;
  displayLayout->addWidget(treeControlers_->getControlerById(TreeCanvasControlers::ID_DRAW_NODES_ID_CTRL));
  displayLayout->addWidget(treeControlers_->getControlerById(TreeCanvasControlers::ID_DRAW_BRLEN_VALUES_CTRL));
  displayLayout->addWidget(treeControlers_->getControlerById(TreeCanvasControlers::ID_DRAW_BOOTSTRAP_VALUES_CTRL));
  displayOptions->setLayout(displayLayout);
  
  QVBoxLayout* layout = new QVBoxLayout;
  layout->addWidget(drawingOptions);
  layout->addWidget(displayOptions);
  layout->addStretch(1);
  controlPanel_->setLayout(layout);

  setCentralWidget(treePanelScrollArea_);
  QDockWidget* controlsDockWidget = new QDockWidget(tr("Drawing"));
  controlsDockWidget->setWidget(controlPanel_);
  controlsDockWidget->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
  addDockWidget(Qt::RightDockWidgetArea, controlsDockWidget);
  fileDialog_ = new QFileDialog(this, "Tree File");

  resize(600, 400);
}




void PhyView::createActions_()
{
  openAction_ = new QAction(tr("&Open"), this);
  openAction_->setShortcut(tr("Ctrl+O"));
  openAction_->setStatusTip(tr("Open a new tree file"));
  connect(openAction_, SIGNAL(triggered()), this, SLOT(open()));

  saveAction_ = new QAction(tr("&Save"), this);
  saveAction_->setShortcut(tr("Ctrl+S"));
  saveAction_->setStatusTip(tr("Save the current tree to file"));
  connect(saveAction_, SIGNAL(triggered()), this, SLOT(save()));

  closeAction_ = new QAction(tr("&Close"), this);
  closeAction_->setShortcut(tr("Ctrl+W"));
  closeAction_->setStatusTip(tr("Close the current tree plot."));
  connect(closeAction_, SIGNAL(triggered()), this, SLOT(close()));

  exitAction_ = new QAction(tr("&Quit"), this);
  exitAction_->setShortcut(tr("Ctrl+Q"));
  exitAction_->setStatusTip(tr("Quit PhyView"));
  connect(exitAction_, SIGNAL(triggered()), this, SLOT(exit()));

  aboutQtAction_ = new QAction(tr("About Qt"), this);
  connect(aboutQtAction_, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}




void PhyView::createMenus_()
{
  fileMenu_ = menuBar()->addMenu(tr("&File"));
  fileMenu_->addAction(openAction_);
  fileMenu_->addAction(saveAction_);
  fileMenu_->addAction(closeAction_);
  fileMenu_->addAction(exitAction_);
  
  helpMenu_ = menuBar()->addMenu(tr("&Help"));
  helpMenu_->addAction(aboutQtAction_);
}




void PhyView::createStatusBar_()
{
  updateStatusBar();
}


void PhyView::closeEvent(QCloseEvent* event)
{

}



void PhyView::open()
{
  QString path = fileDialog_->getOpenFileName();
  cout << "Opening file: " << path.toStdString() << endl;
  Newick treeReader;
  Tree* tree = treeReader.read(path.toStdString());
  
  if (treePanel_->getTreeDrawing()->hasTree())
    delete treePanel_->getTreeDrawing()->getTree();
  treePanel_->setTree(tree);
  treeControlers_->actualizeOptions();
}

bool PhyView::save()
{
}

bool PhyView::saveAs()
{
}

void PhyView::close()
{
}

void PhyView::exit()
{
}

void PhyView::about()
{
}

void PhyView::updateStatusBar()
{
}


int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

//  MyWidget hello;
//  Tree* tree = TreeTemplateTools::parenthesisToTree("((A:1,B:1):1,C:2);");
//  TreeDrawing* td  = new PhylogramPlot(tree);
//  hello.setTreeDrawing(td);
//  hello.show();
  PhyView* phyview = new PhyView();
  phyview->show();

  return app.exec();
}


