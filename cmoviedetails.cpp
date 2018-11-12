#include "cmoviedetails.h"
#include "ui_cmoviedetails.h"

#include "cmovieimage.h"


cMovieDetails::cMovieDetails(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::cMovieDetails),
	m_lpActorsModel(0),
	m_lpGenreModel(0)
{
	ui->setupUi(this);

	m_lpActorsModel	= new QStandardItemModel(0, 0);
	ui->m_lpDetailsActors->setModel(m_lpActorsModel);

	m_lpGenreModel	= new QStandardItemModel(0, 9);
	ui->m_lpDetailsGenre->setModel(m_lpGenreModel);
}

cMovieDetails::~cMovieDetails()
{
	delete m_lpActorsModel;
	delete m_lpGenreModel;

	delete ui;
}

void cMovieDetails::setMovie(cMovie* lpMovie)
{
	ui->m_lpName->setText(lpMovie->movieTitle());
	ui->m_lpFirstAired->setDate(lpMovie->releaseDate());
	ui->m_lpVoting->setText(QString::number(lpMovie->voteAverage()));

			ui->m_lpDetailsBanner->clear();
	if(!lpMovie->backdropPath().isEmpty())
	{
		cMovieImage	image;
		QPixmap	banner	= image.getImage(lpMovie->backdropPath());
		ui->m_lpDetailsBanner->setPixmap(banner);
	}

	ui->m_lpDetailsOverview->setText(lpMovie->overview());

	m_lpActorsModel->clear();
	for(int x = 0;x < lpMovie->cast().count();x++)
	{
		QList<QStandardItem*>	items;
		QStringList				str	= lpMovie->cast().at(x).split(",");

		items.append(new QStandardItem(str.at(0)));
		items.append(new QStandardItem(str.at(1)));
		m_lpActorsModel->appendRow(items);
	}
	ui->m_lpDetailsActors->resizeColumnToContents(0);

	m_lpGenreModel->clear();
	for(int x = 0;x < lpMovie->genres().count();x++)
		m_lpGenreModel->appendRow(new QStandardItem(lpMovie->genres().at(x)));

	ui->m_lpDetailsGenre->resizeColumnToContents(0);
}
