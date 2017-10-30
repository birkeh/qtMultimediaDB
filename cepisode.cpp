#include "cepisode.h"
#include "common.h"


#define DELETE(x) { if(x) delete x;x = 0;}

cEpisode::cEpisode() :
	m_iID(-1),
	m_szName(""),
	m_iEpisodeNumber(-1),
	m_airDate(QDate(1900, 1, 1)),
	m_szOverview(""),
	m_szProductionCode(""),
	m_iSeasonNumber(-1),
	m_iSeasonID(-1),
	m_iSeriesID(-1),
	m_szStillPath(""),
	m_dVoteAverage(-1.0),
	m_iVoteCount(-1),
//	m_szFileName(""),
//	m_iThumbHeight(-1),
//	m_iThumbWidth(-1),
	m_state(cEpisode::StateInit),
	m_lpGroup(0),
	m_lpLabel(0),
	m_lpButton1(0),
	m_lpButton2(0),
	m_lpButton3(0)
{
}

cEpisode::~cEpisode()
{
	deleteResources();
}

void cEpisode::setID(const qint32& iID)
{
	m_iID	= iID;
}

qint32 cEpisode::id()
{
	return(m_iID);
}

void cEpisode::setName(const QString& szName)
{
	m_szName	= szName;
}

QString cEpisode::name()
{
	return(m_szName);
}

void cEpisode::setEpisodeNumber(const qint16& iEpisodeNumber)
{
	m_iEpisodeNumber	= iEpisodeNumber;
}

qint16 cEpisode::episodeNumber()
{
	return(m_iEpisodeNumber);
}

void cEpisode::setAirDate(const QString& szAirDate)
{
	m_airDate	= QDate::fromString(szAirDate, "yyyy-MM-dd");
}

void cEpisode::setAirDate(const QDate& airDate)
{
	m_airDate	= airDate;
}

QDate cEpisode::airDate()
{
	return(m_airDate);
}

void cEpisode::setGuestStars(const QString& szGuestStars)
{
	m_szGuestStars	= szGuestStars.split("|");
}

void cEpisode::setGuestStars(const QStringList& szGuestStars)
{
	m_szGuestStars	= cleanList(szGuestStars);
}

QStringList cEpisode::guestStars()
{
	return(m_szGuestStars);
}

void cEpisode::setOverview(const QString& szOverview)
{
	m_szOverview	= szOverview;
}

QString cEpisode::overview()
{
	return(m_szOverview);
}

void cEpisode::setProductionCode(const QString& szProductionCode)
{
	m_szProductionCode	= szProductionCode;
}

QString cEpisode::productionCode()
{
	return(m_szProductionCode);
}

void cEpisode::setSeasonNumber(const qint16& iSeasonNumber)
{
	m_iSeasonNumber	= iSeasonNumber;
}

qint16 cEpisode::seasonNumber()
{
	return(m_iSeasonNumber);
}

void cEpisode::setSeasonID(const qint32& iSeasonID)
{
	m_iSeasonID	= iSeasonID;
}

qint32 cEpisode::seasonID()
{
	return(m_iSeasonID);
}

void cEpisode::setSeriesID(const qint32& iSeriesID)
{
	m_iSeriesID	= iSeriesID;
}

qint32 cEpisode::seriesID()
{
	return(m_iSeriesID);
}

void cEpisode::setStillPath(const QString& szStillPath)
{
	m_szStillPath	= szStillPath;
}

QString cEpisode::stillPath()
{
	return(m_szStillPath);
}

void cEpisode::setVoteAverage(const qreal& dVoteAverage)
{
	m_dVoteAverage	= dVoteAverage;
}

qreal cEpisode::voteAverage()
{
	return(m_dVoteAverage);
}

void cEpisode::setVoteCount(const qint16& iVoteCount)
{
	m_iVoteCount	= iVoteCount;
}

qint16 cEpisode::voteCount()
{
	return(m_iVoteCount);
}

void cEpisode::setCrew(const QString& szCrew)
{
	m_szCrew	= szCrew.split("|");
}

void cEpisode::setCrew(const QStringList& szCrew)
{
	m_szCrew	= szCrew;
}

QStringList cEpisode::crew()
{
	return(m_szCrew);
}

void cEpisode::setState(const State& state)
{
	m_state		= state;
	switch(m_state)
	{
	case StateInit:
		if(m_lpButton1)
			m_lpButton1->setChecked(true);
		if(m_lpButton2)
			m_lpButton2->setChecked(false);
		if(m_lpButton3)
			m_lpButton3->setChecked(false);
		break;
	case StateProgress:
		if(m_lpButton2)
			m_lpButton2->setChecked(true);
		if(m_lpButton1)
			m_lpButton1->setChecked(false);
		if(m_lpButton3)
			m_lpButton3->setChecked(false);
		break;
	case StateDone:
		if(m_lpButton3)
			m_lpButton3->setChecked(true);
		if(m_lpButton1)
			m_lpButton1->setChecked(false);
		if(m_lpButton2)
			m_lpButton2->setChecked(false);
		break;
	default:
		break;
	}
}

cEpisode::State cEpisode::state()
{
	return(m_state);
}
/*
void cEpisode::setFileName(const QString& szFileName)
{
	m_szFileName	= szFileName;
}

QString cEpisode::fileName()
{
	return(m_szFileName);
}

void cEpisode::setThumbHeight(const qint16& iThumbHeight)
{
	m_iThumbHeight	= iThumbHeight;
}

qint16 cEpisode::thumbHeight()
{
	return(m_iThumbHeight);
}

void cEpisode::setThumbWidth(const qint16& iThumbWidth)
{
	m_iThumbWidth	= iThumbWidth;
}

qint16 cEpisode::thumbWidth()
{
	return(m_iThumbWidth);
}
*/
bool cEpisode::isValid()
{
	if(m_iSeasonID != -1 && m_iEpisodeNumber != -1 && m_iSeasonNumber != -1)
		return(true);
	return(false);
}

void cEpisode::setGroup(QButtonGroup* lpGroup)
{
	m_lpGroup	= lpGroup;
}

void cEpisode::setLabel(QLabel* lpLabel)
{
	m_lpLabel	= lpLabel;
}

void cEpisode::setButton1(QRadioButton* lpButton1)
{
	m_lpButton1	= lpButton1;
}

void cEpisode::setButton2(QRadioButton* lpButton2)
{
	m_lpButton2	= lpButton2;
}

void cEpisode::setButton3(QRadioButton* lpButton3)
{
	m_lpButton3	= lpButton3;
}

void cEpisode::updateState()
{
	if(m_lpButton1)
	{
		if(m_lpButton1->isChecked())
			m_state	= StateInit;
	}
	if(m_lpButton2)
	{
		if(m_lpButton2->isChecked())
			m_state	= StateProgress;
	}
	if(m_lpButton3)
	{
		if(m_lpButton3->isChecked())
			m_state	= StateDone;
	}
}

void cEpisode::deleteResources()
{
	DELETE(m_lpGroup);
	DELETE(m_lpLabel);
	DELETE(m_lpButton1);
	DELETE(m_lpButton2);
	DELETE(m_lpButton3);
}
