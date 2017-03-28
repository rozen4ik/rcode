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
                tr("Author: Mikhail Rozenberg\n"\
                   "RCode version 0.2"));
}

void MainWindow::newFile()
{
    editor->clear();
    statusBar()->showMessage("New file");
}

void MainWindow::openFile(const QString &path)
{
    QString fileName = path;
    if (fileName.isNull())
    {
        fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", "Text Files (*.txt);; C/C++ Files (*.c *.cpp *.h);; "
                                                                           "HTML Files (*.html);; ""Java Files (*.java);; "
                                                                           "C# Files (*.cs);; Python Files (*.py)"
                                                                           "JavaScript (*.js)");
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
    QString fileName = QFileDialog::getSaveFileName(this, "Save As File", "source", tr("*.txt;; *.c;; *.cpp;; *.h;; *.html;; *.java;; *.cs;; "
                                                                                       "*.py;; *.js"));
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
    font.setPointSize(14);
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
    cmBox->addItem("C");
    cmBox->addItem("C++");
    cmBox->addItem("HTML");
    cmBox->addItem("Java");
    cmBox->addItem("C#");
    cmBox->addItem("Python");
    cmBox->addItem("JavaScript");

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
        highlighterCPP = new HighlighterCPP(editor->document());
        break;
    case 3:
        highlighterHTML = new HighlighterHTML(editor->document());
        break;
    case 4:
        highlighterJAVA = new HighlighterJAVA(editor->document());
        break;
    case 5:
        highlighterCSHARP = new HighlighterCSHARP(editor->document());
        break;
    case 6:
        highlighterPYTHON = new HighlighterPYTHON(editor->document());
        break;
    case 7:
        highlighterJAVASCRIPT = new HighlighterJAVASCRIPT(editor->document());
    default:      
        break;
    }
}

void MainWindow::settingsDialog()
{
    editor->setFont(QFontDialog::getFont(0, editor->font()));
}

//QStringList list;
//list << "Вася" << "Петя" << "Катя" << "Маша" << "Юля" << "Петр Петр" << "Павел" << "Пинки"
//        << "Петр Паша" << "Петр Вася" << "Петр Катя" << "Петр Пинки" << "Петр Ваня";

//QCompleter *completer = new QCompleter(list, this);
//completer->setCaseSensitivity(Qt::CaseInsensitive);

//QLineEdit *e = new QLineEdit();
//e->setCompleter(completer);

//void MeasuresPanel::searchTextChanged(QString)
//{
//    // Ищем введенный текст...
//    Database d;
//    QLineEdit *edit = static_cast< QLineEdit * >(sender());
//    QCompleter *completer = edit->completer();

//    // Выясним, что же все таки надо искать...
//    // nameLine, diseaseLine, pointLine
//    QStringList items;
//    QVector< int > keys;

//    if (!edit->objectName().compare("nameLine", Qt::CaseInsensitive))
//    {
//        // Работаем с именем
//        keys = d.searchName(edit->text());
//    } else
//        if (!edit->objectName().compare("diseaseLine", Qt::CaseInsensitive))
//        {
//            // Работа с заболеванием
//            keys = d.searchDisease(edit->text());
//        } else // Работа с точками
//            keys = d.searchPoints(edit->text());

//    // Нашли ряд ключей
//    for (QVector< int >::iterator i = keys.begin(); i != keys.end(); i++)
//    {
//        items << d.getName(*i);
//    }

//    delete completer;
//    completer = new QCompleter(items);
//    completer->setCompletionMode(QCompleter::InlineCompletion);
//    completer->setCaseSensitivity(Qt::CaseInsensitive);
//    edit->setCompleter(completer);
//    edit->setFocus();
//}
