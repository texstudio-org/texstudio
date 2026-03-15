#include "chatdelegate.h"
#include <QPainter>
#include <QTextDocument>
#include <QTextCursor>
#include <QAbstractTextDocumentLayout>

void ChatDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QString text = index.data(Qt::DisplayRole).toString();
    Sender sender = static_cast<Sender>(index.data(Qt::UserRole).toInt());

    painter->save();
    painter->setRenderHint(QPainter::Antialiasing);

    const int buttonSize = 20;

    // Calculate bubble size based on text
    QRect bubbleRect = option.rect.adjusted(10, 5, -10, -5);
    QTextDocument doc;
    doc.setMarkdown(text);
    doc.setTextWidth(bubbleRect.width() - margin);

    int pos1=index.data(Qt::UserRole+1).toInt();
    int pos2=index.data(Qt::UserRole+2).toInt();
    if(pos1>-1 && pos2>0){
        QTextCursor cursor(&doc);
        cursor.setPosition(pos1);
        cursor.setPosition(pos2,QTextCursor::KeepAnchor);
        QTextCharFormat selectFormat = cursor.charFormat();
        selectFormat.setBackground(Qt::blue);
        selectFormat.setForeground(Qt::white);
        cursor.setCharFormat(selectFormat); // set format for selection
    }

    int width = doc.idealWidth() + (padding * 2);
    int height = doc.size().height() + (padding * 2);

    bubbleRect.setWidth(width);
    bubbleRect.setHeight(height+buttonSize+2); // Extra space for "Copy" button

    // Positioning: Right for "Me", Left for "Them"
    if (sender == Sender::Me) {
        bubbleRect.moveLeft(option.rect.left());
        painter->setBrush(QColor(0x0078fe)); // iMessage Blue
        painter->setPen(Qt::NoPen);
    } else {
        if (sender == Sender::Them) {
            bubbleRect.moveLeft(option.rect.left()+margin);
            painter->setBrush(QColor(0xe9e9eb)); // Light Gray
            painter->setPen(Qt::NoPen);
        } else {
            // error
            bubbleRect.moveLeft(option.rect.left());
            painter->setBrush(QColor(Qt::red)); // Light Red
            painter->setPen(Qt::NoPen);
        }
    }

    // Draw the Bubble
    painter->drawRoundedRect(bubbleRect, 15, 15);

    // Draw the Text
    painter->setPen(sender == Sender::Me ? Qt::white : Qt::black);
    QRect textRect = bubbleRect.adjusted(padding, padding, -padding, -padding);
    painter->translate(textRect.topLeft());
    doc.drawContents(painter, QRect(0, 0, textRect.width(), textRect.height()));
    painter->restore();
    painter->save();
    // Draw the "Copy" button

    QRect copyButtonRect;
    copyButtonRect = QRect(
        bubbleRect.left()+padding,
        bubbleRect.bottom() - buttonSize-2,
        buttonSize,
        buttonSize
        );

    // Draw button background
    painter->setBrush(QColor("#d3d3d3"));
    painter->drawRoundedRect(copyButtonRect, 3, 3);

    // Draw "Copy" icon (or text)
    painter->setPen(Qt::black);
    painter->drawText(copyButtonRect, Qt::AlignCenter, "📋");
    // Draw "Insert" button
    //painter->setBrush(m_isInsertButtonHovered && (index == m_hoveredIndex) ? QColor("#a0a0a0") : QColor("#d3d3d3"));
    copyButtonRect.translate(buttonSize,0);
    painter->drawRoundedRect(copyButtonRect, 3, 3);
    painter->drawText(copyButtonRect, Qt::AlignCenter, "📝");

    painter->restore();
}

QSize ChatDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const {
    // Essential to prevent bubbles from overlapping
    QTextDocument doc;
    doc.setMarkdown(index.data(Qt::DisplayRole).toString());
    doc.setTextWidth(option.rect.width() - 2*padding - margin); // Account for margins
    qreal width = doc.idealWidth() + 2*padding;
    return QSize(width, doc.size().height()+2*padding+40); // Extra space for "Copy" button
}

