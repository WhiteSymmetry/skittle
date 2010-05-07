#include <QtGui>
#include <QScrollArea>
#include <QtGui/QScrollBar>
#include <QtGui/QCheckBox>

#include <iostream>
#include <string>

#include "MainWindow.h"
#include "FastaReader.h"
#include "GtfReader.h"
#include "glwidget.h"
#include "AbstractGraph.h"
#include "NucleotideDisplay.h"
#include "FrequencyMap.h"
#include "AnnotationDisplay.h"
#include "CylinderDisplay.h"
#include "AlignmentDisplay.h"
#include "OligomerDisplay.h"
#include "HighlightDisplay.h"
#include "ViewManager.h"

MainWindow::MainWindow()
{
	setDockOptions(QMainWindow::AllowNestedDocks|QMainWindow::AllowTabbedDocks|QMainWindow::AnimatedDocks);
	setWindowTitle( "Skittle Genome Visualizer");
	createActions();
	createMenus();
	createToolbars();
	createDocks();
	createStatusBar();
	oldScale = 1;
	createUiConnections();
	
	viewManager	= new ViewManager(this, getDisplayVariables());
	setCentralWidget(viewManager);  
	createFileConnections();

	readSettings();
	
	//openAction->trigger();
}

void MainWindow::addDisplayActions(AbstractGraph* display)
{
	if(display->actionLabel.size() > 0)
	{
		QAction* presetAction = new QAction(QString(display->actionLabel.c_str()),this);
		presetAction->setStatusTip(QString(display->actionTooltip.c_str()));
		presetAction->setData(QString(display->actionData.c_str()));
		display->toggleButton = presetAction;
		connect(presetAction,SIGNAL(triggered()),display, SLOT(toggleVisibility()));
		connect(display, SIGNAL(deleteButton(QAction*)), this, SLOT(removeButton(QAction*)));
	
		presetMenu->addAction(presetAction);
		presetToolBar->addAction(presetAction);
	}
	else
	{
		if(viewManager->activeWidget != NULL)
			viewManager->activeWidget->print("Tried to add display mode with no label, aborting...");//TODO: Move print to MainWindow
	}
}

void MainWindow::removeButton(QAction* presetAction)
{
	presetMenu->removeAction(presetAction);
	presetToolBar->removeAction(presetAction);
}

void MainWindow::addDisplayDivider()
{
	presetToolBar->addSeparator();	
}

void MainWindow::createActions()
{
	moveAction = new QAction("Move",this);	
	resizeAction = new QAction("Resize",this);	
	zoomAction = new QAction("Zoom",this);	
	selectAction = new QAction("Select",this);	
	findAction = new QAction("&Find",this);	
	addAnnotationAction = new QAction("Add Annotation",this);	
	nextAnnotationAction = new QAction("Next Annotation",this);	
	prevAnnotationAction = new QAction("Previous Annotation",this);	
	browseCommunityAction = new QAction("Browse Community Research",this);	
	delAnnotationAction = new QAction("Delete Current Bookmark",this);	
	
	/*****TODO: NOT CURRENTLY IN USE ********/
	findSequenceAction = new QAction("Find Sequence",this);	
	findSequenceAction->setStatusTip("Find Arbitrary Sequence");
	findNextAction = new QAction("Find Next", this);
	findNextAction->setStatusTip("Jump to Next Instance of Current Sequence");
	findPrevAction = new QAction("Find Previous", this);
	findPrevAction->setStatusTip("Jump to Previous Instance of Current Sequence");
	hilightResultsAction = new QAction("Highlight Results",this);
	hilightResultsAction->setStatusTip("Highlight All copies of Current Sequence");
	hilightResultsAction->setCheckable(true);
	
	addViewAction = new QAction("Add New View Panel",this);	
	
	openAction = new QAction("&Open",this);
	openAction->setStatusTip("Open a Sequence File");
	
	importAction = new QAction("&Import GTF Annotation File",this);
	importAction->setStatusTip("Open GTF / GFF Annotation File");
	
	exitAction = new QAction("E&xit",this);
	exitAction->setStatusTip("Close Program");
}

