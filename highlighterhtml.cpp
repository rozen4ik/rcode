#include "highlighterhtml.h"
#include <QTextCharFormat>
#include <QBrush>
#include <QColor>


HighlighterHTML::HighlighterHTML(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{
    HighlightingRule rule;

    edgeTagFormat.setForeground(QBrush(QColor("#32a9dd")));
    insideTagFormat.setForeground(Qt::blue);
    insideTagFormat.setFontWeight(QFont::Bold);
    openTag = QRegExp("<");
    closeTag = QRegExp(">");

    tagsFormat.setForeground(Qt::darkBlue);
    tagsFormat.setFontWeight(QFont::Bold);

    QStringList keywordPatterns;
    keywordPatterns << "<\\ba\\b" << "<\\babbr\\b" << "<\\bacronym\\b" << "<\\baddress\\b" << "<\\bapplet\\b"
                    << "<\\barea\\b" << "<\\barticle\\b" << "<\\baside\\b" << "<\\baudio\\b" << "<\\bb\\b"
                    << "<\\bbase\\b" << "<\\bbasefont\\b" << "<\\bbdi\\b" << "<\\bbdo\\b" << "<\\bbgsound\\b"
                    << "<\\bblockquote\\b" << "<\\bbig\\b" << "<\\bbody\\b" << "<\\bblink\\b" << "<\\bbr\\b"
                    << "<\\bbutton\\b" << "<\\bcanvas\\b" << "<\\bcaption\\b" << "<\\bcenter\\b" << "<\\bcite\\b"
                    << "<\\bcode\\b" << "<\\bcol\\b" << "<\\bcolgroup\\b" << "<\\bcommand\\b" << "<\\bcomment\\b"
                    << "<\\bdata\\b" << "<\\bdatalist\\b" << "<\\bdd\\b" << "<\\bdel\\b" << "<\\bdetails\\b"
                    << "<\\bdfn\\b" << "<\\bdialog\\b" << "<\\bdir\\b" << "<\\bdiv\\b" << "<\\bdl\\b"
                    << "<\\bdt\\b" << "<\\bem\\b" << "<\\bembed\\b" << "<\\bfieldset\\b" << "<\\bfigcaption\\b"
                    << "<\\bfigure\\b" << "<\\bfont\\b" << "<\\bfooter\\b" << "<\\bform\\b" << "<\\bframe\\b"
                    << "<\\bframeset\\b" << "<\\bh1\\b" << "<\\bh2\\b" << "<\\bh3\\b" << "<\\bh4\\b"
                    << "<\\bh5\\b" << "<\\bh6\\b" << "<\\bhead\\b" << "<\\bheader\\b" << "<\\bhgroup\\b"
                    << "<\\bhr\\b" << "<\\bhtml\\b" << "<\\bi\\b" << "<\\biframe\\b" << "<\\bimg\\b"
                    << "<\\binput\\b" << "<\\bins\\b" << "<\\bisindex\\b" << "<\\bkbd\\b" << "<\\bkeygen\\b"
                    << "<\\blabel\\b" << "<\\blegend\\b" << "<\\bli\\b" << "<\\blink\\b" << "<\\blisting\\b"
                    << "<\\bmain\\b" << "<\\bmap\\b" << "<\\bmarquee\\b" << "<\\bmark\\b" << "<\\bmenu\\b"
                    << "<\\bamenuitem\\b" << "<\\bmeta\\b" << "<\\bmeter\\b" << "<\\bmulticol\\b" << "<\\bnav\\b"
                    << "<\\bnobr\\b" << "<\\bnoembed\\b" << "<\\bnoindex\\b" << "<\\bnoframes\\b" << "<\\bnoscript\\b"
                    << "<\\bobject\\b" << "<\\bol\\b" << "<\\boptgroup\\b" << "<\\boption\\b" << "<\\boutput\\b"
                    << "<\\bp\\b" << "<\\bparam\\b" << "<\\bpicture\\b" << "<\\bplaintext\\b" << "<\\bpre\\b"
                    << "<\\bprogress\\b" << "<\\bq\\b" << "<\\brp\\b" << "<\\brt\\b" << "<\\brtc\\b" << "<\\bruby\\b"
                    << "<\\bs\\b" << "<\\bsamp\\b" << "<\\bscript\\b" << "<\\bsection\\b" << "<\\bselect\\b"
                    << "<\\bsmall\\b" << "<\\bsource\\b" << "<\\bspacer\\b" << "<\\bspan\\b" << "<\\bstrike\\b"
                    << "<\\bstrong\\b" << "<\\bstyle\\b" << "<\\bsub\\b" << "<\\bsummary\\b" << "<\\bsup\\b"
                    << "<\\btable\\b" << "<\\btbody\\b" << "<\\btd\\b" << "<\\btemplate\\b" << "<\\btextarea\\b"
                    << "<\\btfoot\\b" << "<\\bth\\b" << "<\\bthead\\b" << "<\\btime\\b" << "<\\btitle\\b"
                    << "<\\btr\\b" << "<\\btrack\\b" << "<\\btt\\b" << "<\\bu\\b" << "<\\bul\\b" << "<\\bvar\\b"
                    << "<\\bvideo\\b" << "<\\bwbr\\b" << "<\\bxmp\\b";

    for (const QString &pattern : keywordPatterns)
    {
        rule.pattern = QRegExp(pattern);
        rule.format = tagsFormat;
        startTagRules.append(rule);
    }

    QStringList keywordPatterns_end;
    keywordPatterns_end << "<!\\bDOCTYPE\\b" << "</\\ba\\b" << "</\\babbr\\b" << "</\\bacronym\\b" << "</\\baddress\\b" << "</\\bapplet\\b"
                        << "</\\barea\\b" << "</\\barticle\\b" << "</\\baside\\b" << "</\\baudio\\b" << "</\\bb\\b"
                        << "</\\bbase\\b" << "</\\bbasefont\\b" << "</\\bbdi\\b" << "</\\bbdo\\b" << "</\\bbgsound\\b"
                        << "</\\bblockquote\\b" << "</\\bbig\\b" << "</\\bbody\\b" << "</\\bblink\\b" << "</\\bbr\\b"
                        << "</\\bbutton\\b" << "</\\bcanvas\\b" << "</\\bcaption\\b" << "</\\bcenter\\b" << "</\\bcite\\b"
                        << "</\\bcode\\b" << "</\\bcol\\b" << "</\\bcolgroup\\b" << "</\\bcommand\\b" << "</\\bcomment\\b"
                        << "</\\bdata\\b" << "</\\bdatalist\\b" << "</\\bdd\\b" << "</\\bdel\\b" << "</\\bdetails\\b"
                        << "</\\bdfn\\b" << "</\\bdialog\\b" << "</\\bdir\\b" << "</\\bdiv\\b" << "</\\bdl\\b"
                        << "</\\bdt\\b" << "</\\bem\\b" << "</\\bembed\\b" << "</\\bfieldset\\b" << "</\\bfigcaption\\b"
                        << "</\\bfigure\\b" << "</\\bfont\\b" << "</\\bfooter\\b" << "</\\bform\\b" << "</\\bframe\\b"
                        << "</\\bframeset\\b" << "</\\bh1\\b" << "</\\bh2\\b" << "</\\bh3\\b" << "</\\bh4\\b"
                        << "</\\bh5\\b" << "</\\bh6\\b" << "</\\bhead\\b" << "</\\bheader\\b" << "</\\bhgroup\\b"
                        << "</\\bhr\\b" << "</\\bhtml\\b" << "</\\bi\\b" << "</\\biframe\\b" << "</\\bimg\\b"
                        << "</\\binput\\b" << "</\\bins\\b" << "</\\bisindex\\b" << "</\\bkbd\\b" << "</\\bkeygen\\b"
                        << "</\\blabel\\b" << "</\\blegend\\b" << "</\\bli\\b" << "</\\blink\\b" << "</\\blisting\\b"
                        << "</\\bmain\\b" << "</\\bmap\\b" << "</\\bmarquee\\b" << "</\\bmark\\b" << "</\\bmenu\\b"
                        << "</\\bamenuitem\\b" << "</\\bmeta\\b" << "</\\bmeter\\b" << "</\\bmulticol\\b" << "</\\bnav\\b"
                        << "</\\bnobr\\b" << "</\\bnoembed\\b" << "</\\bnoindex\\b" << "</\\bnoframes\\b" << "</\\bnoscript\\b"
                        << "</\\bobject\\b" << "</\\bol\\b" << "</\\boptgroup\\b" << "</\\boption\\b" << "</\\boutput\\b"
                        << "</\\bp\\b" << "</\\bparam\\b" << "</\\bpicture\\b" << "</\\bplaintext\\b" << "</\\bpre\\b"
                        << "</\\bprogress\\b" << "</\\bq\\b" << "</\\brp\\b" << "</\\brt\\b" << "</\\brtc\\b" << "</\\bruby\\b"
                        << "</\\bs\\b" << "</\\bsamp\\b" << "</\\bscript\\b" << "</\\bsection\\b" << "</\\bselect\\b"
                        << "</\\bsmall\\b" << "</\\bsource\\b" << "</\\bspacer\\b" << "</\\bspan\\b" << "</\\bstrike\\b"
                        << "</\\bstrong\\b" << "</\\bstyle\\b" << "</\\bsub\\b" << "</\\bsummary\\b" << "</\\bsup\\b"
                        << "</\\btable\\b" << "</\\btbody\\b" << "</\\btd\\b" << "</\\btemplate\\b" << "</\\btextarea\\b"
                        << "</\\btfoot\\b" << "</\\bth\\b" << "</\\bthead\\b" << "</\\btime\\b" << "</\\btitle\\b"
                        << "</\\btr\\b" << "</\\btrack\\b" << "</\\btt\\b" << "</\\bu\\b" << "</\\bul\\b" << "</\\bvar\\b"
                        << "</\\bvideo\\b" << "</\\bwbr\\b" << "</\\bxmp\\b";

    for (const QString &pattern : keywordPatterns_end)
    {
        rule.pattern = QRegExp(pattern);
        rule.format = tagsFormat;
        endTagRules.append(rule);
    }

    multiLineCommentFormat.setForeground(Qt::darkGray);
    commentStartExpression = QRegExp("<!--");
    commentEndExpression = QRegExp("-->");

    quotationFormat.setForeground(Qt::darkGreen);
    quotes = QRegExp("\"");
}

void HighlighterHTML::highlightBlock(const QString &text)
{
    setCurrentBlockState(HighlighterHTML::None);

    // TAG
    int startIndex = 0;
    // Если не находимся внутри тега,
    if (previousBlockState() != HighlighterHTML::Tag && previousBlockState() != HighlighterHTML::Quote)
    {
        // То пытаемся найти начало следующего тега
        startIndex = openTag.indexIn(text);
    }

    // Забираем состояние предыдущего текстового блока
    int subPreviousTag = previousBlockState();
    while (startIndex >= 0)
    {
        // ищем символ конца тега
        int endIndex = closeTag.indexIn(text, startIndex);

        int tagLength;
        // если конец тега не найден, то устанавливаем состояние блока
        if (endIndex == -1)
        {
            setCurrentBlockState(HighlighterHTML::Tag);
            tagLength = text.length() - startIndex;
        }
        else
        {
            tagLength = endIndex - startIndex + closeTag.matchedLength();
        }

        // Устанавливаем форматирования для тега
        if (subPreviousTag != HighlighterHTML::Tag)
        {
            // с начала тега и до конца, если предыдущее состояние не равнялось Tag
            setFormat(startIndex, 1, edgeTagFormat);
            setFormat(startIndex + 1, tagLength - 1, insideTagFormat);
        }
        else
        {
            // Если же находимся уже внутри тега с самого начала блока
            // и до конца тега
            setFormat(startIndex, tagLength, insideTagFormat);
            subPreviousTag = HighlighterHTML::None;
        }
        // Форматируем символ конца тега
        setFormat(endIndex, 1, edgeTagFormat);

        /// QUOTES ///////////////////////////////////////
        int startQuoteIndex = 0;
        // Если не находимся в кавычках с предыдущего блока
        if (previousBlockState() != HighlighterHTML::Quote)
        {
            // То пытаемся найти начало кавычек
            startQuoteIndex = quotes.indexIn(text, startIndex);
        }

        // Подсвечиваем все кавычки внутри тега
        while (startQuoteIndex >= 0 && ((startQuoteIndex < endIndex) || (endIndex == -1)))
        {
            int endQuoteIndex = quotes.indexIn(text, startQuoteIndex + 1);
            int quoteLength;
            if (endQuoteIndex == -1)
            {
                // Если закрывающая кавычка не найдена, то устанавливаем состояние Quote для блока
                setCurrentBlockState(HighlighterHTML::Quote);
                quoteLength = text.length() - startQuoteIndex;
            }
            else
            {
                quoteLength = endQuoteIndex - startQuoteIndex + quotes.matchedLength();
            }

            if ((endIndex > endQuoteIndex) || endIndex == -1)
            {
                setFormat(startQuoteIndex, quoteLength, quotationFormat);
                startQuoteIndex = quotes.indexIn(text, startQuoteIndex + quoteLength);
            }
            else
            {
                break;
            }
        }
        //////////////////////////////////////////////////
        // Снова ищем начало тега
        startIndex = openTag.indexIn(text, startIndex + tagLength);
    }

    // EDGES OF TAGS
    // Обработка цвета саимх тегов, то есть подсветка слов div, p, strong и т.д.
    for (const HighlightingRule &rule : startTagRules)
    {
        QRegExp expression(rule.pattern);
        int index = expression.indexIn(text);
        while (index >= 0)
        {
            int length = expression.matchedLength();
            setFormat(index + 1, length - 1, rule.format);
            index = expression.indexIn(text, index + length);
        }
    }

    for (const HighlightingRule &rule : endTagRules)
    {
        QRegExp expression(rule.pattern);
        int index = expression.indexIn(text);
        while (index >= 0) {
            int length = expression.matchedLength();
            setFormat(index + 1, 1, edgeTagFormat);
            setFormat(index + 2, length - 2, rule.format);
            index = expression.indexIn(text, index + length);
        }
    }

    // COMMENT
    int startCommentIndex = 0;
    // Если предыдущее состояние тега не является комментарием
    if (previousBlockState() != HighlighterHTML::Comment)
    {
        // то пытаемся найти начало комментария
        startCommentIndex = commentStartExpression.indexIn(text);
    }

    // Если комментарий найден
    while (startCommentIndex >= 0)
    {
        // Ищем конец комментария
        int endCommentIndex = commentEndExpression.indexIn(text, startCommentIndex);
        int commentLength;

        // Если конец не найден
        if (endCommentIndex == -1)
        {
            // То устанавливаем состояние Comment
            // Принцип аналогичен, что и для обычных тегов
            setCurrentBlockState(HighlighterHTML::Comment);
            commentLength = text.length() - startCommentIndex;
        }
        else
        {
            commentLength = endCommentIndex - startCommentIndex
                            + commentEndExpression.matchedLength();
        }

        setFormat(startCommentIndex, commentLength, multiLineCommentFormat);
        startCommentIndex = commentStartExpression.indexIn(text, startCommentIndex + commentLength);
    }
}

