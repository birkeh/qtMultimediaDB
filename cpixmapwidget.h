#ifndef CPIXMAPWIDGET_H
#define CPIXMAPWIDGET_H


#include <QWidget>
#include <QPixmap>


class cPixmapWidget : public QWidget
{
	Q_OBJECT
public:
	explicit cPixmapWidget(QWidget *parent = nullptr);
	void		setPixmap(const QPixmap& pixmap);

signals:

public slots:

protected:
	QPixmap		m_pixmap;
	void		paintEvent(QPaintEvent *event);
};

#endif // CPIXMAPWIDGET_H