void MainWindow::createMenus()
{
	fileMenu = menuBar()->addMenu("&File");
	fileMenu->addAction(openAction);
	fileMenu->addSeparator();
	fileMenu->addAction(importAction);
	fileMenu->addAction(exitAction);
	searchMenu = menuBar()->addMenu("&Search");
	searchMenu->addAction(findSequenceAction);
	searchMenu->addAction(findNextAction);
	searchMenu->addAction(findPrevAction);
	searchMenu->addAction(hilightResultsAction);
	viewMenu = menuBar()->addMenu("&View");
	toolBarMenu = viewMenu->addMenu("ToolBar");
	presetMenu = viewMenu->addMenu("Presets");
	viewMenu->addSeparator();
	viewMenu->addAction(addViewAction);
	
	annotationMenu = menuBar()->addMenu("&Annotations");
	annotationMenu->addAction(addAnnotationAction);
	annotationMenu->addAction(nextAnnotationAction);
	annotationMenu->addAction(prevAnnotationAction);
	annotationMenu->addAction(browseCommunityAction);
	annotationMenu->addAction(delAnnotationAction);
	toolMenu = menuBar()->addMenu("&Tools");
	toolMenu->addAction(moveAction);
	toolMenu->addAction(resizeAction);
	toolMenu->addAction(zoomAction);
	toolMenu->addAction(selectAction);
	toolMenu->addAction(findAction);
	toolActionGroup = new QActionGroup(this);
	toolActionGroup->addAction(moveAction);
	toolActionGroup->addAction(resizeAction);
	toolActionGroup->addAction(zoomAction);
	toolActionGroup->addAction(selectAction);
	toolActionGroup->addAction(findAction);
	
}

void MainWindow::createToolbars()
{
	annotationToolBar = addToolBar("Annotations");
	annotationToolBar->setObjectName("annotations");
	annotationToolBar->addAction(addAnnotationAction);
	annotationToolBar->addAction(nextAnnotationAction);
	annotationToolBar->addAction(prevAnnotationAction);
	annotationToolBar->addAction(browseCommunityAction);
	annotationToolBar->addAction(delAnnotationAction);
	toolBarMenu->addAction(annotationToolBar->toggleViewAction());
	
	presetToolBar = new QToolBar("Presets");
	presetToolBar->setObjectName("presets");
	presetToolBar->setOrientation(Qt::Horizontal);
	toolBarMenu->addAction(presetToolBar->toggleViewAction());
	
	toolToolBar = addToolBar("tools");
	toolToolBar->setObjectName("tools");
	toolToolBar->addAction(moveAction);
	toolToolBar->addAction(resizeAction);
	toolToolBar->addAction(zoomAction);
	toolToolBar->addAction(selectAction);
	toolToolBar->addAction(findAction);
	toolBarMenu->addAction(toolToolBar->toggleViewAction());
	
	settingToolBar = addToolBar("Global Settings");
	settingToolBar->setObjectName("setting");

	QLabel* activeW = new QLabel("Active Window:");
	QFont boldFont = activeW->font();
	boldFont.setBold(true);
	activeW->setFont(boldFont);	
	settingToolBar->addWidget(activeW);
	settingToolBar->addSeparator();
	
	settingToolBar->addWidget(new QLabel("Display Width"));
	widthDial = new QSpinBox(this);
    widthDial->setMinimum(1);
    widthDial->setMaximum(1000000000);
    widthDial->setValue(128);
	settingToolBar->addWidget(widthDial);

	doubleDisplayWidth = new QPushButton("x2",this);
	settingToolBar->addWidget(doubleDisplayWidth);
	halveDisplayWidth = new QPushButton("/2",this);
	settingToolBar->addWidget(halveDisplayWidth);
	
	settingToolBar->addWidget(new QLabel("Scale"));
	scale = new QSpinBox(this);
    scale->setMinimum(1);
    scale->setMaximum(100000);
    scale->setValue(1);
    scale->setSingleStep(4);	
	settingToolBar->addWidget(scale);
	
	settingToolBar->addWidget(new QLabel("Zoom"));
	zoom = new QSpinBox(this);
    zoom->setMinimum(1);
    zoom->setMaximum(100000);
    zoom->setSingleStep(10);
    zoom->setValue(100);	
	settingToolBar->addWidget(zoom);
	
	settingToolBar->addWidget(new QLabel("Start"));
	startOffset = new QSpinBox(this);
    startOffset->setMinimum(1);
    startOffset->setMaximum(400000000);
    startOffset->setValue(1);
	settingToolBar->addWidget(startOffset);
	
	settingToolBar->addWidget(new QLabel("Display Length"));
	displayLength = new QSpinBox(this);
    displayLength->setMinimum(1000);
    displayLength->setMaximum(400000000);//something very large MAX_INT?
    displayLength->setSingleStep(1000);
    displayLength->setValue(10000);	
	settingToolBar->addWidget(displayLength);

	
	//settingToolBar->addSeparator();

	QLabel* multiW = new QLabel("Multiple Windows:");
	multiW->setFont(boldFont);	
	settingToolBar->addWidget(multiW);
	settingToolBar->addSeparator();
	//QActionGroup* multiGroup = new QActionGroup(this);
	syncCheckBox = new QCheckBox("Synchronize Views", this);
    syncCheckBox->setCheckState(Qt::Checked);	
	//multiGroup->addWidget(syncCheckBox);
	settingToolBar->addWidget(syncCheckBox);
	settingToolBar->addWidget( new QLabel("Offsets:"));
	
	
	toolBarMenu->addAction(settingToolBar->toggleViewAction());
	addToolBar(Qt::RightToolBarArea,presetToolBar);
	addToolBar(Qt::LeftToolBarArea,toolToolBar);
	addToolBar(Qt::LeftToolBarArea,annotationToolBar);
	addToolBar(Qt::TopToolBarArea,settingToolBar);
}

