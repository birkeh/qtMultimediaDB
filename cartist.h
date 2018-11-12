#ifndef CARTIST_H
#define CARTIST_H


#include <QMetaType>
#include <QDate>
#include <QSqlDatabase>
#include <QStringList>
#include <QMap>


class cArtist
{
public:
	cArtist();

	void			setArtistID(const qint32& iArtistID);
	qint32			artistID();
	void			setArtist(const QString& szArtist);
	QString			artist();
	void			setArtistStripped(const QString& szArtistStripped);
	QString			artistStripped();
	void			setArtistAlernate(const QString& szArtistAlernate);
	QString			artistAlernate();
	void			setLabel(const QString& szLabel);
	QString			label();
	void			setLabelID(const qint32& iLabelID);
	qint32			labelID();
	void			setFormedYear(const qint32& iFormedYear);
	qint32			formedYear();
	void			setBornYear(const qint32& iBornYear);
	qint32			bornYear();
	void			setDiedYear(const qint32& iDiedYear);
	qint32			diedYear();
	void			setDisbanded(const QString& szDisbanded);
	QString			disbanded();
	void			setStyle(const QString& szStyle);
	QString			style();
	void			setGenre(const QString& szGenre);
	QString			genre();
	void			setMood(const QString& szMood);
	QString			mood();
	void			setWebsite(const QString& szWebsite);
	QString			website();
	void			setFacebook(const QString& szFacebook);
	QString			facebook();
	void			setTwitter(const QString& szTwitter);
	QString			twitter();
	void			setBiography(const QString& szBiography);
	QString			biography();
	void			setGender(const QString& szGender);
	QString			gender();
	void			setMembers(const qint32& iMembers);
	qint32			members();
	void			setCountry(const QString& szCountry);
	QString			country();
	void			setCountryCode(const QString& szCountryCode);
	QString			countryCode();
	void			setArtistThumb(const QString& szArtistThumb);
	QString			artistThumb();
	void			setArtistLogo(const QString& szArtistLogo);
	QString			artistLogo();
	void			setArtistClearart(const QString& szArtistClearart);
	QString			artistClearart();
	void			setArtistWideThumb(const QString& szArtistWideThumb);
	QString			artistWideThumb();
	void			setArtistFanart(const QString& szArtistFanart);
	QString			artistFanart();
	void			setArtistFanart2(const QString& szArtistFanart2);
	QString			artistFanart2();
	void			setArtistFanart3(const QString& szArtistFanart3);
	QString			artistFanart3();
	void			setArtistBanner(const QString& szArtistBanner);
	QString			artistBanner();
	void			setMusicBrainzID(const QString& szMusicBrainzID);
	QString			musicBrainzID();
	void			setLastFMChart(const QString& szLastFMChart);
	QString			lastFMChart();

private:
	qint32			m_iArtistID;
	QString			m_szArtist;
	QString			m_szArtistStripped;
	QString			m_szArtistAlernate;
	QString			m_szLabel;
	qint32			m_iLabelID;
	qint32			m_iFormedYear;
	qint32			m_iBornYear;
	qint32			m_iDiedYear;
	QString			m_szDisbanded;
	QString			m_szStyle;
	QString			m_szGenre;
	QString			m_szMood;
	QString			m_szWebsite;
	QString			m_szFacebook;
	QString			m_szTwitter;
	QString			m_szBiography;
	QString			m_szGender;
	qint32			m_iMembers;
	QString			m_szCountry;
	QString			m_szCountryCode;
	QString			m_szArtistThumb;
	QString			m_szArtistLogo;
	QString			m_szArtistClearart;
	QString			m_szArtistWideThumb;
	QString			m_szArtistFanart;
	QString			m_szArtistFanart2;
	QString			m_szArtistFanart3;
	QString			m_szArtistBanner;
	QString			m_szMusicBrainzID;
	QString			m_szLastFMChart;
};

Q_DECLARE_METATYPE(cArtist*)

class cArtistList : public QList<cArtist*>
{
public:
	cArtist*		add(const qint32& iArtistID);
	cArtist*		add(cArtist* lpArtist);
	cArtist*		find(const qint32& iArtistID);
};

#endif // CARTIST_H
