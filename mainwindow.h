#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "highlightercpp.h"
#include "highlighterhtml.h"
#include "codeeditor.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);

public slots:
    void about();
    void newFile();
    void openFile(const QString &path = QString());
    void saveAsFile();

private:
    void setupEditor();
    void setupFileMenu();
    void setupHelpMenu();
    void setupDockWidgets();

    QDockWidget *dockWidgets;
    CodeEditor *editor;
    HighlighterCPP *highlighterCPP;
    HighlighterHTML *highlighterHTML;
};

#endif // MAINWINDOW_H
