#ifndef CPREFERENCES_H
#define CPREFERENCES_H

#include <QDialog>

namespace Ui {
class cPreferences;
}

class cPreferences : public QDialog
{
	Q_OBJECT

public:
	explicit cPreferences(QWidget *parent = nullptr);
	~cPreferences();

	bool					displaySeason0Changed();
private slots:
	void on_m_lpSeriesPathSelect_clicked();

	void on_m_lpMoviesPathSelect_clicked();

private:
	Ui::cPreferences*		ui;
	bool					m_bDisplaySeason0;
};

#endif // CPREFERENCES_H
