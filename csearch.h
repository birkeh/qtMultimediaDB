#ifndef CSEARCH_H
#define CSEARCH_H


#include <QDialog>
#include <QStandardItemModel>


namespace Ui {
class cSearch;
}

/*!
 \brief

 \class cSearch csearch.h "csearch.h"
*/
class cSearch : public QDialog
{
	Q_OBJECT

public:
	/*!
	 \brief

	 \fn cSearch
	 \param parent
	*/
	explicit cSearch(QWidget *parent = 0);
	/*!
	 \brief

	 \fn ~cSearch
	*/
	~cSearch();

	/*!
	 \brief

	 \fn id
	 \return qint32
	*/
	qint32	id();
	/*!
	 \brief

	 \fn placeholderName
	 \return QString
	*/
	QString	placeholderName();

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

	 \fn on_m_lpResults_clicked
	 \param index
	*/
	void	on_m_lpResults_clicked(const QModelIndex &index);
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

	 \fn on_m_lpResults_doubleClicked
	 \param index
	*/
	void on_m_lpResults_doubleClicked(const QModelIndex &index);

private:
	Ui::cSearch*		ui; /*!< TODO: describe */
	QStandardItemModel*	m_lpResultsModel;

	/*!
	 \brief

	 \fn setButtonBox
	*/
	void	setButtonBox();
};

#endif // CSEARCH_H
