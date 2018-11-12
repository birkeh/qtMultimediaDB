#include "cseriedetails.h"
#include "ui_cseriedetails.h"

#include "cmovieimage.h"


cSerieDetails::cSerieDetails(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::cSerieDetails),
	m_lpActorsModel(0),
	m_lpGenreModel(0)
{
	ui->setupUi(this);

	m_lpActorsModel	= new QStandardItemModel(0, 0);
	ui->m_lpDetailsActors->setModel(m_lpActorsModel);

	m_lpGenreModel	= new QStandardItemModel(0, 0);
	ui->m_lpDetailsGenre->setModel(m_lpGenreModel);
}

cSerieDetails::~cSerieDetails()
{
	delete m_lpActorsModel;
	delete m_lpGenreModel;

	delete ui;
}

void cSerieDetails::setSerie(cSerie* lpSerie)
{
	ui->m_lpName->setText(lpSerie->seriesName());
	ui->m_lpFirstAired->setDate(lpSerie->firstAired());
	ui->m_lpVoting->setText(QString::number(lpSerie->voteAverage()));

	ui->m_lpDetailsBanner->clear();
	if(!lpSerie->backdropPath().isEmpty())
	{
		cMovieImage	image;
		QPixmap		banner	= image.getImage(lpSerie->backdropPath());
		ui->m_lpDetailsBanner->setPixmap(banner);
	}

	ui->m_lpDetailsOverview->setText(lpSerie->overview());

	m_lpActorsModel->clear();
	for(int x = 0;x < lpSerie->cast().count();x++)
	{
		QList<QStandardItem*>	items;
		QStringList				str	= lpSerie->cast().at(x).split(",");

		items.append(new QStandardItem(str.at(0)));
		items.append(new QStandardItem(str.at(1)));
		m_lpActorsModel->appendRow(items);
	}
	ui->m_lpDetailsActors->resizeColumnToContents(0);

	m_lpGenreModel->clear();
	for(int x = 0;x < lpSerie->genre().count();x++)
		m_lpGenreModel->appendRow(new QStandardItem(lpSerie->genre().at(x)));

	ui->m_lpDetailsGenre->resizeColumnToContents(0);
}
