#ifndef CEXPORTDIALOG_H
#define CEXPORTDIALOG_H


#include <QDialog>


namespace Ui {
class cExportDialog;
}

/*!
 \brief

 \class cExportDialog cexportdialog.h "cexportdialog.h"
*/
class cExportDialog : public QDialog
{
	Q_OBJECT

public:
	/*!
	 \brief

	 \fn cExportDialog
	 \param parent
	*/
	explicit cExportDialog(QWidget *parent = 0);
	/*!
	 \brief

	 \fn ~cExportDialog
	*/
	~cExportDialog();

	/*!
	 \brief

	 \fn values
	 \param bSeries
	 \param szSeriesPath
	 \param bMovies
	 \param szMoviesPath
	*/
	void			values(bool& bSeries, QString& szSeriesPath, bool& bMovies, QString& szMoviesPath);
private slots:
	/*!
	 \brief

	 \fn on_m_lpSeriesPathSelect_clicked
	*/
	void			on_m_lpSeriesPathSelect_clicked();
	/*!
	 \brief

	 \fn on_m_lpMoviesPathSelect_clicked
	*/
	void			on_m_lpMoviesPathSelect_clicked();

private:
	Ui::cExportDialog *ui; /*!< TODO: describe */
};

#endif // CEXPORTDIALOG_H
