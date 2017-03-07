#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "highlightercpp.h"
#include "highlighterhtml.h"
#include "highlighteroff.h"
#include "highlighterjava.h"
#include "highlightercsharp.h"
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
    void settingsDialog();
    void saveAsFile();
    void comboxIndex(int comboIndex);


private:
    void setupEditor();
    void setupFileMenu();
    void setupHelpMenu();
    void setupDockWidgets();

    QDockWidget *dockWidgets;
    CodeEditor *editor;
    HighlighterOFF *highlighterOFF;
    HighlighterCPP *highlighterCPP;
    HighlighterHTML *highlighterHTML;
    HighlighterJAVA *highlighterJAVA;
    HighlighterCSHARP *highlighterCSHARP;
};

#endif // MAINWINDOW_H
