#include "highlighterjavascript.h"

HighlighterJAVASCRIPT::HighlighterJAVASCRIPT(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{
    HighlightingRule rule;
    keywordFormat.setForeground(Qt::darkBlue);
    keywordFormat.setFontWeight(QFont::Bold);
    QStringList keywordPatterns;
    keywordPatterns << "\\babstract\\b" << "\\belse\\b" << "\\binstanceof\\b" << "\\bswitch\\b"
                    << "\\bboolean\\b" << "\\benum\\b" << "\\bint\\b" << "\\bsynchronized\\b"
                    << "\\bbreak\\b" << "\\bexport\\b" << "\\binterface\\b" << "\\bthis\\b"
                    << "\\bbyte\\b" << "\\bextends\\b" << "\\blong\\b" << "\\bthrow\\b"
                    << "\\bcase\\b" << "\\bfalse\\b" << "\\bnative\\b" << "\\bthrows\\b"
                    << "\\bcatch\\b" << "\\bfinal\\b" << "\\bnew\\b" << "\\btransient\\b"
                    << "\\bchar\\b" << "\\bfinally\\b" << "\\bnull\\b" << "\\btrue\\b"
                    << "\\bclass\\b" << "\\bfloat\\b" << "\\bpackage\\b" << "\\btry\\b"
                    << "\\bconst\\b" << "\\bfor\\b" << "\\bprivate\\b" << "\\btypeof\\b"
                    << "\\bcontinue\\b" << "\\bfunction\\b" << "\\bprotected\\b" << "\\bvar\\b"
                    << "\\bdebugger\\b" << "\\bgoto\\b" << "\\bpublic\\b" << "\\bvoid\\b"
                    << "\\bdefault\\b" << "\\bif\\b" << "\\breturn\\b" << "\\bvolatile\\b"
                    << "\\bdo\\b" << "\\bimport\\b" << "\\bstatic\\b" << "\\bwith\\b"
                    << "\\bdelete\\b" << "\\bimplements\\b" << "\\bshort\\b" << "\\bwhile\\b"
                    << "\\bdouble\\b" << "\\bin\\b" << "\\bsuper\\b";
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
    rule.pattern = QRegExp("//[^\n]*");
    rule.format = singleLineCommentFormat;
    highlightingRules.append(rule);
    preprocessorFormat.setForeground(Qt::darkBlue);
    rule.pattern = QRegExp("\'.*\'");
    rule.format = preprocessorFormat;
    highlightingRules.append(rule);
    multiLineCommentFormat.setForeground(Qt::darkCyan);
    commentStartExpression = QRegExp("/\\*");
    commentEndExpression = QRegExp("\\*/");
}

void HighlighterJAVASCRIPT::highlightBlock(const QString &text)
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
