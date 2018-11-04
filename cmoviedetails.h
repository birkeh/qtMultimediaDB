#ifndef CMOVIEDETAILS_H
#define CMOVIEDETAILS_H


#include "cmovie.h"

#include <QWidget>


namespace Ui {
class cMovieDetails;
}

class cMovieDetails : public QWidget
{
	Q_OBJECT

public:
	explicit cMovieDetails(QWidget *parent = 0);
	~cMovieDetails();

	void				setMovie(cMovie* lpMovie);
private:
	Ui::cMovieDetails*	ui;
};

#endif // CMOVIEDETAILS_H
