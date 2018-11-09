#include "cartist.h"


cArtist::cArtist() :
	m_iArtistID(0),
	m_szArtist(QString("")),
	m_szArtistStripped(QString("")),
	m_szArtistAlernate(QString("")),
	m_szLabel(QString("")),
	m_iLabelID(0),
	m_iFormedYear(0),
	m_iBornYear(0),
	m_iDiedYear(0),
	m_szDisbanded(QString("")),
	m_szStyle(QString("")),
	m_szGenre(QString("")),
	m_szMood(QString("")),
	m_szWebsite(QString("")),
	m_szFacebook(QString("")),
	m_szTwitter(QString("")),
	m_szBiography(QString("")),
	m_szGender(QString("")),
	m_iMembers(0),
	m_szCountry(QString("")),
	m_szCountryCode(QString("")),
	m_szArtistThumb(QString("")),
	m_szArtistLogo(QString("")),
	m_szArtistClearart(QString("")),
	m_szArtistWideThumb(QString("")),
	m_szArtistFanart(QString("")),
	m_szArtistFanart2(QString("")),
	m_szArtistFanart3(QString("")),
	m_szArtistBanner(QString("")),
	m_szMusicBrainzID(QString("")),
	m_szLastFMChart(QString(""))
{
}

void cArtist::setArtistID(const qint32& iArtistID)
{
	m_iArtistID	= iArtistID;
}

qint32 cArtist::artistID()
{
	return(m_iArtistID);
}

void cArtist::setArtist(const QString& szArtist)
{
	m_szArtist	= szArtist;
}

QString cArtist::artist()
{
	return(m_szArtist);
}

void cArtist::setArtistStripped(const QString& szArtistStripped)
{
	m_szArtistStripped	= szArtistStripped;
}

QString cArtist::artistStripped()
{
	return(m_szArtistStripped);
}

void cArtist::setArtistAlernate(const QString& szArtistAlernate)
{
	m_szArtistAlernate	= szArtistAlernate;
}

QString cArtist::artistAlernate()
{
	return(m_szArtistAlernate);
}

void cArtist::setLabel(const QString& szLabel)
{
	m_szLabel	= szLabel;
}

QString cArtist::label()
{
	return(m_szLabel);
}

void cArtist::setLabelID(const qint32& iLabelID)
{
	m_iLabelID	= iLabelID;
}

qint32 cArtist::labelID()
{
	return(m_iLabelID);
}

void cArtist::setFormedYear(const qint32& iFormedYear)
{
	m_iFormedYear	= iFormedYear;
}

qint32 cArtist::formedYear()
{
	return(m_iFormedYear);
}

void cArtist::setBornYear(const qint32& iBornYear)
{
	m_iBornYear	= iBornYear;
}

qint32 cArtist::bornYear()
{
	return(m_iBornYear);
}

void cArtist::setDiedYear(const qint32& iDiedYear)
{
	m_iDiedYear	= iDiedYear;
}

qint32 cArtist::diedYear()
{
	return(m_iDiedYear);
}

void cArtist::setDisbanded(const QString& szDisbanded)
{
	m_szDisbanded	= szDisbanded;
}

QString cArtist::disbanded()
{
	return(m_szDisbanded);
}

void cArtist::setStyle(const QString& szStyle)
{
	m_szStyle	= szStyle;
}

QString cArtist::style()
{
	return(m_szStyle);
}

void cArtist::setGenre(const QString& szGenre)
{
	m_szGenre	= szGenre;
}

QString cArtist::genre()
{
	return(m_szGenre);
}

void cArtist::setMood(const QString& szMood)
{
	m_szMood	= szMood;
}

QString cArtist::mood()
{
	return(m_szMood);
}

void cArtist::setWebsite(const QString& szWebsite)
{
	m_szWebsite	= szWebsite;
}

QString cArtist::website()
{
	return(m_szWebsite);
}

void cArtist::setFacebook(const QString& szFacebook)
{
	m_szFacebook	= szFacebook;
}

