#ifndef CPIXMAPWIDGET_H
#define CPIXMAPWIDGET_H


#include <QWidget>
#include <QPixmap>


/*!
 \brief

 \class cPixmapWidget cpixmapwidget.h "cpixmapwidget.h"
*/
class cPixmapWidget : public QWidget
{
	Q_OBJECT
public:
	/*!
	 \brief

	 \fn cPixmapWidget
	 \param parent
	*/
	explicit cPixmapWidget(QWidget *parent = nullptr);
	/*!
	 \brief

	 \fn setPixmap
	 \param pixmap
	*/
	void		setPixmap(const QPixmap& pixmap);

signals:

public slots:

protected:
	QPixmap		m_pixmap; /*!< TODO: describe */
	/*!
	 \brief

	 \fn paintEvent
	 \param event
	*/
	void		paintEvent(QPaintEvent *event);
};

#endif // CPIXMAPWIDGET_H
