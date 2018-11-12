#include "cmoviesearch.h"
#include "ui_cmoviesearch.h"

#include "cthemoviedbv3.h"

#include "cmovie.h"
#include "cmessageanimatedialog.h"

#include <QList>


cMovieSearch::cMovieSearch(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::cMovieSearch),
	m_lpResultsModel(0)
{
	ui->setupUi(this);
	ui->m_lpSearchButton->setEnabled(false);
	ui->m_lpTabWidget->setCurrentIndex(0);

	ui->m_lpButtonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
	ui->m_lpSearch->setFocus();
	ui->m_lpSearchButton->setDefault(true);

	m_lpResultsModel	= new QStandardItemModel(0, 0);
	ui->m_lpResults->setModel(m_lpResultsModel);
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
	setCursor(Qt::WaitCursor);

	cMessageAnimateDialog*	lpDialog	= new cMessageAnimateDialog(this);
	lpDialog->setTitle("Search");
	lpDialog->setMessage("Searching");
	lpDialog->show();

	cTheMovieDBV3		theMovieDBV3;
	QString				szSearchText	= ui->m_lpSearch->text();
	qint32				iYear			= -1;

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

	m_lpResultsModel->clear();
	QStringList	headerLabels	= QStringList() << tr("Title") << tr("Year");
	m_lpResultsModel->setHorizontalHeaderLabels(headerLabels);

	for(int z = 0;z < movieList.count();z++)
	{
		cMovie*	lpMovie	= movieList.at(z);

		QList<QStandardItem*>	items;

		items.append(new QStandardItem(lpMovie->movieTitle()));
		items.append(new QStandardItem(QString::number(lpMovie->releaseDate().year())));
		items[0]->setData(QVariant::fromValue(lpMovie));
		items[1]->setData(QVariant::fromValue(lpMovie));
		items[0]->setCheckable(true);

		m_lpResultsModel->appendRow(items);
	}

	for(int x = 0;x < headerLabels.count();x++)
		ui->m_lpResults->resizeColumnToContents(x);

	m_lpResultsModel->sort(0, Qt::AscendingOrder);

	delete lpDialog;

	setCursor(Qt::ArrowCursor);
}

QList<qint32> cMovieSearch::id()
{
	QList<qint32>	idList;

	for(int x = 0;x < m_lpResultsModel->rowCount();x++)
	{
		if(m_lpResultsModel->item(x, 0)->checkState() == Qt::Checked)
		{
			cMovie*	lpMovie	= m_lpResultsModel->item(x, 0)->data().value<cMovie*>();
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

qint32 cMovieSearch::year()
{
	return(ui->m_lpYear->value());
}

void cMovieSearch::on_m_lpResults_clicked(const QModelIndex& index)
{
	setCursor(Qt::WaitCursor);

	cMovie*	lpMovie	= m_lpResultsModel->itemFromIndex(index)->data().value<cMovie*>();

	if(lpMovie->cast().isEmpty())
	{
		cTheMovieDBV3	theMovieDB;
		theMovieDB.loadCastMovie(lpMovie);
	}
	ui->m_lpMovieDetails->setMovie(lpMovie);

	setButtonBox();

	setCursor(Qt::ArrowCursor);
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
		for(int x = 0;x < m_lpResultsModel->rowCount();x++)
		{
			if(m_lpResultsModel->item(x, 0)->checkState() == Qt::Checked)
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
