#include "chatdelegate.h"
#include <QPainter>
#include <QTextDocument>

void ChatDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QString text = index.data(Qt::DisplayRole).toString();
    Sender sender = static_cast<Sender>(index.data(Qt::UserRole).toInt());

    painter->save();
    painter->setRenderHint(QPainter::Antialiasing);

    // Calculate bubble size based on text
    QRect bubbleRect = option.rect.adjusted(10, 5, -10, -5);
    QTextDocument doc;
    doc.setMarkdown(text);
    doc.setTextWidth(bubbleRect.width() - margin);

    int width = doc.idealWidth() + (padding * 2);
    int height = doc.size().height() + (padding * 2);

    bubbleRect.setWidth(width);
    bubbleRect.setHeight(height);

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
}

QSize ChatDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const {
    // Essential to prevent bubbles from overlapping
    QTextDocument doc;
    doc.setMarkdown(index.data(Qt::DisplayRole).toString());
    doc.setTextWidth(option.rect.width() - 2*padding - margin); // Account for margins
    qreal width = doc.idealWidth() + 2*padding;
    return QSize(width, doc.size().height()+2*padding);
}
