#include "cscrollarea.h"

#include <QPainter>

cScrollArea::cScrollArea(QWidget* parent) :
	QScrollArea(parent)
{
}

void cScrollArea::setPixmap(const QPixmap& pixmap)
{
	m_pixmap	= pixmap;
}

void cScrollArea::paintEvent(QPaintEvent *event)
{
	if(!m_pixmap.isNull())
	{
		QPainter	painter(this);
		painter.drawPixmap(0, 0, m_pixmap);
	}
	QScrollArea::paintEvent(event);
}