void MainWindow::createDocks()
{	
	QDockWidget *infoDock = new QDockWidget("Information Display", this);
	infoDock->setObjectName("infodock");
	toolBarMenu->addAction(infoDock->toggleViewAction());
	infoDock->setAllowedAreas(Qt::AllDockWidgetAreas);
	
	tabWidget = new QTabWidget(infoDock);
	infoDock->setWidget(tabWidget);
	textArea = new QTextEdit(tabWidget);
    tabWidget->addTab(textArea, QString("Text Output"));
	addDockWidget(Qt::BottomDockWidgetArea, infoDock);
	
	/*
	QWidget *filters = new QWidget;
	QVBoxLayout *filterLayout = new QVBoxLayout;
	QTabWidget *tabWidget = new QTabWidget();
	tabWidget->addTab(new QListWidget, "Presets");
	//tabWidget->addTab(new QTreeView, "Advanced");
	QTableWidget *propsWidget = new QTableWidget(4,3);
	
	filterLayout->addWidget(tabWidget);
	filterLayout->addWidget(propsWidget);
	filters->setLayout(filterLayout);*/
}

void MainWindow::createStatusBar()
{
	//QLabel *statusTip = new QLabel("This is a status Tip",this);
	//QProgressBar *processStatus = new QProgressBar(this);
	//processStatus->setMinimumWidth(300);
	//processStatus->setMaximumWidth(300);
	//processStatus->setValue(75);
	//QLabel *processState = new QLabel("Loading...",this);
	
	//statusBar()->addPermanentWidget(processStatus);
	//statusBar()->addPermanentWidget(processState);
	statusBar()->showMessage(tr("Ready"));
}
void MainWindow::createUiConnections()
{	/******Internal UI Logic*********/
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close())); 
    
	connect( scale, SIGNAL(valueChanged(int)), this, SLOT(changeScale(int)));
	
	connect( doubleDisplayWidth, SIGNAL(clicked()), this, SLOT(doubleWidth()));
	connect( halveDisplayWidth, SIGNAL(clicked()), this, SLOT(halveWidth()));	
}
void MainWindow::createFileConnections()
{

    connect(openAction, SIGNAL(triggered()), this, SLOT(open()));
    connect(this, SIGNAL(newFileOpen(QString)), viewManager, SLOT(changeFile(QString)));

	connect(importAction, SIGNAL(triggered()), this, SLOT(openGtf()));
	connect(this, SIGNAL(newGtfFileOpen(QString)), viewManager, SLOT(addAnnotationDisplay(QString)));	
	connect(addAnnotationAction, SIGNAL(triggered()), viewManager, SLOT(addBookmark()));
    
}

