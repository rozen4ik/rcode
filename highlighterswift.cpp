#include "highlighterswift.h"

HighlighterSWIFT::HighlighterSWIFT(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{
    HighlightingRule rule;
    keywordFormat.setForeground(Qt::darkBlue);
    keywordFormat.setFontWeight(QFont::Bold);
    QStringList keywordPatterns;
    keywordPatterns << "\\bclass\\b" << "\\bdeinit\\b" << "\\benum\\b" << "\\bextension\\b"
                    << "\\func\\b" << "\\binit\\b" << "\\binternal\\b"
                    << "\\blet\\b" << "\\boperator\\b" << "\\bprivate\\b" << "\\bprotocol\\b"
                    << "\\bpublics\\b" << "\\bstatic\\b" << "\\bstruct\\b" << "\\bsubscript\\b"
                    << "\\btypealias\\b" << "\\bvar\\b" << "\\bCharacter\\b"
                    << "\\bbreak\\b" << "\\bcase\\b" << "\\bcontinue\\b" << "\\bdefault\\b"
                    << "\\bdo\\b" << "\\belse\\b" << "\\bfallthrough\\b" << "\\bfor\\b"
                    << "\\bif\\b" << "\\bin\\b" << "\\breturn\\b" << "\\bswitch\\b"
                    << "\\bwhere\\b" << "\\bwhile\\b" << "\\bInt\\b" << "\\bBool\\b"
                    << "\\bas\\b" << "\\bdynamicType\\b" << "\\bfalse\\b" << "\\bis\\b"
                    << "\\bnil\\b" << "\\bself\\b" << "\\bSelf\\b" << "\\bsuper\\b"
                    << "\\btrue\\b" << "\\b_COLUMN_\\b" << "\\b_FILE_\\b" << "\\b_FUNCTION_\\b"
                    << "\\b_LINE_\\b" << "\\bString\\b" << "\\bDouble\\b" << "\\bFloat\\b"
                    << "\\bassociativity\\b" << "\\bconvenience\\b" << "\\bdynamic\\b" << "\\bdidSet\\b"
                    << "\\bfinal\\b" << "\\bget\\b" << "\\binfix\\b" << "\\binout\\b"
                    << "\\blazy\\b" << "\\bleft\\b" << "\\bmutating\\b" << "\\bnone\\b"
                    << "\\bnonmutating\\b" << "\\boptional\\b" << "\\boverride\\b" << "\\bpostfix\\b"
                    << "\\bprecedence\\b" << "\\bprefix\\b" << "\\bProtocol\\b" << "\\brequired\\b"
                    << "\\bright\\b" << "\\bset\\b" << "\\bType\\b" << "\\bunowned\\b"
                    << "\\weak\\b" << "\\bwillSet\\b";

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
    preprocessorFormat.setForeground(Qt::darkRed);
    rule.pattern = QRegExp("import.*");
    rule.format = preprocessorFormat;
    highlightingRules.append(rule);
    multiLineCommentFormat.setForeground(Qt::darkCyan);
    commentStartExpression = QRegExp("/\\*");
    commentEndExpression = QRegExp("\\*/");
}

void HighlighterSWIFT::highlightBlock(const QString &text)
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
