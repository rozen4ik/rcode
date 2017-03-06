#include <QtWidgets>
#include "codeeditor.h"
#include "mainwindow.h"

CodeEditor::CodeEditor(QWidget *parent) : QPlainTextEdit(parent)
{
    currentLineBackground = QColor(180,220,250);
    marginBackground = Qt::lightGray;
    marginForeground = Qt::black;
    this->setLineWrapMode(QPlainTextEdit::NoWrap);
    lineNumberArea = new LineNumberArea(this);
    connect(this, SIGNAL(blockCountChanged(int)), this, SLOT(updateLineNumberAreaWidth(int)));
    connect(this, SIGNAL(updateRequest(QRect,int)), this, SLOT(updateLineNumberArea(QRect,int)));
    connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(highlightCurrentLine()));
    updateLineNumberAreaWidth(0);
    highlightCurrentLine();
    codeCompleter = new QCompleter(this);
    codeCompleter->setModelSorting(QCompleter::CaseInsensitivelySortedModel);
    codeCompleter->setCaseSensitivity(Qt::CaseInsensitive);
    codeCompleter->setWrapAround(false);
    this->setCompleter(codeCompleter);
}

void CodeEditor::setCompleter(QCompleter *completer)
{
    if (codeCompleter)
    {
        QObject::disconnect(codeCompleter, 0, this, 0);
    }
    codeCompleter = completer;
    if (!codeCompleter)
    {
        return;
    }
    codeCompleter->setWidget(this);
    codeCompleter->setCompletionMode(QCompleter::PopupCompletion);
    codeCompleter->setCaseSensitivity(Qt::CaseInsensitive);
    QObject::connect(codeCompleter, SIGNAL(activated(QString)),
                     this, SLOT(insertCompletion(QString)));
}

QAbstractItemModel *CodeEditor::modelFromFile(const QString& fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly))
    {
        return new QStringListModel(codeCompleter);
    }
#ifndef QT_NO_CURSOR
    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
#endif
    QStringList words;
    while (!file.atEnd())
    {
        QByteArray line = file.readLine();
        if (!line.isEmpty())
            words << line.trimmed();
    }

#ifndef QT_NO_CURSOR
    QApplication::restoreOverrideCursor();
#endif
    return new QStringListModel(words, codeCompleter);
}

QString CodeEditor::textUnderCursor() const
{
    QTextCursor tc = textCursor();
    tc.select(QTextCursor::WordUnderCursor);
    return tc.selectedText();
}

void CodeEditor::insertCompletion(const QString& completion)
{
    if (codeCompleter->widget() != this)
    {
        return;
    }
    QTextCursor tc = textCursor();
    int extra = completion.length() - codeCompleter->completionPrefix().length();
    tc.movePosition(QTextCursor::Left);
    tc.movePosition(QTextCursor::EndOfWord);
    tc.insertText(completion.right(extra));
    setTextCursor(tc);
}

void CodeEditor::focusInEvent(QFocusEvent *e)
{
    if (codeCompleter)
        codeCompleter->setWidget(this);
    QPlainTextEdit::focusInEvent(e);
}

void CodeEditor::keyPressEvent(QKeyEvent *e)
{
    if (codeCompleter && codeCompleter->popup()->isVisible())
    {
       switch (e->key()) {
       case Qt::Key_Enter:
       case Qt::Key_Return:
       case Qt::Key_Escape:
       case Qt::Key_Tab:
       case Qt::Key_Backtab:
            e->ignore();
            return;
       default:
           break;
       }
    }
    bool isShortcut = ((e->modifiers() & Qt::ControlModifier) && e->key() == Qt::Key_E);
    if (!codeCompleter || !isShortcut)
    {
        QPlainTextEdit::keyPressEvent(e);
    }
    const bool ctrlOrShift = e->modifiers() & (Qt::ControlModifier | Qt::ShiftModifier);
    if (!codeCompleter || (ctrlOrShift && e->text().isEmpty()))
    {
        return;
    }
    static QString eow("~!@#$%^&*()_+{}|:\"<>?,./;'[]\\-=");
    bool hasModifier = (e->modifiers() != Qt::NoModifier) && !ctrlOrShift;
    QString completionPrefix = textUnderCursor();

    if (!isShortcut && (hasModifier || e->text().isEmpty()|| completionPrefix.length() < 3
                      || eow.contains(e->text().right(1))))
    {
        codeCompleter->popup()->hide();
        return;
    }
    if (completionPrefix != codeCompleter->completionPrefix())
    {
        codeCompleter->setCompletionPrefix(completionPrefix);
        codeCompleter->popup()->setCurrentIndex(codeCompleter->completionModel()->index(0, 0));
    }
    QRect cr = cursorRect();
    cr.setWidth(codeCompleter->popup()->sizeHintForColumn(0)
                + codeCompleter->popup()->verticalScrollBar()->sizeHint().width());
    codeCompleter->complete(cr);
}

void CodeEditor::setTabSpaces(const int tabStop)
{
    QFontMetrics metrics(this->font());
    this->setTabStopWidth(tabStop * metrics.width(' '));
}

void CodeEditor::setFont(const QFont& font)
{
    this->setTabSpaces(4);
    QPlainTextEdit::setFont(font);
}

int CodeEditor::lineNumberAreaWidth()
{
    int digits = 1;
    int max = qMax(1, blockCount());
    while (max >= 10)
    {
        max /= 10;
        ++digits;
    }
    int space = 3 + fontMetrics().width(QLatin1Char('9')) * digits;
    return space;
}

void CodeEditor::updateLineNumberAreaWidth(int /* newBlockCount */)
{
    setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}

void CodeEditor::updateLineNumberArea(const QRect &rect, int dy)
{
    if (dy)
    {
        lineNumberArea->scroll(0, dy);
    }
    else
    {
        lineNumberArea->update(0, rect.y(), lineNumberArea->width(), rect.height());
    }
    if (rect.contains(viewport()->rect()))
    {
        updateLineNumberAreaWidth(0);
    }
}

void CodeEditor::resizeEvent(QResizeEvent *e)
{
    QPlainTextEdit::resizeEvent(e);
    QRect cr = contentsRect();
    lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
}

void CodeEditor::highlightCurrentLine()
{
    QList<QTextEdit::ExtraSelection> extraSelections;
    if (!isReadOnly())
    {
        QTextEdit::ExtraSelection selection;
        selection.format.setBackground(currentLineBackground);
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        selection.cursor = textCursor();
        selection.cursor.clearSelection();
        extraSelections.append(selection);
    }
    setExtraSelections(extraSelections);
}

void CodeEditor::lineNumberAreaPaintEvent(QPaintEvent *event)
{
    QPainter painter(lineNumberArea);
    painter.fillRect(event->rect(), marginBackground);
    QTextBlock block = firstVisibleBlock();
    int blockNumber = block.blockNumber();
    int top = (int) blockBoundingGeometry(block).translated(contentOffset()).top();
    int bottom = top + (int) blockBoundingRect(block).height();
    while (block.isValid() && top <= event->rect().bottom())
    {
        if (block.isVisible() && bottom >= event->rect().top())
        {
            QString number = QString::number(blockNumber + 1);
            painter.setPen(marginForeground);
            painter.drawText(0, top, lineNumberArea->width(), fontMetrics().height(),
                             Qt::AlignRight, number);
        }
        block = block.next();
        top = bottom;
        bottom = top + (int) blockBoundingRect(block).height();
        ++blockNumber;
    }
}
