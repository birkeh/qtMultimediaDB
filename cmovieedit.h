#ifndef CMOVIEEDIT_H
#define CMOVIEEDIT_H


#include "cmovie.h"

#include <QDialog>
#include <QStandardItemModel>


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
	explicit cMovieEdit(QWidget *parent = nullptr);
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

	 \fn on_buttonBox_accepted
	*/
	void		on_buttonBox_accepted();

private:
	Ui::cMovieEdit*		ui;					/*!< TODO: describe */
	cMovie*				m_lpMovie;			/*!< TODO: describe */
	QStandardItemModel*	m_lpActorsModel;	/*!< TODO: describe */
	QStandardItemModel*	m_lpGenreModel;		/*!< TODO: describe */
};

#endif // CMOVIEEDIT_H
