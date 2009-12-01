/********************************************************************************
** This file is derived from a file generated by Qt Designer.  However, it now 
** uses a custom border layout so it will not be overridden.
**
** Form generated from reading ui file 'QtSkittle.ui'
**
********************************************************************************/

#ifndef UI_QTSKITTLE_H
#define UI_QTSKITTLE_H

#include <string>
#include <sstream>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QScrollArea>
#include <QtGui/QScrollBar>
#include <QtGui/QSlider>
#include <QtGui/QSpinBox>
#include <QtGui/QStatusBar>
#include <QtGui/QToolButton>
#include <QtGui/QTextBrowser>
#include <QtGui/QWidget>
#include "glwidget.h"
#include "BorderLayout.h"

QT_BEGIN_NAMESPACE

using std::stringstream;

class Ui_SkittleGUI
{
public:
	string chromosomeName;
    /*QAction *actionNucleotide_Display;
    QAction *actionFrequency_Map;
    QAction *actionSkittle_Website;
    QAction *actionReset_View;*/
    QAction *actionOpen;
    QAction *actionOpenGTF;
    QAction *actionExit;
    QWidget *centralwidget;
    BorderLayout* layout;
    BorderLayout* sidebar;
    BorderLayout* toolBar;
    QScrollArea *toolBox;
    QToolButton *moveButton;
    QToolButton *selectButton;
    QToolButton *resizeButton;
    QToolButton *bookmarkButton;
    GLWidget* glWidget;
    QScrollBar* verticalScrollBar;
    QScrollBar* horizontalScrollBar;
    QLabel *label;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QPushButton *cylinderButton;
    QPushButton *nucButton;
    QPushButton *alignButton;
    QPushButton *freqButton;
    
    QGroupBox *sizeBox;
    QSpinBox *sizeDial;
    QGroupBox *widthBox;
    QSpinBox *widthDial;
    QPushButton *widthX2Button;
    QPushButton *widthDiv2Button;
    QGroupBox *startBox;
    QSpinBox *startDial;
    QGroupBox *scaleBox;
    QSpinBox *scaleDial;    
    QGroupBox *zoomBox;
    QSpinBox *zoomDial;
    
    QCheckBox *textureCheckBox;
    //QCheckBox *widthLock;
    
