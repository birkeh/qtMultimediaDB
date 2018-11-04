#include "cmoviesearch.h"
#include "ui_cmoviesearch.h"

#include "cthemoviedbv3.h"

#include "cmovie.h"
#include "cmessageanimatedialog.h"

#include <QList>



cMovieSearch::cMovieSearch(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::cMovieSearch)
{
	ui->setupUi(this);
	ui->m_lpSearchButton->setEnabled(false);
	ui->m_lpTabWidget->setCurrentIndex(0);

	ui->m_lpButtonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
	ui->m_lpSearch->setFocus();
	ui->m_lpSearchButton->setDefault(true);
}

cMovieSearch::~cMovieSearch()
{
	delete ui;
}

void cMovieSearch::on_m_lpSearch_textChanged(const QString &/*arg1*/)
{
	if(ui->m_lpSearch->text().isEmpty())
		ui->m_lpSearchButton->setEnabled(false);
	else
		ui->m_lpSearchButton->setEnabled(true);
}

void cMovieSearch::on_m_lpSearchButton_clicked()
{
	cMessageAnimateDialog*	lpDialog	= new cMessageAnimateDialog(this);
	lpDialog->setTitle("Search");
	lpDialog->setMessage("Searching");
	lpDialog->show();

	cTheMovieDBV3		theMovieDBV3;
	QString				szSearchText	= ui->m_lpSearch->text();
	qint16				iYear			= -1;

	if(szSearchText.contains("(") && szSearchText.contains(")"))
	{
		QString	tmp	= szSearchText.mid(szSearchText.indexOf("(")+1);
		if(tmp.contains(")"))
		{
			tmp		= tmp.left(tmp.indexOf(")"));
			iYear	= tmp.toInt();

			szSearchText	= szSearchText.left(szSearchText.indexOf("(")-1);
		}
	}

	QList<cMovie*>		movieList	= theMovieDBV3.searchMovie(szSearchText, iYear, "de-DE");

	ui->m_lpResults->clear();

	for(int z = 0;z < movieList.count();z++)
	{
		cMovie*	lpMovie	= movieList.at(z);
		QTreeWidgetItem*	lpNew		= new QTreeWidgetItem(ui->m_lpResults);
		lpNew->setText(0, lpMovie->movieTitle());
		lpNew->setText(1, QString("%1").arg(lpMovie->releaseDate().year()));
		lpNew->setData(0, Qt::UserRole, QVariant::fromValue(lpMovie));
		lpNew->setData(1, Qt::UserRole, QVariant::fromValue(lpMovie));
		lpNew->setCheckState(0, Qt::Unchecked);

		ui->m_lpResults->addTopLevelItem(lpNew);
	}
	ui->m_lpResults->resizeColumnToContents(0);
	ui->m_lpResults->resizeColumnToContents(1);

	ui->m_lpResults->sortItems(0, Qt::AscendingOrder);

	delete lpDialog;
}

QList<qint32> cMovieSearch::id()
{
	QList<qint32>	idList;

	for(int x = 0;x < ui->m_lpResults->topLevelItemCount();x++)
	{
		if(ui->m_lpResults->topLevelItem(x)->checkState(0) == Qt::Checked)
		{
			cMovie*	lpMovie	= ui->m_lpResults->topLevelItem(x)->data(0, Qt::UserRole).value<cMovie*>();
			idList.append(lpMovie->movieID());
		}
	}

	if(idList.isEmpty())
	{
		qint32	iID	= ui->m_lpSearch->text().toInt();
		if(iID)
			idList.append(iID);
		return(idList);
	}
	return(idList);
}

QString cMovieSearch::placeholderName()
{
	return(ui->m_lpPlaceholderName->text());
}

bool cMovieSearch::placeholder()
{
	return(ui->m_lpTabWidget->currentIndex() == 1);
}

qint16 cMovieSearch::year()
{
	return(ui->m_lpYear->value());
}

void cMovieSearch::on_m_lpResults_clicked(const QModelIndex &/*index*/)
{
	setButtonBox();
}

void cMovieSearch::on_m_lpPlaceholderName_textChanged(const QString &/*arg1*/)
{
	setButtonBox();
}

void cMovieSearch::on_m_lpYear_valueChanged(int /*arg1*/)
{
	setButtonBox();
}

void cMovieSearch::setButtonBox()
{
	if(ui->m_lpTabWidget->currentIndex() == 0)
	{
		ui->m_lpButtonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
		for(int x = 0;x < ui->m_lpResults->topLevelItemCount();x++)
		{
			if(ui->m_lpResults->topLevelItem(x)->checkState(0) == Qt::Checked)
			{
				ui->m_lpButtonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
				return;
			}
		}
	}

	if(ui->m_lpPlaceholderName->text().isEmpty())
	{
		ui->m_lpButtonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
		return;
	}

	if(ui->m_lpYear->value() == 0)
	{
		ui->m_lpButtonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
		return;
	}

	ui->m_lpButtonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
}

//void cMovieSearch::on_m_lpResults_doubleClicked(const QModelIndex &index)
//{
//	if(index.isValid())
//		accept();
//}

void cMovieSearch::on_m_lpResults_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
	cMovie*	lpMovie	= current->data(0, Qt::UserRole).value<cMovie*>();

	if(lpMovie->cast().isEmpty())
	{
		cTheMovieDBV3	theMovieDB;
		theMovieDB.loadCastMovie(lpMovie);
	}
	ui->m_lpMovieDetails->setMovie(lpMovie);
}
