#ifndef CEPISODE_H
#define CEPISODE_H


#include <QMetaType>
#include <QList>
#include <QDate>

#include <QButtonGroup>
#include <QLabel>
#include <QRadioButton>


class cEpisode
{
public:
	enum State
	{
		StateUnknown	= 0,
		StateInit		= 1,
		StateProgress	= 2,
		StateDone		= 3,
	};

	cEpisode();
	~cEpisode();

	void		setID(const qint32& iID);
	qint32		id();

	void		setName(const QString& szName);
	QString		name();

	void		setEpisodeNumber(const qint16& iEpisodeNumber);
	qint16		episodeNumber();

	void		setAirDate(const QString& szAirDate);
	void		setAirDate(const QDate& airDate);
	QDate		airDate();

	void		setGuestStars(const QString& szGuestStars);
	void		setGuestStars(const QStringList& szGuestStars);
	QStringList	guestStars();

	void		setOverview(const QString& szOverview);
	QString		overview();

	void		setProductionCode(const QString& szProductionCode);
	QString		productionCode();

	void		setSeasonNumber(const qint16& iSeasonNumber);
	qint16		seasonNumber();

	void		setSeasonID(const qint32& iSeasonID);
	qint32		seasonID();

	void		setSeriesID(const qint32& iSeriesID);
	qint32		seriesID();

	void		setStillPath(const QString& szStillPath);
	QString		stillPath();

	void		setVoteAverage(const qreal& dVoteAverage);
	qreal		voteAverage();

	void		setVoteCount(const qint16& iVoteCount);
	qint16		voteCount();

	void		setCrew(const QString& szCrew);
	void		setCrew(const QStringList& szCrew);
	QStringList	crew();

	void		setState(const State& state);
	State		state();

	void		setFileName(const QString& szFileName);
	QString		fileName();

	void		setThumbHeight(const qint16& iThumbHeight);
	qint16		thumbHeight();

	void		setThumbWidth(const qint16& iThumbWidth);
	qint16		thumbWidth();

	bool		isValid();

	void		setGroup(QButtonGroup* lpGroup);
	void		setLabel(QLabel* lpLabel);
	void		setButton1(QRadioButton* lpButton1);
	void		setButton2(QRadioButton* lpButton2);
	void		setButton3(QRadioButton* lpButton3);

	void		updateState();
	void		deleteResources();
private:
	qint32			m_iID;
	QString			m_szName;
	qint16			m_iEpisodeNumber;
	QDate			m_airDate;
	QStringList		m_szGuestStars;
	QString			m_szOverview;
	QString			m_szProductionCode;
	qint16			m_iSeasonNumber;
	qint32			m_iSeasonID;
	qint32			m_iSeriesID;
	QString			m_szStillPath;
	qreal			m_dVoteAverage;
	qint16			m_iVoteCount;
	QStringList		m_szCrew;
	State			m_state;
//	qint16			m_iThumbHeight;
//	qint16			m_iThumbWidth;
	QButtonGroup*	m_lpGroup;
	QLabel*			m_lpLabel;
	QRadioButton*	m_lpButton1;
	QRadioButton*	m_lpButton2;
	QRadioButton*	m_lpButton3;
};

Q_DECLARE_METATYPE(cEpisode*)

#endif // CEPISODE_H
