#include "cmoviedetails.h"
#include "ui_cmoviedetails.h"

#include "cmovieimage.h"


cMovieDetails::cMovieDetails(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::cMovieDetails)
{
	ui->setupUi(this);
}

cMovieDetails::~cMovieDetails()
{
	delete ui;
}

void cMovieDetails::setMovie(cMovie* lpMovie)
{
	ui->m_lpName->setText(lpMovie->movieTitle());
	ui->m_lpFirstAired->setDate(lpMovie->releaseDate());

	ui->m_lpDetailsBanner->clear();
	if(!lpMovie->backdropPath().isEmpty())
	{
		cMovieImage	image;
		QPixmap	banner	= image.getImage(lpMovie->backdropPath());
		ui->m_lpDetailsBanner->setPixmap(banner);
	}

	ui->m_lpDetailsOverview->setText(lpMovie->overview());

	ui->m_lpDetailsActors->clear();
	QTreeWidgetItem*	lpItem;
	for(int x = 0;x < lpMovie->cast().count();x++)
	{
		QStringList	str	= lpMovie->cast().at(x).split(",");
		lpItem	= new QTreeWidgetItem(ui->m_lpDetailsActors);
		lpItem->setText(0, str.at(0));
		lpItem->setText(1, str.at(1));
		ui->m_lpDetailsActors->addTopLevelItem(lpItem);
	}
	ui->m_lpDetailsActors->resizeColumnToContents(0);

	ui->m_lpDetailsGenre->clear();
	for(int x = 0;x < lpMovie->genres().count();x++)
	{
		lpItem	= new QTreeWidgetItem(ui->m_lpDetailsGenre);
		lpItem->setText(0, lpMovie->genres().at(x));
		ui->m_lpDetailsGenre->addTopLevelItem(lpItem);
	}
	ui->m_lpDetailsGenre->resizeColumnToContents(0);
}
