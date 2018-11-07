#ifndef CSEASONDELEGATE_H
#define CSEASONDELEGATE_H


#include <QStyledItemDelegate>


/*!
 \brief

 \class cSeasonDelegate cseasondelegate.h "cseasondelegate.h"
*/
class cSeasonDelegate : public QStyledItemDelegate
{
	Q_OBJECT

public:
	cSeasonDelegate(QWidget *parent = 0) : QStyledItemDelegate(parent) {}

	/*!
	 \brief

	 \fn paint
	 \param painter
	 \param option
	 \param index
	*/
	void		paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;
	/*!
	 \brief

	 \fn sizeHint
	 \param option
	 \param index
	 \return QSize
	*/
	QSize		sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;
	//QWidget*	createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;
	//void		setEditorData(QWidget *editor, const QModelIndex &index) const Q_DECL_OVERRIDE;
	//void		setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const Q_DECL_OVERRIDE;
};

#endif // CSEASONDELEGATE_H
