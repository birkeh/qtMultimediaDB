#ifndef CSCROLLAREA_H
#define CSCROLLAREA_H


#include <QScrollArea>
#include <QPixmap>


/*!
 \brief

 \class cScrollArea cscrollarea.h "cscrollarea.h"
*/
class cScrollArea : public QScrollArea
{
public:
	cScrollArea(QWidget* parent = 0);
	/*!
	 \brief

	 \fn setPixmap
	 \param pixmap
	*/
	void		setPixmap(const QPixmap& pixmap);
protected:
	QPixmap		m_pixmap; /*!< TODO: describe */
	/*!
	 \brief

	 \fn paintEvent
	 \param event
	*/
	void		paintEvent(QPaintEvent *event);
};

#endif // CSCROLLAREA_H
