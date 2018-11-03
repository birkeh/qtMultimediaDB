#include "cmoviediscover.h"
#include "ui_cmoviediscover.h"

#include "ccheckboxitemdelegate.h"
#include "cthemoviedbv3.h"

#include "cmovie.h"

#include <QStandardItem>
#include <QMap>
#include <QList>


cMovieDiscover::cMovieDiscover(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::cMovieDiscover)
{
	ui->setupUi(this);

	m_lpGenresModel				= new QStandardItemModel(0, 1);
	QStringList	headerLabels	= QStringList() << tr("Name");
	m_lpGenresModel->setHorizontalHeaderLabels(headerLabels);
	ui->m_lpGenres->setModel(m_lpGenresModel);
	ui->m_lpGenres->setItemDelegate(new cCheckBoxItemDelegate());
	ui->m_lpGenres->setWrapping(true);

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
	qint16			iYear	= ui->m_lpYear->value();
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

	cTheMovieDBV3			movieDB3;
	QList<cMovie*>			movieList	= movieDB3.discoverMovie(szText, bAdult, iYear, genres, voteMin, voteMax, "de-DE");

	m_lp
}

void cMovieDiscover::on_m_lpYearEnable_clicked(bool checked)
{
	ui->m_lpYear->setEnabled(checked);
}
