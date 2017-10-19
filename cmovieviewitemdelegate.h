#ifndef CMOVIEVIEWITEMDELEGATE_H
#define CMOVIEVIEWITEMDELEGATE_H


#include <QStyledItemDelegate>


class cMovieViewItemDelegate : public QStyledItemDelegate
{
public:
protected:
	void			paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
	QSize			sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // CMOVIEVIEWITEMDELEGATE_H
