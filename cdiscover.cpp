#include "cdiscover.h"
#include "ui_cdiscover.h"

#include "ccheckboxitemdelegate.h"
#include "cthemoviedbv3.h"

#include <QStandardItem>
#include <QMap>
#include <QList>

#include <QDebug>


cDiscover::cDiscover(const cSerieList serieList, QWidget *parent) :
	QDialog(parent),
	ui(new Ui::cDiscover),
	m_serieList(serieList)
{
	ui->setupUi(this);

	m_lpGenresModel				= new QStandardItemModel(0, 1);
	QStringList	headerLabels	= QStringList() << tr("Name");
	m_lpGenresModel->setHorizontalHeaderLabels(headerLabels);
	ui->m_lpGenres->setModel(m_lpGenresModel);
	ui->m_lpGenres->setItemDelegate(new cCheckBoxItemDelegate());
	ui->m_lpGenres->setWrapping(true);

	m_lpSeriesModel			= new QStandardItemModel(0, 1);
	ui->m_lpSeries->setModel(m_lpSeriesModel);

	headerLabels	= QStringList() << tr("Title") << tr("Year") << tr("Voting");
	m_lpSeriesModel->setHorizontalHeaderLabels(headerLabels);

	connect(ui->m_lpVoting, &QxtSpanSlider::spanChanged, this, &cDiscover::spanChanged);

	ui->m_lpVoting->setRange(0, 100);
	ui->m_lpVoting->setLowerValue(0);
	ui->m_lpVoting->setUpperValue(100);

	cTheMovieDBV3			movieDB3;
	QMap<qint32, QString>	genres;

	genres	= movieDB3.genresSerie("de-DE");

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

cDiscover::~cDiscover()
{
	delete ui;
	delete m_lpGenresModel;
}

void cDiscover::spanChanged(int lower, int upper)
{
	ui->m_lpVotingFrom->setText(QString::number((qreal)lower/10));
	ui->m_lpVotingTo->setText(QString::number((qreal)upper/10));
}

void cDiscover::on_m_lpDiscover_clicked()
{
	QString			szText	= ui->m_lpText->text();
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
	QList<cSerie*>			serieList	= movieDB3.discoverSerie(szText, iYear, genres, voteMin, voteMax, "de-DE");

	m_lpSeriesModel->clear();

	QStringList	headerLabels	= QStringList() << tr("Title") << tr("Year") << tr("Voting");
	m_lpSeriesModel->setHorizontalHeaderLabels(headerLabels);

	for(int x = 0; x < serieList.count();x++)
	{
		cSerie*	lpSerie	= serieList[x];

		if(m_serieList.find(lpSerie->seriesID()))
			continue;
		QList<QStandardItem*>	items;

		items.append(new QStandardItem(lpSerie->seriesName()));
		items.append(new QStandardItem(QString::number(lpSerie->firstAired().year())));
		items.append(new QStandardItem(QString::number(lpSerie->voteAverage())));
		items[0]->setData(QVariant::fromValue(lpSerie));
		items[1]->setData(QVariant::fromValue(lpSerie));
		items[2]->setData(QVariant::fromValue(lpSerie));
		items[0]->setCheckable(true);

		m_lpSeriesModel->appendRow(items);
	}

	for(int x = 0;x < headerLabels.count();x++)
		ui->m_lpSeries->resizeColumnToContents(x);

	setCursor(Qt::ArrowCursor);
}

void cDiscover::on_m_lpYearEnable_clicked(bool checked)
{
	ui->m_lpYear->setEnabled(checked);
}

void cDiscover::on_m_lpSeries_clicked(const QModelIndex &index)
{
	setCursor(Qt::WaitCursor);

	QStandardItem*	lpItem	= m_lpSeriesModel->itemFromIndex(index);
	cSerie*			lpSerie	= lpItem->data().value<cSerie*>();

	if(lpSerie->cast().isEmpty())
	{
		cTheMovieDBV3	theMovieDB;
		theMovieDB.loadCastSerie(lpSerie);
	}
	ui->m_lpSerieDetails->setSerie(lpSerie);

	setCursor(Qt::ArrowCursor);
}

QList<qint32> cDiscover::id()
{
	QList<qint32>	idList;

	for(int x = 0;x < m_lpSeriesModel->rowCount();x++)
	{
		if(m_lpSeriesModel->item(x, 0)->checkState() == Qt::Checked)
		{
			cSerie*	lpSerie	= m_lpSeriesModel->item(x, 0)->data().value<cSerie*>();
			idList.append(lpSerie->seriesID());
		}
	}

	return(idList);
}