QString cArtist::facebook()
{
	return(m_szFacebook);
}

void cArtist::setTwitter(const QString& szTwitter)
{
	m_szTwitter	= szTwitter;
}

QString cArtist::twitter()
{
	return(m_szTwitter);
}

void cArtist::setBiography(const QString& szBiography)
{
	m_szBiography	= szBiography;
}

QString cArtist::biography()
{
	return(m_szBiography);
}

void cArtist::setGender(const QString& szGender)
{
	m_szGender	= szGender;
}

QString cArtist::gender()
{
	return(m_szGender);
}

void cArtist::setMembers(const qint32& iMembers)
{
	m_iMembers	= iMembers;
}

qint32 cArtist::members()
{
	return(m_iMembers);
}

void cArtist::setCountry(const QString& szCountry)
{
	m_szCountry	= szCountry;
}

QString cArtist::country()
{
	return(m_szCountry);
}

void cArtist::setCountryCode(const QString& szCountryCode)
{
	m_szCountryCode	= szCountryCode;
}

QString cArtist::countryCode()
{
	return(m_szCountryCode);
}

void cArtist::setArtistThumb(const QString& szArtistThumb)
{
	m_szArtistThumb	= szArtistThumb;
}

QString cArtist::artistThumb()
{
	return(m_szArtistThumb);
}

void cArtist::setArtistLogo(const QString& szArtistLogo)
{
	m_szArtistLogo	= szArtistLogo;
}

QString cArtist::artistLogo()
{
	return(m_szArtistLogo);
}

void cArtist::setArtistClearart(const QString& szArtistClearart)
{
	m_szArtistClearart	= szArtistClearart;
}

QString cArtist::artistClearart()
{
	return(m_szArtistClearart);
}

void cArtist::setArtistWideThumb(const QString& szArtistWideThumb)
{
	m_szArtistWideThumb	= szArtistWideThumb;
}

QString cArtist::artistWideThumb()
{
	return(m_szArtistWideThumb);
}

void cArtist::setArtistFanart(const QString& szArtistFanart)
{
	m_szArtistFanart	= szArtistFanart;
}

QString cArtist::artistFanart()
{
	return(m_szArtistFanart);
}

void cArtist::setArtistFanart2(const QString& szArtistFanart2)
{
	m_szArtistFanart2	= szArtistFanart2;
}

QString cArtist::artistFanart2()
{
	return(m_szArtistFanart2);
}

void cArtist::setArtistFanart3(const QString& szArtistFanart3)
{
	m_szArtistFanart3	= szArtistFanart3;
}

QString cArtist::artistFanart3()
{
	return(m_szArtistFanart3);
}

void cArtist::setArtistBanner(const QString& szArtistBanner)
{
	m_szArtistBanner	= szArtistBanner;
}

QString cArtist::artistBanner()
{
	return(m_szArtistBanner);
}

void cArtist::setMusicBrainzID(const QString& szMusicBrainzID)
{
	m_szMusicBrainzID	= szMusicBrainzID;
}

QString cArtist::musicBrainzID()
{
	return(m_szMusicBrainzID);
}

void cArtist::setLastFMChart(const QString& szLastFMChart)
{
	m_szLastFMChart	= szLastFMChart;
}

QString cArtist::lastFMChart()
{
	return(m_szLastFMChart);
}

cArtist* cArtistList::add(const qint32& iID)
{
	cArtist*	lpNew	= find(iID);
	if(!lpNew)
		lpNew	= new cArtist;
	lpNew->setArtistID(iID);
	append(lpNew);
	return(lpNew);
}

cArtist* cArtistList::add(cArtist* lpArtist)
{
	for(int z = 0;z < count();z++)
	{
		if(at(z) == lpArtist)
			return(0);
	}
	append(lpArtist);
	return(lpArtist);
}

cArtist* cArtistList::find(const qint32& iID)
{
	for(int z = 0;z < count();z++)
	{
		if(at(z)->artistID() == iID)
			return(at(z));
	}
	return(0);
}
