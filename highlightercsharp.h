#ifndef HIGHLIGHTERCSHARP_H
#define HIGHLIGHTERCSHARP_H


#include <QSyntaxHighlighter>
#include <QTextCharFormat>

QT_BEGIN_NAMESPACE
class QTextDocument;
QT_END_NAMESPACE

class HighlighterCSHARP : public QSyntaxHighlighter
{
    Q_OBJECT

public:
    HighlighterCSHARP(QTextDocument *parent = 0);

protected:
    void highlightBlock(const QString &text);

private:
    struct HighlightingRule
    {
        QRegExp pattern;
        QTextCharFormat format;
    };
    QVector<HighlightingRule> highlightingRules;

    QRegExp commentStartExpression;
    QRegExp commentEndExpression;

    QTextCharFormat keywordFormat;
    QTextCharFormat classFormat;
    QTextCharFormat singleLineCommentFormat;
    QTextCharFormat multiLineCommentFormat;
    QTextCharFormat quotationFormat;
    QTextCharFormat functionFormat;
    QTextCharFormat preprocessorFormat;
};

#endif // HIGHLIGHTERCSHARP_H
