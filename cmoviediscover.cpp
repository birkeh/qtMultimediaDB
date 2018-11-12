#include "cmoviediscover.h"
#include "ui_cmoviediscover.h"

#include "ccheckboxitemdelegate.h"
#include "cthemoviedbv3.h"

#include <QStandardItem>
#include <QMap>
#include <QList>

#include <QDebug>


cMovieDiscover::cMovieDiscover(const cMovieList movieList, QWidget *parent) :
	QDialog(parent),
	ui(new Ui::cMovieDiscover),
	m_movieList(movieList)
{
	ui->setupUi(this);

	m_lpGenresModel				= new QStandardItemModel(0, 1);
	QStringList	headerLabels	= QStringList() << tr("Name");
	m_lpGenresModel->setHorizontalHeaderLabels(headerLabels);
	ui->m_lpGenres->setModel(m_lpGenresModel);
	ui->m_lpGenres->setItemDelegate(new cCheckBoxItemDelegate());
	ui->m_lpGenres->setWrapping(true);

	m_lpMoviesModel			= new QStandardItemModel(0, 1);
	ui->m_lpMovies->setModel(m_lpMoviesModel);

	headerLabels	= QStringList() << tr("Title") << tr("Year") << tr("Voting");
	m_lpMoviesModel->setHorizontalHeaderLabels(headerLabels);

	connect(ui->m_lpVoting, &QxtSpanSlider::spanChanged, this, &cMovieDiscover::spanChanged);

	ui->m_lpVoting->setRange(0, 100);
	ui->m_lpVoting->setLowerValue(0);
	ui->m_lpVoting->setUpperValue(100);

	cTheMovieDBV3			movieDB3;
	QMap<qint32, QString>	genres;

	genres	= movieDB3.genresMovie("de-DE");

	QMapIterator<qint32, QString>	iterator(genres);
	while(iterator.hasNext())
	{
		iterator.next();
		QStandardItem*	lpItem	= new QStandardItem(iterator.value());
		lpItem->setData(iterator.key());
		lpItem->setCheckable(true);

		m_lpGenresModel->appendRow(lpItem);
	}
}

cMovieDiscover::~cMovieDiscover()
{
	delete ui;
	delete m_lpGenresModel;
}

void cMovieDiscover::spanChanged(int lower, int upper)
{
	ui->m_lpVotingFrom->setText(QString::number((qreal)lower/10));
	ui->m_lpVotingTo->setText(QString::number((qreal)upper/10));
}

void cMovieDiscover::on_m_lpDiscover_clicked()
{
	QString			szText	= ui->m_lpText->text();
	bool			bAdult	= ui->m_lpIncludeAdult->isChecked();
	qint32			iYear	= ui->m_lpYear->value();
	qreal			voteMin	= (qreal)ui->m_lpVoting->lowerValue()/10;
	qreal			voteMax	= (qreal)ui->m_lpVoting->upperValue()/10;

	QList<qint32>	genres;

	if(!ui->m_lpYearEnable->isChecked())
		iYear		= -1;

	for(int x = 0;x < m_lpGenresModel->rowCount();x++)
	{
		QStandardItem*	lpItem	= m_lpGenresModel->item(x);

		if(lpItem->checkState() == Qt::Checked)
			genres.append(lpItem->data().toInt());
	}

	setCursor(Qt::WaitCursor);

	cTheMovieDBV3			movieDB3;
	QList<cMovie*>			movieList	= movieDB3.discoverMovie(szText, bAdult, iYear, genres, voteMin, voteMax, "de-DE");

	m_lpMoviesModel->clear();

	QStringList	headerLabels	= QStringList() << tr("Title") << tr("Year") << tr("Voting");
	m_lpMoviesModel->setHorizontalHeaderLabels(headerLabels);

	for(int x = 0; x < movieList.count();x++)
	{
		cMovie*	lpMovie	= movieList[x];

		if(m_movieList.find(lpMovie->movieID()))
			continue;
		QList<QStandardItem*>	items;

		items.append(new QStandardItem(lpMovie->movieTitle()));
		items.append(new QStandardItem(QString::number(lpMovie->releaseDate().year())));
		items.append(new QStandardItem(QString::number(lpMovie->voteAverage())));
		items[0]->setData(QVariant::fromValue(lpMovie));
		items[1]->setData(QVariant::fromValue(lpMovie));
		items[2]->setData(QVariant::fromValue(lpMovie));
		items[0]->setCheckable(true);

		m_lpMoviesModel->appendRow(items);
	}

	for(int x = 0;x < headerLabels.count();x++)
		ui->m_lpMovies->resizeColumnToContents(x);

	setCursor(Qt::ArrowCursor);
}

void cMovieDiscover::on_m_lpYearEnable_clicked(bool checked)
{
	ui->m_lpYear->setEnabled(checked);
}

void cMovieDiscover::on_m_lpMovies_clicked(const QModelIndex &index)
{
	setCursor(Qt::WaitCursor);

	QStandardItem*	lpItem	= m_lpMoviesModel->itemFromIndex(index);
	cMovie*			lpMovie	= lpItem->data().value<cMovie*>();

	if(lpMovie->cast().isEmpty())
	{
		cTheMovieDBV3	theMovieDB;
		theMovieDB.loadCastMovie(lpMovie);
	}
	ui->m_lpMovieDetails->setMovie(lpMovie);

	setCursor(Qt::ArrowCursor);
}

QList<qint32> cMovieDiscover::id()
{
	QList<qint32>	idList;

	for(int x = 0;x < m_lpMoviesModel->rowCount();x++)
	{
		if(m_lpMoviesModel->item(x, 0)->checkState() == Qt::Checked)
		{
			cMovie*	lpMovie	= m_lpMoviesModel->item(x, 0)->data().value<cMovie*>();
			idList.append(lpMovie->movieID());
		}
	}

	return(idList);
}
