#ifndef CDISCOVER_H
#define CDISCOVER_H


#include <cserie.h>

#include <QDialog>
#include <QStandardItemModel>


namespace Ui {
class cDiscover;
}

class cDiscover : public QDialog
{
	Q_OBJECT

public:
	explicit cDiscover(const cSerieList serieList, QWidget *parent = 0);
	~cDiscover();

	QList<qint32>			id();

private slots:
	void					spanChanged(int lower, int upper);
	void					on_m_lpDiscover_clicked();
	void					on_m_lpYearEnable_clicked(bool checked);
	void					on_m_lpSeries_clicked(const QModelIndex &index);

private:
	Ui::cDiscover*			ui;
	QStandardItemModel*		m_lpGenresModel;
	QStandardItemModel*		m_lpSeriesModel;
	cSerieList				m_serieList;
};

#endif // CDISCOVER_H
