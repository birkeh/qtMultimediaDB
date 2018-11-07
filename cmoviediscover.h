#ifndef CMOVIEDISCOVER_H
#define CMOVIEDISCOVER_H


#include "cmovie.h"

#include <QDialog>
#include <QStandardItemModel>


namespace Ui {
class cMovieDiscover;
}

/*!
 \brief

 \class cMovieDiscover cmoviediscover.h "cmoviediscover.h"
*/
class cMovieDiscover : public QDialog
{
	Q_OBJECT

public:
	/*!
	 \brief

	 \fn cMovieDiscover
	 \param movieList
	 \param parent
	*/
	explicit cMovieDiscover(const cMovieList movieList, QWidget *parent = 0);
	/*!
	 \brief

	 \fn ~cMovieDiscover
	*/
	~cMovieDiscover();

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

	 \fn on_m_lpMovies_clicked
	 \param index
	*/
	void on_m_lpMovies_clicked(const QModelIndex &index);

private:
	Ui::cMovieDiscover*		ui; /*!< TODO: describe */
	QStandardItemModel*		m_lpGenresModel; /*!< TODO: describe */
	QStandardItemModel*		m_lpMoviesModel; /*!< TODO: describe */
	cMovieList				m_movieList; /*!< TODO: describe */
};

#endif // CMOVIEDISCOVER_H
