#include "highlighterobjective_c.h"

HighlighterOBJECTIVE_C::HighlighterOBJECTIVE_C(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{
    HighlightingRule rule;
    keywordFormat.setForeground(Qt::darkBlue);
    keywordFormat.setFontWeight(QFont::Bold);
    QStringList keywordPatterns;
    keywordPatterns << "\\bauto\\b" << "\\belse\\b" << "\\blong\\b" << "\\bswitch\\b"
                    << "\\bbreak\\b" << "\\benum\\b" << "\\bregister\\b" << "\\btypedef\\b"
                    << "\\bcase\\b" << "\\bextern\\b" << "\\breturn\\b" << "\\bunion\\b"
                    << "\\bchar\\b" << "\\bfloat\\b" << "\\bshort\\b" << "\\bunsigned\\b"
                    << "\\bconst\\b" << "\\bfor\\b" << "\\bsigned\\b" << "\\bvoid\\b"
                    << "\\bcontinue\\b" << "\\bgoto\\b" << "\\bsizeof\\b" << "\\bvolatile\\b"
                    << "\\bdefault\\b" << "\\bif\\b" << "\\bstatic\\b" << "\\bwhile\\b"
                    << "\\bdo\\b" << "\\bint\\b" << "\\bstruct\\b" << "\\b_Packed\\b"
                    << "\\bdouble\\b" << "\\bprotocol\\b" << "\\binterface\\b" << "\\bimplementation\\b"
                    << "\\bNSObject\\b" << "\\bNSInteger\\b" << "\\bNSNumber\\b" << "\\bCGFloat\\b"
                    << "\\bproperty\\b" << "\\bnonatomic\\b" << "\\bretain\\b" << "\\bstrong\\b"
                    << "\\bweak\\b" << "\\bunsafe_unretained\\b" << "\\breadwrite\\b" << "\\breadonly\\b";;
    foreach (const QString &pattern, keywordPatterns)
    {
        rule.pattern = QRegExp(pattern);
        rule.format = keywordFormat;
        highlightingRules.append(rule);
    }
    classFormat.setFontWeight(QFont::Bold);
    classFormat.setForeground(Qt::darkMagenta);
    rule.pattern = QRegExp("\\bQ[A-Za-z]+\\b");
    rule.format = classFormat;
    highlightingRules.append(rule);
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
    preprocessorFormat.setForeground(Qt::darkRed);
    rule.pattern = QRegExp("#.*");
    rule.format = preprocessorFormat;
    highlightingRules.append(rule);
    multiLineCommentFormat.setForeground(Qt::darkCyan);
    commentStartExpression = QRegExp("/\\*");
    commentEndExpression = QRegExp("\\*/");
}

void HighlighterOBJECTIVE_C::highlightBlock(const QString &text)
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
