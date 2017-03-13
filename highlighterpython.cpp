#include "highlighterpython.h"

HighlighterPYTHON::HighlighterPYTHON(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{
    HighlightingRule rule;
    keywordFormat.setForeground(Qt::darkBlue);
    keywordFormat.setFontWeight(QFont::Bold);
    QStringList keywordPatterns;
    keywordPatterns << "\\bFalse\\b" << "\\bclass\\b" << "\\bfinaly" << "\\bis\\b" << "\\breturn\\b"
                    << "\\bNone\\b" << "\\bcontinue\\b" << "\\bfor\\b" << "\\blambda\\b" << "\\btry"
                    << "\\bTrue\\b" << "\\bdef\\b" << "\\bfrom\\b" << "\\bnonlocal\\b" << "\\bwhile\\b"
                    << "\\band\\b" << "\\bdel\\b" << "\\bglobal\\b" << "\\bnot\\b" << "\\bwith\\b"
                    << "\\bas\\b" << "\\belif\\b" << "\\bif\\b" << "\\bor\\b" <<"\\byield\\b"
                    << "\\bassert\\b" << "\\belse\\b" << "\\bpass\\b" << "\\bbreak\\b" << "\\bexcept\\b"
                    << "\\bin\\b" << "\\braise\\b" << "\\bint\\b" << "\\bfloat\\b" << "\\bcomplex\\b"
                    << "\\bimport";
    foreach (const QString &pattern, keywordPatterns)
    {
        rule.pattern = QRegExp(pattern);
        rule.format = keywordFormat;
        highlightingRules.append(rule);
    }
    functionFormat.setForeground(Qt::blue);
    rule.pattern = QRegExp("\\b[A-Za-z0-9_]+(?=\\()");
    rule.format = functionFormat;
    highlightingRules.append(rule);
    quotationFormat.setForeground(Qt::darkBlue);
    rule.pattern = QRegExp("\".*\"");
    rule.format = quotationFormat;
    highlightingRules.append(rule);
    singleLineCommentFormat.setForeground(Qt::darkGreen);
    rule.pattern = QRegExp("#[^\n]*");
    rule.format = singleLineCommentFormat;
    highlightingRules.append(rule);
    /*preprocessorFormat.setForeground(Qt::darkRed);
    rule.pattern = QRegExp("import.*");
    rule.format = preprocessorFormat;
    highlightingRules.append(rule)*/;
    multiLineCommentFormat.setForeground(Qt::darkCyan);
    commentStartExpression = QRegExp("/\\*");
    commentEndExpression = QRegExp("\\*/");
}

void HighlighterPYTHON::highlightBlock(const QString &text)
{
    foreach (const HighlightingRule &rule, highlightingRules)
    {
        QRegExp expression(rule.pattern);
        int index = expression.indexIn(text);
        while (index >= 0)
        {
            int length = expression.matchedLength();
            setFormat(index, length, rule.format);
            index = expression.indexIn(text, index + length);
        }
    }
    setCurrentBlockState(0);
    int startIndex = 0;
    if (previousBlockState() != 1)
    {
        startIndex = commentStartExpression.indexIn(text);
    }
    while (startIndex >= 0)
    {
        int endIndex = commentEndExpression.indexIn(text, startIndex);
        int commentLength;
        if (endIndex == -1)
        {
            setCurrentBlockState(1);
            commentLength = text.length() - startIndex;
        } else
        {
            commentLength = endIndex - startIndex
                            + commentEndExpression.matchedLength();
        }
        setFormat(startIndex, commentLength, multiLineCommentFormat);
        startIndex = commentStartExpression.indexIn(text, startIndex + commentLength);
    }
}
