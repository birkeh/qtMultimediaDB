#ifndef CDISCOVER_H
#define CDISCOVER_H


#include <cserie.h>

#include <QDialog>
#include <QStandardItemModel>


namespace Ui {
class cDiscover;
}

/*!
 \brief

 \class cDiscover cdiscover.h "cdiscover.h"
*/
class cDiscover : public QDialog
{
	Q_OBJECT

public:
	/*!
	 \brief

	 \fn cDiscover
	 \param serieList
	 \param parent
	*/
	explicit cDiscover(const cSerieList serieList, QWidget *parent = 0);
	/*!
	 \brief

	 \fn ~cDiscover
	*/
	~cDiscover();

	/*!
	 \brief

	 \fn id
	 \return QList<qint32>
	*/
	QList<qint32>			id();

private slots:
	/*!
	 \brief

	 \fn spanChanged
	 \param lower
	 \param upper
	*/
	void					spanChanged(int lower, int upper);
	/*!
	 \brief

	 \fn on_m_lpDiscover_clicked
	*/
	void					on_m_lpDiscover_clicked();
	/*!
	 \brief

	 \fn on_m_lpYearEnable_clicked
	 \param checked
	*/
	void					on_m_lpYearEnable_clicked(bool checked);
	/*!
	 \brief

	 \fn on_m_lpSeries_clicked
	 \param index
	*/
	void					on_m_lpSeries_clicked(const QModelIndex &index);

private:
	Ui::cDiscover*			ui; /*!< TODO: describe */
	QStandardItemModel*		m_lpGenresModel; /*!< TODO: describe */
	QStandardItemModel*		m_lpSeriesModel; /*!< TODO: describe */
	cSerieList				m_serieList; /*!< TODO: describe */
};

#endif // CDISCOVER_H
