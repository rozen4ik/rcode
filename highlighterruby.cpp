#include "highlighterruby.h"

HighlighterRUBY::HighlighterRUBY(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{
    HighlightingRule rule;
    keywordFormat.setForeground(Qt::darkBlue);
    keywordFormat.setFontWeight(QFont::Bold);
    QStringList keywordPatterns;
    keywordPatterns << "\\alias\\b" << "\\belse\\b" << "\\bnext\\b" << "\\bthen\\b"
                    << "\\band\\b" << "\\belsif\\b" << "\\bnil\\b" << "\\btrue\\b"
                    << "\\bBEGIN\\b" << "\\bEND\\b" << "\\bnot\\b" << "\\bundef\\b"
                    << "\\bbegin\\b" << "\\bend\\b" << "\\bor\\b" << "\\bunless\\b"
                    << "\\bbreak\\b" << "\\bensure\\b" << "\\bredo\\b" << "\\buntil\\b"
                    << "\\bcase\\b" << "\\bfalse\\b" << "\\brescue\\b" << "\\bwhen\\b"
                    << "\\bclass\\b" << "\\bfor\\b" << "\\bretry\\b" << "\\bwhile\\b"
                    << "\\bdef\\b" << "\\bif\\b" << "\\breturn\\b" << "\\byield\\b"
                    << "\\bdefined\\b" << "\\bin\\b" << "\\bself\\b" << "\\bdo\\b"
                    << "\\bmodule\\b" << "\\bsuper\\b" << "\\bFixnum\\b" << "\\bBignum\\b"
                    << "\\bString\\b" << "\\bArray\\b" << "\\binclude\\b" << "\\bextend\\b";

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
    multiLineCommentFormat.setForeground(Qt::darkCyan);
    commentStartExpression = QRegExp("/\\*");
    commentEndExpression = QRegExp("\\*/");
}

void HighlighterRUBY::highlightBlock(const QString &text)
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

