#include "mainwindow.h"
#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupFileMenu();
    setupHelpMenu();
    setupEditor();
    setCentralWidget(editor);
    setWindowTitle(tr("RCode"));
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About"),
                tr("<p>The <b>QCodeEdit</b> example shows how " \
                   "to create a basic code editing component with " \
                   "simple syntax highlighting by subclassing " \
                   "the <b>QSyntaxHighlighter</b> class and describing " \
                   "highlighting rules using regular expressions.</p>"));
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
        fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", "C++ Files (*.cpp *.h)");
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
    QString fileName = QFileDialog::getSaveFileName(this, "Save As File", "source", tr("*.cpp;;*.h"));
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
    highlighter = new Highlighter(editor->document());
    statusBar()->showMessage("Ready to work!");
}

void MainWindow::setupFileMenu()
{
    QMenu *fileMenu = new QMenu(tr("&File"), this);
    menuBar()->addMenu(fileMenu);
    fileMenu->addAction(tr("&New"), this, SLOT(newFile()), QKeySequence::New);
    fileMenu->addAction(tr("&Open..."), this, SLOT(openFile()), QKeySequence::Open);
    fileMenu->addAction(tr("&Save As.."), this, SLOT(saveAsFile()), QKeySequence::Save);
    fileMenu->addAction(tr("&Exit"), qApp, SLOT(quit()), QKeySequence::Quit);
}

void MainWindow::setupHelpMenu()
{
    QMenu *helpMenu = new QMenu(tr("&Help"), this);
    menuBar()->addMenu(helpMenu);
    helpMenu->addAction(tr("&About"), this, SLOT(about()));
}

