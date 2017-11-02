#include "cpixmapwidget.h"

#include <QPainter>


cPixmapWidget::cPixmapWidget(QWidget *parent) : QWidget(parent)
{

}

void cPixmapWidget::setPixmap(const QPixmap& pixmap)
{
	m_pixmap	= pixmap;
}

void cPixmapWidget::paintEvent(QPaintEvent *event)
{
	if(!m_pixmap.isNull())
	{
		QPainter	painter(this);
		painter.drawPixmap(0, 0, m_pixmap.scaled(width(), height(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation));
	}
	QWidget::paintEvent(event);
}
