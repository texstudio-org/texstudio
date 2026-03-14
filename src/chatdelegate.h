#ifndef Header_ChatDelegate
#define Header_ChatDelegate
#include <QStyledItemDelegate>

enum class Sender { Me, Them, Error };

struct Message {
    QString text;
    Sender sender;
};

/*!
 * \brief The ChatDelegate class
 * Custom delegate to render chat messages as bubbles, mimicking iMessage style.
 */
class ChatDelegate : public QStyledItemDelegate {
public:
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif