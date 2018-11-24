#ifndef CMOVIESEARCH_H
#define CMOVIESEARCH_H

#include <QDialog>
#include <QList>
#include <QStandardItemModel>

#include "cmovie.h"


namespace Ui {
class cMovieSearch;
}

/*!
 \brief

 \class cMovieSearch cmoviesearch.h "cmoviesearch.h"
*/
class cMovieSearch : public QDialog
{
	Q_OBJECT

public:
	/*!
	 \brief

	 \fn cMovieSearch
	 \param parent
	*/
	explicit cMovieSearch(const cMovieList& movieList, QWidget *parent = nullptr);
	/*!
	 \brief

	 \fn ~cMovieSearch
	*/
	~cMovieSearch();

	/*!
	 \brief

	 \fn id
	 \return QList<qint32>
	*/
	QList<qint32>	id();
	/*!
	 \brief

	 \fn placeholderName
	 \return QString
	*/
	QString			placeholderName();

	/*!
	 \brief

	 \fn placeholder
	 \return bool
	*/
	bool	placeholder();
	/*!
	 \brief

	 \fn year
	 \return qint32
	*/
	qint32	year();

private slots:
	/*!
	 \brief

	 \fn on_m_lpSearchButton_clicked
	*/
	void	on_m_lpSearchButton_clicked();

	/*!
	 \brief

	 \fn on_m_lpSearch_textChanged
	 \param arg1
	*/
	void	on_m_lpSearch_textChanged(const QString &arg1);
	/*!
	 \brief

	 \fn on_m_lpPlaceholderName_textChanged
	 \param arg1
	*/
	void	on_m_lpPlaceholderName_textChanged(const QString &arg1);
	/*!
	 \brief

	 \fn on_m_lpYear_valueChanged
	 \param arg1
	*/
	void	on_m_lpYear_valueChanged(int arg1);

	/*!
	 \brief

	 \fn on_m_lpResults_clicked
	 \param index
	*/
	void	on_m_lpResults_clicked(const QModelIndex &index);

private:
	Ui::cMovieSearch*		ui; /*!< TODO: describe */
	QStandardItemModel*		m_lpResultsModel;
	cMovieList				m_movieList; /*!< TODO: describe */

	/*!
	 \brief

	 \fn setButtonBox
	*/
	void	setButtonBox();
};

#endif // CMOVIESEARCH_H
