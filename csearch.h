#ifndef CSEARCH_H
#define CSEARCH_H

#include <QDialog>

namespace Ui {
class cSearch;
}

class cSearch : public QDialog
{
	Q_OBJECT

public:
	explicit cSearch(QWidget *parent = 0);
	~cSearch();

	qint32	id();
	QString	placeholderName();

	bool	placeholder();
	qint16	year();

private slots:
	void	on_m_lpSearchButton_clicked();
	void	on_m_lpSearch_textChanged(const QString &arg1);

	void	on_m_lpResults_clicked(const QModelIndex &index);
	void	on_m_lpPlaceholderName_textChanged(const QString &arg1);
	void	on_m_lpYear_valueChanged(int arg1);

private:
	Ui::cSearch *ui;

	void	setButtonBox();
};

#endif // CSEARCH_H
