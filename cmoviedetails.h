#ifndef CMOVIEDETAILS_H
#define CMOVIEDETAILS_H


#include "cmovie.h"

#include <QWidget>
#include <QStandardItemModel>


namespace Ui {
class cMovieDetails;
}

/*!
 \brief

 \class cMovieDetails cmoviedetails.h "cmoviedetails.h"
*/
class cMovieDetails : public QWidget
{
	Q_OBJECT

public:
	/*!
	 \brief

	 \fn cMovieDetails
	 \param parent
	*/
	explicit cMovieDetails(QWidget *parent = 0);
	/*!
	 \brief

	 \fn ~cMovieDetails
	*/
	~cMovieDetails();

	/*!
	 \brief

	 \fn setMovie
	 \param lpMovie
	*/
	void				setMovie(cMovie* lpMovie);
private:
	Ui::cMovieDetails*	ui; /*!< TODO: describe */
	QStandardItemModel*	m_lpActorsModel;
	QStandardItemModel*	m_lpGenreModel;
};

#endif // CMOVIEDETAILS_H