bool ChatDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index){
    if (event->type() == QEvent::MouseButtonPress) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        if (mouseEvent->button() == Qt::LeftButton) {
            Sender sender = static_cast<Sender>(index.data(Qt::UserRole).toInt());
            QPoint pt=mouseEvent->pos();
            int pos=getPositionFromClick(index,option.rect,pt,sender);
            resetCursorInAllRows(model);
            model->setData(index,pos,Qt::UserRole+1); // Store cursor position in UserRole+1
            model->setData(index,-1,Qt::UserRole+2); // reset anchor in UserRole+2
        }
    }
    if (event->type() == QEvent::MouseButtonRelease) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        if (mouseEvent->button() == Qt::LeftButton) {
            // Calculate button rect (same logic as in paint)
            Sender sender = static_cast<Sender>(index.data(Qt::UserRole).toInt());
            QRect bubbleRect = option.rect.adjusted(10, 5, -10, -5);
            int buttonSize = 20;
            QRect copyButtonRect;
            if (sender == Sender::Me) {
                copyButtonRect = QRect(
                    bubbleRect.left(),
                    bubbleRect.bottom() - buttonSize - 2 - padding,
                    buttonSize,
                    buttonSize
                    );
            } else {
                copyButtonRect = QRect(
                    bubbleRect.left()+margin,
                    bubbleRect.bottom() - buttonSize - 2 - padding,
                    buttonSize,
                    buttonSize
                    );
            }
            QRect insertButtonRect=copyButtonRect.translated(buttonSize,0);
            // Check if click is inside the button
            if (copyButtonRect.contains(mouseEvent->pos())) {
                QApplication::clipboard()->setText(index.data(Qt::DisplayRole).toString());
                model->setData(index,-1,Qt::UserRole+1);
                return true;
            }
            if (insertButtonRect.contains(mouseEvent->pos())) {
                emit insertTextClicked(index); // Emit the signal
                model->setData(index,-1,Qt::UserRole+1);
                return true;
            }
            // check for selection
            int pos=model->data(index,Qt::UserRole+1).toInt();
            if(pos>-1){
                // selection logic
                Sender sender = static_cast<Sender>(index.data(Qt::UserRole).toInt());
                QPoint pt=mouseEvent->pos();
                int pos=getPositionFromClick(index,option.rect,pt,sender);
                model->setData(index,pos,Qt::UserRole+2); // Store cursor position in UserRole+1
            }
        }
    }
    return QStyledItemDelegate::editorEvent(event, model, option, index);
}

bool ChatDelegate::helpEvent(QHelpEvent *event, QAbstractItemView *view, const QStyleOptionViewItem &option, const QModelIndex &index){
    if (!event || !view) {
        return false;
    }

    if (event->type() == QEvent::ToolTip) {
        // Calculate button rect (same logic as in paint and editorEvent)
        Sender sender = static_cast<Sender>(index.data(Qt::UserRole).toInt());
        QRect bubbleRect = option.rect.adjusted(10, 5, -10, -5);
        int buttonSize = 20;
        QRect copyButtonRect;
        if (sender == Sender::Me) {
            copyButtonRect = QRect(
                bubbleRect.left(),
                bubbleRect.bottom() - buttonSize - 2 - padding,
                buttonSize,
                buttonSize
                );
        } else {
            copyButtonRect = QRect(
                bubbleRect.left()+margin,
                bubbleRect.bottom() - buttonSize - 2 - padding,
                buttonSize,
                buttonSize
                );
        }

        // Check if the mouse is over the button
        if (copyButtonRect.contains(event->pos())) {
            QToolTip::showText(event->globalPos(), "Copy content to clipboard");
            return true;
        }
        QRect insertButtonRect=copyButtonRect.translated(buttonSize,0);
        if (insertButtonRect.contains(event->pos())) {
            QToolTip::showText(event->globalPos(), "Insert content into document");
            return true;
        }
    }

    return QStyledItemDelegate::helpEvent(event, view, option, index);
}

int ChatDelegate::getPositionFromClick(const QModelIndex &index, const QRect rect,const QPoint &clickPos,const Sender sender) const
{
    QRect bubbleRect = rect.adjusted(10, 5, -10, -5);
    if (sender == Sender::Them) {
        bubbleRect.moveLeft(rect.left()+margin);
    }else{
        bubbleRect.moveLeft(rect.left());
    }
    QRect textRect = bubbleRect.adjusted(padding, padding, -padding, -padding);

    QPoint offset=textRect.topLeft();
    const QString text=index.data(Qt::DisplayRole).toString();
    QTextDocument doc;
    doc.setMarkdown(text);
    doc.setTextWidth(bubbleRect.width() - margin);
    auto layout = doc.documentLayout();
    QPoint pt=clickPos-offset;
    int pos = layout->hitTest(pt, Qt::FuzzyHit);
    return pos;
}
/*!
 * \brief reset stored cursor positions in all indexes
 * \param model
 */
void ChatDelegate::resetCursorInAllRows(QAbstractItemModel *model)
{
    // iterate through all rows and reset cursor position
    for (int row = 0; row < model->rowCount(); ++row) {
        QModelIndex idx = model->index(row, 0);
        model->setData(idx,-1,Qt::UserRole+1); // reset cursor position
        model->setData(idx,-1,Qt::UserRole+2); // reset anchor position
    }
}