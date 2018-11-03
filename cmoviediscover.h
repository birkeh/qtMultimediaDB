#ifndef CMOVIEDISCOVER_H
#define CMOVIEDISCOVER_H


#include <QDialog>
#include <QStandardItemModel>


namespace Ui {
class cMovieDiscover;
}

class cMovieDiscover : public QDialog
{
	Q_OBJECT

public:
	explicit cMovieDiscover(QWidget *parent = 0);
	~cMovieDiscover();

private slots:
	void					spanChanged(int lower, int upper);
	void					on_m_lpDiscover_clicked();
	void					on_m_lpYearEnable_clicked(bool checked);

private:
	Ui::cMovieDiscover*		ui;
	QStandardItemModel*		m_lpGenresModel;
};

#endif // CMOVIEDISCOVER_H
