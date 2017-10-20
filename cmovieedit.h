#ifndef CMOVIEEDIT_H
#define CMOVIEEDIT_H


#include "cmovie.h"

#include <QDialog>

namespace Ui {
class cMovieEdit;
}

class cMovieEdit : public QDialog
{
	Q_OBJECT

public:
	explicit cMovieEdit(QWidget *parent = 0);
	~cMovieEdit();

	void		setMovie(cMovie* lpMovie);
private slots:
	void on_m_lpInit_clicked();

	void on_m_lpProgress_clicked();

	void on_m_lpDone_clicked();

private:
	Ui::cMovieEdit *ui;

	cMovie*		m_lpMovie;
};

#endif // CMOVIEEDIT_H
