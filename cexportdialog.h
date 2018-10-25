#ifndef CEXPORTDIALOG_H
#define CEXPORTDIALOG_H


#include <QDialog>


namespace Ui {
class cExportDialog;
}

class cExportDialog : public QDialog
{
	Q_OBJECT

public:
	explicit cExportDialog(QWidget *parent = 0);
	~cExportDialog();

	void			values(bool& bSeries, QString& szSeriesPath, bool& bMovies, QString& szMoviesPath);
private slots:
	void			on_m_lpSeriesPathSelect_clicked();
	void			on_m_lpMoviesPathSelect_clicked();

private:
	Ui::cExportDialog *ui;
};

#endif // CEXPORTDIALOG_H
