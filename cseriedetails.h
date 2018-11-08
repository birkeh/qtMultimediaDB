#ifndef CSERIEDETAILS_H
#define CSERIEDETAILS_H


#include "cserie.h"

#include <QWidget>
#include <QStandardItemModel>


namespace Ui {
class cSerieDetails;
}

/*!
 \brief

 \class cSerieDetails cseriedetails.h "cseriedetails.h"
*/
class cSerieDetails : public QWidget
{
	Q_OBJECT

public:
	/*!
	 \brief

	 \fn cSerieDetails
	 \param parent
	*/
	explicit cSerieDetails(QWidget *parent = 0);
	/*!
	 \brief

	 \fn ~cSerieDetails
	*/
	~cSerieDetails();

	/*!
	 \brief

	 \fn setSerie
	 \param lpSerie
	*/
	void				setSerie(cSerie* lpSerie);
private:
	Ui::cSerieDetails*	ui; /*!< TODO: describe */
	QStandardItemModel*	m_lpActorsModel; /*!< TODO: describe */
	QStandardItemModel*	m_lpGenreModel; /*!< TODO: describe */
};

#endif // CSERIEDETAILS_H
