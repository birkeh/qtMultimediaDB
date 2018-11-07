#ifndef CMOVIEEDIT_H
#define CMOVIEEDIT_H


#include "cmovie.h"

#include <QDialog>

namespace Ui {
class cMovieEdit;
}

/*!
 \brief

 \class cMovieEdit cmovieedit.h "cmovieedit.h"
*/
class cMovieEdit : public QDialog
{
	Q_OBJECT

public:
	/*!
	 \brief

	 \fn cMovieEdit
	 \param parent
	*/
	explicit cMovieEdit(QWidget *parent = 0);
	/*!
	 \brief

	 \fn ~cMovieEdit
	*/
	~cMovieEdit();

	/*!
	 \brief

	 \fn setMovie
	 \param lpMovie
	*/
	void		setMovie(cMovie* lpMovie);
private slots:
	/*!
	 \brief

	 \fn on_m_lpInit_clicked
	*/
	void on_m_lpInit_clicked();

	/*!
	 \brief

	 \fn on_m_lpProgress_clicked
	*/
	void on_m_lpProgress_clicked();

	/*!
	 \brief

	 \fn on_m_lpDone_clicked
	*/
	void on_m_lpDone_clicked();

private:
	Ui::cMovieEdit *ui; /*!< TODO: describe */

	cMovie*		m_lpMovie; /*!< TODO: describe */
};

#endif // CMOVIEEDIT_H
