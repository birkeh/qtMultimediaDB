#ifndef CSCROLLAREA_H
#define CSCROLLAREA_H


#include <QScrollArea>
#include <QPixmap>


class cScrollArea : public QScrollArea
{
public:
	cScrollArea(QWidget* parent = 0);
	void		setPixmap(const QPixmap& pixmap);
protected:
	QPixmap		m_pixmap;
	void		paintEvent(QPaintEvent *event);
};

#endif // CSCROLLAREA_H
