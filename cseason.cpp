#include "cseason.h"

#define DELETE(x) { if(x) delete x; x=nullptr; }

cSeason::cSeason() :
	m_i_ID(-1),
	m_airDate(QDate(1900, 1, 1)),
	m_szName(""),
	m_szOverview(""),
	m_iID(-1),
	m_szPosterPath(""),
	m_iSeasonNumber(-1),
	m_lpGroupBox(nullptr),
	m_lpGridLayout(nullptr),
	m_lpGrid(nullptr),
	m_lpLabel1(nullptr),
	m_lpAllInit(nullptr),
	m_lpAllProgress(nullptr),
	m_lpAllDone(nullptr),
	m_lpSpacer(nullptr),
	m_lpSerie(nullptr)

{
}

cSeason::~cSeason()
{
	deleteResources();
}

void cSeason::set_ID(const qint32& _iID)
{
	m_i_ID	= _iID;
}

qint32 cSeason::_id()
{
	return(m_i_ID);
}

void cSeason::setAirDate(const QString& szAirDate)
{
	m_airDate	= QDate::fromString(szAirDate, "yyyy-MM-dd");
}

void cSeason::setAirDate(const QDate& airDate)
{
	m_airDate	= airDate;
}

QDate cSeason::airDate()
{
	return(m_airDate);
}

void cSeason::setName(const QString& szName)
{
	m_szName	= szName;
}

QString cSeason::name()
{
	return(m_szName);
}

void cSeason::setOverview(const QString& szOverview)
{
	m_szOverview	= szOverview;
}

QString cSeason::overview()
{
	return(m_szOverview);
}

void cSeason::setID(const qint32& iID)
{
	m_iID	= iID;
}

qint32 cSeason::id()
{
	return(m_iID);
}

void cSeason::setPosterPath(const QString& szPosterPath)
{
	m_szPosterPath	= szPosterPath;
}

QString cSeason::posterPath()
{
	return(m_szPosterPath);
}

void cSeason::setSeasonNumber(const qint32& iSeasonNumber)
{
	m_iSeasonNumber	= iSeasonNumber;
}

qint32 cSeason::seasonNumber()
{
	return(m_iSeasonNumber);
}

void cSeason::setSerie(cSerie* lpSerie)
{
	m_lpSerie	= lpSerie;
}

cSerie* cSeason::serie()
{
	return(m_lpSerie);
}

cEpisode* cSeason::addEpisode(qint32 iNumber)
{
	cEpisode*	lpNew	= new cEpisode;
	lpNew->setEpisodeNumber(iNumber);
	lpNew->setState(cEpisode::StateInit);
	m_episodeList.append(lpNew);
	return(lpNew);
}

cEpisode* cSeason::addEpisode(cEpisode* lpEpisode)
{
	if(episodeList().contains(lpEpisode))
		return(nullptr);
	m_episodeList.append(lpEpisode);
	return(lpEpisode);
}

QList<cEpisode*> cSeason::episodeList()
{
	return(m_episodeList);
}

cEpisode* cSeason::findEpisode(qint32 iNumber)
{
	for(int x = 0;x < m_episodeList.count();x++)
	{
		if(m_episodeList.at(x)->episodeNumber() == iNumber)
			return(m_episodeList.at(x));
	}
	return(nullptr);
}

qint32 cSeason::episodeCount()
{
	qint32	iTotal = -1;
	for(int z = 0;z < m_episodeList.count();z++)
	{
		cEpisode*	lpEpisode	= m_episodeList.at(z);
		if(lpEpisode)
		{
			if(lpEpisode->episodeNumber() > iTotal)
				iTotal	= lpEpisode->episodeNumber();
		}
	}
	return(iTotal);
}

void cSeason::setGroupBox(QGroupBox* lpGroupBox)
{
	m_lpGroupBox	= lpGroupBox;
}

void cSeason::setGridLayout(QGridLayout* lpGridLayout)
{
	m_lpGridLayout	= lpGridLayout;
}

void cSeason::setGrid(QGridLayout* lpGrid)
{
	m_lpGrid	= lpGrid;
}

void cSeason::setLabel1(QLabel* lpLabel1)
{
	m_lpLabel1	= lpLabel1;
}

bool cSeason::hasInit()
{
	for(int x = 0;x < m_episodeList.count();x++)
	{
		cEpisode*	lpEpisode	= m_episodeList.at(x);
		if(lpEpisode->state() == cEpisode::StateInit)
			return(true);
	}
	return(false);
}

bool cSeason::hasProgress()
{
	for(int x = 0;x < m_episodeList.count();x++)
	{
		cEpisode*	lpEpisode	= m_episodeList.at(x);
		if(lpEpisode->state() == cEpisode::StateProgress)
			return(true);
	}
	return(false);
}

bool cSeason::hasDone()
{
	for(int x = 0;x < m_episodeList.count();x++)
	{
		cEpisode*	lpEpisode	= m_episodeList.at(x);
		if(lpEpisode->state() == cEpisode::StateDone)
			return(true);
	}
	return(false);
}

void cSeason::setAllInit(QPushButton* lpAllInit)
{
	m_lpAllInit	= lpAllInit;
}

void cSeason::setAllProgress(QPushButton* lpAllProgress)
{
	m_lpAllProgress	= lpAllProgress;
}

void cSeason::setAllDone(QPushButton* lpAllDone)
{
	m_lpAllDone	= lpAllDone;
}

void cSeason::setSpacer(QSpacerItem* lpSpacer)
{
	m_lpSpacer	= lpSpacer;
}

void cSeason::deleteResources()
{
	DELETE(m_lpGroupBox);
	DELETE(m_lpGridLayout);
	DELETE(m_lpGrid);
	DELETE(m_lpLabel1);
	DELETE(m_lpAllInit);
	DELETE(m_lpAllProgress);
	DELETE(m_lpAllDone);
	DELETE(m_lpSpacer);

	for(int z = 0;z < m_episodeList.count();z++)
		m_episodeList.at(z)->deleteResources();
}

void cSeason::updateState()
{
	for(int z = 0;z < m_episodeList.count();z++)
		m_episodeList.at(z)->updateState();
}

void cSeason::allInit()
{
	for(int z = 0;z < m_episodeList.count();z++)
		m_episodeList.at(z)->setState(cEpisode::StateInit);
}

void cSeason::allProgress()
{
	for(int z = 0;z < m_episodeList.count();z++)
		m_episodeList.at(z)->setState(cEpisode::StateProgress);
}

void cSeason::allDone()
{
	for(int z = 0;z < m_episodeList.count();z++)
		m_episodeList.at(z)->setState(cEpisode::StateDone);
}

QPushButton* cSeason::allInitButton()
{
	return(m_lpAllInit);
}

QPushButton* cSeason::allProgressButton()
{
	return(m_lpAllProgress);
}

QPushButton* cSeason::allDoneButton()
{
	return(m_lpAllDone);
}