    QTextBrowser* textArea;
    QMenuBar *menubar;
    QMenu *menuFile;
    //QMenu *menuView;
    //QMenu *menuWindows;
    //QMenu *menuHelp;
    QStatusBar *statusbar;

void setupUi(QMainWindow *SkittleGUI)
{
    if (SkittleGUI->objectName().isEmpty())
        SkittleGUI->setObjectName(QString::fromUtf8("SkittleGUI"));
    SkittleGUI->resize(936, 610);
    /*actionNucleotide_Display = new QAction(SkittleGUI);
    actionNucleotide_Display->setObjectName(QString::fromUtf8("actionNucleotide_Display"));
    actionFrequency_Map = new QAction(SkittleGUI);
    actionFrequency_Map->setObjectName(QString::fromUtf8("actionFrequency_Map"));
    actionSkittle_Website = new QAction(SkittleGUI);
    actionSkittle_Website->setObjectName(QString::fromUtf8("actionSkittle_Website"));
    actionReset_View = new QAction(SkittleGUI);
    actionReset_View->setObjectName(QString::fromUtf8("actionReset_View"));
    */
    actionOpen = new QAction(SkittleGUI);
    actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
    actionOpenGTF = new QAction(SkittleGUI);
    actionOpenGTF->setObjectName(QString::fromUtf8("actionOpenGTF"));
    actionExit = new QAction(SkittleGUI);
    actionExit->setObjectName(QString::fromUtf8("actionExit"));
    centralwidget = new QWidget(SkittleGUI);
    centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
    centralwidget->setSizeIncrement(QSize(100, 100));
    
    layout = new BorderLayout(centralwidget);
    //gridLayout = new QGridLayout(centralwidget);
    //gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    
    toolBox = new QScrollArea(centralwidget);
    toolBox->setObjectName(QString::fromUtf8("toolBox"));
    toolBox->setMinimumSize(QSize(80, 400));
    toolBox->setMaximumSize(QSize(80, 16777215));
    toolBar = new BorderLayout(toolBox);
    moveButton = new QToolButton(toolBox);
    moveButton->setObjectName(QString::fromUtf8("moveButton"));
    int toolWidth = 78;
    moveButton->setMinimumSize(QSize(toolWidth, 20));
    moveButton->raise();
   		toolBar->addWidget(moveButton, BorderLayout::North);
    selectButton = new QToolButton(toolBox);
    selectButton->setObjectName(QString::fromUtf8("selectButton"));
    selectButton->setMinimumSize(QSize(toolWidth, 20));
    selectButton->raise();
	    toolBar->addWidget(selectButton, BorderLayout::North);
    resizeButton = new QToolButton(toolBox);
    resizeButton->setObjectName(QString::fromUtf8("resizeButton"));
    resizeButton->setMinimumSize(QSize(toolWidth, 20));
    resizeButton->raise();
	    toolBar->addWidget(resizeButton, BorderLayout::North);
    bookmarkButton = new QToolButton(toolBox);
    bookmarkButton->setObjectName(QString::fromUtf8("bookmarkButton"));
    bookmarkButton->setMinimumSize(QSize(toolWidth, 20));
    bookmarkButton->raise();
	    toolBar->addWidget(bookmarkButton, BorderLayout::North);    
    
	layout->addWidget(toolBox, BorderLayout::West);
    
    scrollArea = new QScrollArea(centralwidget);
    sidebar = new BorderLayout(scrollArea);
    scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
    scrollArea->setMinimumSize(QSize(120, 300));
    scrollArea->setMaximumSize(QSize(120, 16777215));
    scrollArea->setWidgetResizable(true);
    scrollAreaWidgetContents = new QWidget();
    scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
    scrollAreaWidgetContents->setGeometry(QRect(0, 0, 118, 550));
    
    cylinderButton = new QPushButton(scrollAreaWidgetContents);
    cylinderButton->setObjectName(QString::fromUtf8("cylinderButton"));
    cylinderButton->setMinimumSize(QSize(110, 23));
    sidebar->addWidget(cylinderButton, BorderLayout::North);
    
    nucButton = new QPushButton(scrollAreaWidgetContents);
    nucButton->setObjectName(QString::fromUtf8("nucButton"));
    nucButton->setMinimumSize(QSize(110, 23));
    sidebar->addWidget(nucButton, BorderLayout::North);
    
    alignButton = new QPushButton(scrollAreaWidgetContents);
    alignButton->setObjectName(QString::fromUtf8("alignButton"));
    alignButton->setMinimumSize(QSize(110, 23));
    sidebar->addWidget(alignButton, BorderLayout::North);
    
    freqButton = new QPushButton(scrollAreaWidgetContents);
    freqButton->setObjectName(QString::fromUtf8("freqButton"));
    freqButton->setMinimumSize(QSize(110, 23));
    sidebar->addWidget(freqButton, BorderLayout::North);
    
    QFont font;
    font.setPointSize(12);

    sizeBox = new QGroupBox(scrollAreaWidgetContents);
    sizeBox->setObjectName(QString::fromUtf8("sizeBox"));
//    sizeBox->setGeometry(QRect(10, 433, 101, 41));
    sizeBox->setMinimumSize(QSize(101, 41));
    //sizeBox->hide();
    sizeDial = new QSpinBox(sizeBox);
    sizeDial->setObjectName(QString::fromUtf8("sizeDial"));
    sizeDial->setGeometry(QRect(11, 15, 100, 20));
    sizeDial->setFont(font);
    sizeDial->setMinimum(1000);
    sizeDial->setMaximum(400000000);//something very large MAX_INT?
    sizeDial->setSingleStep(1);
    sizeDial->setValue(50000);
    sizeDial->setButtonSymbols( QAbstractSpinBox::NoButtons );
	sizeDial->setMouseTracking(false);
	sizeDial->setFocusPolicy(Qt::NoFocus);
	sizeDial->setKeyboardTracking(false);
    //sizeDial->hide();
    sidebar->addWidget(sizeBox, BorderLayout::South);
	    
    startBox = new QGroupBox(scrollAreaWidgetContents);
    startBox->setObjectName(QString::fromUtf8("startBox"));
    startBox->setMinimumSize(QSize(101, 41));
    startDial = new QSpinBox(startBox);
    startDial->setObjectName(QString::fromUtf8("startDial"));
    startDial->setGeometry(QRect(11, 15, 81, 20));
    startDial->setFont(font);
    startDial->setMinimum(1);
    startDial->setMaximum(400000000);
    startDial->setValue(1);
    sidebar->addWidget(startBox, BorderLayout::South);

    zoomBox = new QGroupBox(scrollAreaWidgetContents);
    zoomBox->setObjectName(QString::fromUtf8("zoomBox"));
    zoomBox->setMinimumSize(QSize(101, 41));
    zoomDial = new QSpinBox(zoomBox);
    zoomDial->setObjectName(QString::fromUtf8("zoomDial"));
    zoomDial->setGeometry(QRect(11, 15, 81, 20));
    zoomDial->setFont(font);
    zoomDial->setMinimum(1);
    zoomDial->setMaximum(100000);
    zoomDial->setSingleStep(10);
    zoomDial->setValue(100);
    sidebar->addWidget(zoomBox, BorderLayout::South);
    scrollArea->setWidget(scrollAreaWidgetContents);
    
    scaleBox = new QGroupBox(scrollAreaWidgetContents);
    scaleBox->setObjectName(QString::fromUtf8("scaleBox"));
    scaleBox->setMinimumSize(QSize(101, 41));
    scaleDial = new QSpinBox(scaleBox);
    scaleDial->setObjectName(QString::fromUtf8("scaleDial"));
    scaleDial->setGeometry(QRect(11, 15, 81, 20));
    scaleDial->setFont(font);
    scaleDial->setMinimum(1);
    scaleDial->setMaximum(100000);
    scaleDial->setValue(1);
    scaleDial->setSingleStep(4);
    sidebar->addWidget(scaleBox, BorderLayout::South);

	/*widthLock = new QCheckBox(scrollAreaWidgetContents);
    widthLock->setObjectName(QString::fromUtf8("widthLock"));
    widthLock->setMinimumSize(QSize(112, 18));
    widthLock->setChecked(false);
    sidebar->addWidget(widthLock, BorderLayout::South);*/

    widthBox = new QGroupBox(scrollAreaWidgetContents);
    widthBox->setObjectName(QString::fromUtf8("widthBox"));
    widthBox->setMinimumSize(QSize(101, 41));
    widthDial = new QSpinBox(widthBox);
    widthDial->setObjectName(QString::fromUtf8("widthDial"));
    widthDial->setGeometry(QRect(11, 15, 81, 20));
    widthDial->setFont(font);
    widthDial->setMinimum(1);
    widthDial->setMaximum(1000000000);
    widthDial->setValue(250);
    
    widthX2Button = new QPushButton(widthBox);
    widthX2Button->setObjectName(QString::fromUtf8("widthX2Button"));
    widthX2Button->setGeometry(QRect(92, 9, 24, 16));
    widthDiv2Button = new QPushButton(widthBox);
    widthDiv2Button->setObjectName(QString::fromUtf8("widthDiv2Button"));
    widthDiv2Button->setGeometry(QRect(92, 25, 24, 16));
    
    sidebar->addWidget(widthBox, BorderLayout::South);
    
    
    textureCheckBox = new QCheckBox(scrollAreaWidgetContents);
    textureCheckBox->setObjectName(QString::fromUtf8("textureCheckBox"));
    textureCheckBox->setMinimumSize(QSize(112, 18));
    textureCheckBox->setChecked(true);
    textureCheckBox->hide();
    sidebar->addWidget(textureCheckBox, BorderLayout::South);

        
	layout->addWidget(scrollArea, BorderLayout::East);
    
    textArea = new QTextBrowser(centralwidget);
    QFont textFont("Courier New", 8);
    textArea->setCurrentFont( textFont );
    textArea->setText("Thank you for using the Skittle Genome Visualizer.  Open any FASTA file using the menu bar: File > Open...");
    textArea->setMinimumHeight(80);
    textArea->setMaximumHeight(80);
    textArea->setOpenExternalLinks(true);
	layout->addWidget(textArea, BorderLayout::South);

    SkittleGUI->setCentralWidget(centralwidget);
    scrollArea->raise();
    menubar = new QMenuBar(SkittleGUI);
    menubar->setObjectName(QString::fromUtf8("menubar"));
    menubar->setGeometry(QRect(0, 0, 936, 21));
    menuFile = new QMenu(menubar);
    menuFile->setObjectName(QString::fromUtf8("menuFile"));
    /*menuView = new QMenu(menubar);
    menuView->setObjectName(QString::fromUtf8("menuView"));
    menuWindows = new QMenu(menubar);
    menuWindows->setObjectName(QString::fromUtf8("menuWindows"));
    menuHelp = new QMenu(menubar);
    menuHelp->setObjectName(QString::fromUtf8("menuHelp"));*/
    SkittleGUI->setMenuBar(menubar);
    statusbar = new QStatusBar(SkittleGUI);
    statusbar->setObjectName(QString::fromUtf8("statusbar"));
    SkittleGUI->setStatusBar(statusbar);

    menubar->addAction(menuFile->menuAction());
    //menubar->addAction(menuView->menuAction());
    //menubar->addAction(menuWindows->menuAction());
    //menubar->addAction(menuHelp->menuAction());
    menuFile->addAction(actionOpen);
    menuFile->addAction(actionOpenGTF);
    menuFile->addAction(actionExit);
    //menuView->addAction(actionReset_View);
    //menuWindows->addAction(actionNucleotide_Display);
    //menuWindows->addAction(actionFrequency_Map);
    //menuHelp->addAction(actionSkittle_Website);

    
    verticalScrollBar = new QScrollBar(centralwidget);
    verticalScrollBar->setObjectName(QString::fromUtf8("verticalScrollBar"));
    verticalScrollBar->setMaximum (100000);
    verticalScrollBar->setPageStep(1000000);
    verticalScrollBar->setSingleStep(1000);
    verticalScrollBar->setOrientation(Qt::Vertical);

	layout->addWidget(verticalScrollBar, BorderLayout::East);
	
	horizontalScrollBar = new QScrollBar(centralwidget);
    horizontalScrollBar->setObjectName(QString::fromUtf8("horizontalScrollBar"));
    horizontalScrollBar->setMaximum (50);
    horizontalScrollBar->setPageStep(100);
    horizontalScrollBar->setSingleStep(10);
    horizontalScrollBar->setOrientation(Qt::Horizontal);

	layout->addWidget(horizontalScrollBar, BorderLayout::South);
	
	/** IMPORTANT: glWidget MUST be instantiated last because the constructor calls the ui ***/
    glWidget = new GLWidget(this, centralwidget);
    glWidget->setObjectName(QString::fromUtf8("glWidget"));
    glWidget->setEnabled(true);
    glWidget->setMinimumSize(QSize(200, 400));
    glWidget->setSizeIncrement(QSize(0, 0));
    glWidget->setMouseTracking(true);
    glWidget->setFocusPolicy(Qt::ClickFocus);
    glWidget->setAutoFillBackground(true);

	layout->addWidget(glWidget, BorderLayout::Center);
	
	QObject::connect(horizontalScrollBar, SIGNAL(valueChanged(int)), glWidget, SLOT(slideHorizontal(int)));
	//QObject::connect(glWidget, SIGNAL(totalWidthChange(int)), horizontalScrollBar, SLOT(setMaximum(int)));
	QObject::connect(glWidget, SIGNAL(xOffsetChange(int)), horizontalScrollBar, SLOT(setValue(int)));

	
	QObject::connect(verticalScrollBar, SIGNAL(valueChanged(int)), startDial, SLOT(setValue(int)));
	QObject::connect(startDial, SIGNAL(valueChanged(int)), verticalScrollBar, SLOT(setValue(int)));
	
    retranslateUi(SkittleGUI);

    QMetaObject::connectSlotsByName(SkittleGUI);
    

} // setupUi

void retranslateUi(QMainWindow *SkittleGUI)
{
    SkittleGUI->setWindowTitle(QApplication::translate("SkittleGUI", "Skittle", 0, QApplication::UnicodeUTF8));
    /*
	actionNucleotide_Display->setText(QApplication::translate("SkittleGUI", "Nucleotide Display", 0, QApplication::UnicodeUTF8));
    actionFrequency_Map->setText(QApplication::translate("SkittleGUI", "Frequency Map", 0, QApplication::UnicodeUTF8));
    actionSkittle_Website->setText(QApplication::translate("SkittleGUI", "Skittle Website", 0, QApplication::UnicodeUTF8));
    actionReset_View->setText(QApplication::translate("SkittleGUI", "Reset View", 0, QApplication::UnicodeUTF8));
    */
	actionOpen->setText(QApplication::translate("SkittleGUI", "Open...", 0, QApplication::UnicodeUTF8));
    actionOpenGTF->setText(QApplication::translate("SkittleGUI", "Open GTF File", 0, QApplication::UnicodeUTF8));
    actionExit->setText(QApplication::translate("SkittleGUI", "Exit", 0, QApplication::UnicodeUTF8));
    //toolBox->setTitle(QApplication::translate("SkittleGUI", "Tools", 0, QApplication::UnicodeUTF8));
    moveButton->setText(QApplication::translate("SkittleGUI", "Move", 0, QApplication::UnicodeUTF8));
    selectButton->setText(QApplication::translate("SkittleGUI", "Select", 0, QApplication::UnicodeUTF8));
    resizeButton->setText(QApplication::translate("SkittleGUI", "Resize", 0, QApplication::UnicodeUTF8));
    bookmarkButton->setText(QApplication::translate("SkittleGUI", "Add Bookmark", 0, QApplication::UnicodeUTF8));
    
    zoomBox->setTitle(QApplication::translate("SkittleGUI", "Zoom", 0, QApplication::UnicodeUTF8));
    scaleBox->setTitle(QApplication::translate("SkittleGUI", "Scale", 0, QApplication::UnicodeUTF8));
    nucButton->setText(QApplication::translate("SkittleGUI", "Nucleotide", 0, QApplication::UnicodeUTF8));
    freqButton->setText(QApplication::translate("SkittleGUI", "Repeat Map", 0, QApplication::UnicodeUTF8));
    alignButton->setText(QApplication::translate("SkittleGUI", "Repeat Overview", 0, QApplication::UnicodeUTF8));
    cylinderButton->setText(QApplication::translate("SkittleGUI", "Alignment Cylinder", 0, QApplication::UnicodeUTF8));
    sizeBox->setTitle(QApplication::translate("SkittleGUI", "Display Length", 0, QApplication::UnicodeUTF8));
    sizeDial->setSuffix(QApplication::translate("SkittleGUI", " bp", 0, QApplication::UnicodeUTF8));

#ifndef QT_NO_ACCESSIBILITY
    sizeDial->setAccessibleName(QApplication::translate("SkittleGUI", "Display Width", "Width", QApplication::UnicodeUTF8));
#endif // QT_NO_ACCESSIBILITY

    sizeDial->setSuffix(QString());
    widthBox->setTitle(QApplication::translate("SkittleGUI", "Display Width", 0, QApplication::UnicodeUTF8));

#ifndef QT_NO_ACCESSIBILITY
    widthDial->setAccessibleName(QApplication::translate("SkittleGUI", "Display Width", "Width", QApplication::UnicodeUTF8));
#endif // QT_NO_ACCESSIBILITY

    widthDial->setSuffix(QString());
    widthX2Button->setText(QApplication::translate("SkittleGUI", "x2", 0, QApplication::UnicodeUTF8));
    widthDiv2Button->setText(QApplication::translate("SkittleGUI", "/2", 0, QApplication::UnicodeUTF8));
    startBox->setTitle(QApplication::translate("SkittleGUI", "Start Position", 0, QApplication::UnicodeUTF8));

#ifndef QT_NO_ACCESSIBILITY
    startDial->setAccessibleName(QApplication::translate("SkittleGUI", "Display Width", "Width", QApplication::UnicodeUTF8));
#endif // QT_NO_ACCESSIBILITY

    startDial->setSuffix(QString());
    textureCheckBox->setText(QApplication::translate("SkittleGUI", "Texture Optimization", 0, QApplication::UnicodeUTF8));
	//widthLock->setText(QApplication::translate("SkittleGUI", "Lock Width", 0, QApplication::UnicodeUTF8));
    
    menuFile->setTitle(QApplication::translate("SkittleGUI", "File", 0, QApplication::UnicodeUTF8));
//    menuView->setTitle(QApplication::translate("SkittleGUI", "View", 0, QApplication::UnicodeUTF8));
//    menuWindows->setTitle(QApplication::translate("SkittleGUI", "Windows", 0, QApplication::UnicodeUTF8));
//    menuHelp->setTitle(QApplication::translate("SkittleGUI", "Help", 0, QApplication::UnicodeUTF8));
} // retranslateUi
    
void print(const char* s)
{
	textArea->append(QString(s));	
}

void print(std::string s)
{
	textArea->append(QString(s.c_str()));	
}

void printHtml(std::string s)
{
	QTextCursor cursor = textArea->textCursor();
	cursor.movePosition(QTextCursor::End);
	cursor.insertHtml(QString(s.c_str()));
}

void print(const char* s, int num)
{
	stringstream ss1;
	ss1 << s << num;

	textArea->append(QString( ss1.str().c_str() ));	
}

void print(int num1, int num2)
{
	stringstream ss1;
	ss1 << num1 << ", " << num2;

	textArea->append(QString( ss1.str().c_str() ));	
}


};

namespace Ui {
    class SkittleGUI: public Ui_SkittleGUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTSKITTLE_H
