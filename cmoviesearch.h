#ifndef CMOVIESEARCH_H
#define CMOVIESEARCH_H

#include <QDialog>
#include <QList>
#include <QTreeWidgetItem>


namespace Ui {
class cMovieSearch;
}

class cMovieSearch : public QDialog
{
	Q_OBJECT

public:
	explicit cMovieSearch(QWidget *parent = 0);
	~cMovieSearch();

	QList<qint32>	id();
	QString			placeholderName();

	bool	placeholder();
	qint16	year();

private slots:
	void	on_m_lpSearchButton_clicked();

	void	on_m_lpSearch_textChanged(const QString &arg1);
	void	on_m_lpPlaceholderName_textChanged(const QString &arg1);
	void	on_m_lpYear_valueChanged(int arg1);

	void	on_m_lpResults_clicked(const QModelIndex &index);
//	void	on_m_lpResults_doubleClicked(const QModelIndex &index);

	void on_m_lpResults_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);

private:
	Ui::cMovieSearch *ui;

	void	setButtonBox();
};

#endif // CMOVIESEARCH_H
