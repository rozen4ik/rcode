#include "mainwindow.h"
#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupFileMenu();
    setupHelpMenu();
    setupEditor();
    setupDockWidgets();
    setCentralWidget(editor);    
    setWindowTitle(tr("RCode"));
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About"),
                tr("Author: Mikhail Rozenberg"));
}

void MainWindow::newFile()
{
    editor->clear();
}

void MainWindow::openFile(const QString &path)
{
    QString fileName = path;
    if (fileName.isNull())
    {
        fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", "Text Files (*.txt);; C++ Files (*.cpp *.h);; HTML Files (*.html);; "
                                                                           "Java Files (*.java)");
    }
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QFile::ReadOnly | QFile::Text))
            editor->setPlainText(file.readAll());
    }
    statusBar()->showMessage("Read to file: " + fileName);
}

void MainWindow::saveAsFile()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save As File", "source", tr("*.txt;;*.cpp;;*.h;;*.html;;*.java"));
    QFile file;
    file.setFileName(fileName);
    file.open(QIODevice::ReadWrite);
    QTextStream stream(&file);
    stream<<editor->toPlainText();
    statusBar()->showMessage("Write to file: " + fileName);
}

void MainWindow::setupEditor()
{
    QFont font;
    font.setFamily("Courier");
    font.setFixedPitch(true);
    font.setPointSize(10);
    editor = new CodeEditor();
    editor->setFont(font);
    editor->setTabSpaces(4);
    statusBar()->showMessage("Ready to work!");
}

void MainWindow::setupFileMenu()
{
    QMenu *fileMenu = new QMenu(tr("&File"), this);
    menuBar()->addMenu(fileMenu);
    fileMenu->addAction(tr("&New"), this, SLOT(newFile()), QKeySequence::New);
    fileMenu->addAction(tr("&Open..."), this, SLOT(openFile()), QKeySequence::Open);
    fileMenu->addAction(tr("&Save As..."), this, SLOT(saveAsFile()), QKeySequence::Save);
    fileMenu->addAction(tr("Settings..."), this, SLOT(settingsDialog()), QKeySequence::Preferences);
    fileMenu->addAction(tr("&Exit"), qApp, SLOT(quit()), QKeySequence::Quit);
}

void MainWindow::setupHelpMenu()
{
    QMenu *helpMenu = new QMenu(tr("&Help"), this);
    menuBar()->addMenu(helpMenu);
    helpMenu->addAction(tr("&About"), this, SLOT(about()));
}

void MainWindow::setupDockWidgets()
{
    QComboBox *cmBox = new QComboBox();
    cmBox->addItem("Plain Text");
    cmBox->addItem("C++");
    cmBox->addItem("HTML");
    cmBox->addItem("Java");

    QDockWidget *dockWidgetComBox = new QDockWidget(tr("Dock Widget"), this);
    dockWidgetComBox->setWindowTitle("Language");
    dockWidgetComBox->setWidget(cmBox);
    addDockWidget(Qt::LeftDockWidgetArea, dockWidgetComBox);
    connect(cmBox, SIGNAL(activated(int)), this, SLOT(comboxIndex(int)));
}

void MainWindow::comboxIndex(int comboIndex)
{
    switch(comboIndex)
    {
    case 0:
        highlighterOFF = new HighlighterOFF(editor->document());
        break;
    case 1:
        highlighterCPP = new HighlighterCPP(editor->document());
        break;
    case 2:
        highlighterHTML = new HighlighterHTML(editor->document());
        break;
    case 3:
        highlighterJAVA = new HighlighterJAVA(editor->document());
        break;
    default:      
        break;
    }
}

void MainWindow::settingsDialog()
{
    editor->setFont(QFontDialog::getFont(0, editor->font()));
}