UiVariables MainWindow::getDisplayVariables()
{
	UiVariables var = UiVariables();

	var.sizeDial = displayLength;
    var.widthDial = widthDial;
    var.startDial = startOffset;
    var.scaleDial = scale;
    var.zoomDial = zoom;
    
    return var;
}

void MainWindow::open()
{
	QString fileName = QFileDialog::getOpenFileName(
		this,"Open Sequence File", 
		"", 
		"FASTA files (*.fa);; Image files (*.png *.xpm *.jpg);; Text files (*.txt);; All files (*)"
	);
	
    if (!fileName.isEmpty()) 
		 emit newFileOpen(fileName);
}

void MainWindow::open(QString fileName)
{
    if (!fileName.isEmpty()) 
		 emit newFileOpen(fileName);
}

void MainWindow::changeWindowName(std::string name)
{
	string title = "Skittle Genome Visualizer";
	title.append(name);
	setWindowTitle( "Skittle Genome Visualizer");
}

void MainWindow::openGtf()
{
	QString fileName = QFileDialog::getOpenFileName(this,"Open GTF File", "", tr("Annotation files (*.gtf);; Any files (*)"));
    
    if (!fileName.isEmpty()) 
		 emit newGtfFileOpen(fileName);
}

void MainWindow::changeScale(int newScale)
{
	if(newScale < 1)
		newScale = 1;
	
	if(oldScale != newScale)
	{
		widthDial->setSingleStep(newScale);		
		int display_width = widthDial->value() / oldScale;
		display_width = max( 1, display_width);
		int display_size = displayLength->value() / oldScale;
		display_size = max( 1, display_size);
		scale->setValue(newScale);
		widthDial->setValue( display_width * newScale );
		displayLength->setValue(display_size*newScale);
		oldScale = newScale;
	}
}

void MainWindow::doubleWidth()
{
		widthDial->setValue( 2 * widthDial->value() );
}

void MainWindow::halveWidth()
{
		widthDial->setValue( (int)(0.5 * widthDial->value()) );
}


void MainWindow::updateProgress(int val)
{
	//processStatus->setValue(val);
}
void MainWindow::updateState(QString state){
	//processState->setText(state);
}
void MainWindow::updateStatus(QString tip){
	statusBar()->showMessage(tip);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
	writeSettings();
	event->accept();
//	QMainWindow::closeEvent(event);
}

void MainWindow::readSettings()
{
	if(viewManager->activeWidget != NULL)
		viewManager->activeWidget->print("Reading User Settings");
	QSettings settings("Skittle", "Preferences");
	settings.beginGroup("mainWindow");
	restoreGeometry(settings.value("geometry").toByteArray());
	restoreState(settings.value("state").toByteArray());
	settings.endGroup();
}

void MainWindow::writeSettings()
{	
	if(viewManager->activeWidget != NULL)
		viewManager->activeWidget->print("Writing Settings");
	QSettings settings("Skittle", "Preferences");
	settings.beginGroup("mainWindow");
	settings. setValue("geometry", saveGeometry());
	settings.setValue("state", saveState());
	settings.endGroup();
}

/**********Print Functions**********/
void MainWindow::print(const char* s)
{
	textArea->append(QString(s));	
}

void MainWindow::print(std::string s)
{
	textArea->append(QString(s.c_str()));	
}

void MainWindow::printHtml(std::string s)
{
	//QTextCursor cursor = textArea->textCursor();
	//cursor.movePosition(QTextCursor::End);
	textArea->insertHtml(QString(s.c_str()));
}

void MainWindow::print(const char* s, int num)
{
	stringstream ss1;
	ss1 << s << num;

	textArea->append(QString( ss1.str().c_str() ));	
}

void MainWindow::print(int num1, int num2)
{
	stringstream ss1;
	ss1 << num1 << ", " << num2;

	textArea->append(QString( ss1.str().c_str() ));	
}

