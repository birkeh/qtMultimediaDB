#ifndef CMOVIEDISCOVER_H
#define CMOVIEDISCOVER_H


#include "cmovie.h"

#include <QDialog>
#include <QStandardItemModel>


namespace Ui {
class cMovieDiscover;
}

class cMovieDiscover : public QDialog
{
	Q_OBJECT

public:
	explicit cMovieDiscover(const cMovieList movieList, QWidget *parent = 0);
	~cMovieDiscover();

private slots:
	void					spanChanged(int lower, int upper);
	void					on_m_lpDiscover_clicked();
	void					on_m_lpYearEnable_clicked(bool checked);

	void on_m_lpMovies_clicked(const QModelIndex &index);

private:
	Ui::cMovieDiscover*		ui;
	QStandardItemModel*		m_lpGenresModel;
	QStandardItemModel*		m_lpMoviesModel;
	cMovieList				m_movieList;
};

#endif // CMOVIEDISCOVER_H
