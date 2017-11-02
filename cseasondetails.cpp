#include "cseasondetails.h"
#include "ui_cseasondetails.h"

#include "cepisode.h"
#include "cepisodedetails.h"

#include "cmessageanimatedialog.h"

#include "cmovieimage.h"

#include <QDebug>


cSeasonDetails::cSeasonDetails(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::cSeasonDetails)
{
	ui->setupUi(this);
}

cSeasonDetails::~cSeasonDetails()
{
	delete ui;
}

void cSeasonDetails::setSeason(cSeason* lpSeason)
{
	ui->m_lpSeasonName->setText(lpSeason->name());
	ui->m_lpSeasonOverview->setText(lpSeason->overview());

	cMovieImage	image;
	QPixmap		poster		= image.getImage(lpSeason->posterPath());
	ui->m_lpSeasonPoster->setPixmap(poster.scaledToHeight(200));

	for(int x = 0;x < lpSeason->episodeList().count();x++)
	{
		cEpisode*			lpEpisode			= lpSeason->episodeList().at(x);
		cEpisodeDetails*	lpEpisodeDetails	= new cEpisodeDetails(ui->m_lpDetailsEpisodeTab);
		ui->m_lpDetailsEpisodeTab->addTab(lpEpisodeDetails, QString("Episode %1").arg(lpEpisode->episodeNumber()));
		lpEpisodeDetails->setEpisode(lpEpisode);
		if(!x)
			lpEpisodeDetails->loadImages();
	}
}

void cSeasonDetails::on_m_lpDetailsEpisodeTab_tabBarClicked(int index)
{
	cEpisodeDetails*		lpEpisodeDetails	= (cEpisodeDetails*)ui->m_lpDetailsEpisodeTab->widget(index);
	if(!lpEpisodeDetails)
		return;

	lpEpisodeDetails->loadImages();
}
