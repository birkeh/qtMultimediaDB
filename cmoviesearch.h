#ifndef CMOVIESEARCH_H
#define CMOVIESEARCH_H

#include <QDialog>

namespace Ui {
class cMovieSearch;
}

class cMovieSearch : public QDialog
{
	Q_OBJECT

public:
	explicit cMovieSearch(QWidget *parent = 0);
	~cMovieSearch();

	qint32	id();
	QString	placeholderName();

	bool	placeholder();
	qint16	year();

private slots:
	void on_m_lpSearchButton_clicked();

	void on_m_lpSearch_textChanged(const QString &arg1);

private:
	Ui::cMovieSearch *ui;
};

#endif // CMOVIESEARCH_H
