#ifndef CMOVIEVIEWITEMDELEGATE_H
#define CMOVIEVIEWITEMDELEGATE_H


#include <QStyledItemDelegate>


/*!
 \brief

 \class cMovieViewItemDelegate cmovieviewitemdelegate.h "cmovieviewitemdelegate.h"
*/
class cMovieViewItemDelegate : public QStyledItemDelegate
{
public:
protected:
	/*!
	 \brief

	 \fn paint
	 \param painter
	 \param option
	 \param index
	*/
	void			paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
	/*!
	 \brief

	 \fn sizeHint
	 \param option
	 \param index
	 \return QSize
	*/
	QSize			sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // CMOVIEVIEWITEMDELEGATE_H
