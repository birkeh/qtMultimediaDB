#ifndef CFANART_H
#define CFANART_H


#include <QString>
#include <QMetaType>
#include <QList>


class cFanart
{
public:
	enum Type
	{
		TypeUnknown				= 0,
		TypeHDTVLogo			= 1,
		TypeClearLogo			= 2,
		TypeTVPoster			= 3,
		TypeClearArt			= 4,
		TypeHDClearArt			= 5,
		TypeShowBackground		= 6,
		TypeSeasonPoster		= 7,
		TypeTVThumb				= 8,
		TypeSeasonBanner		= 9,
		TypeCharacterArt		= 10,
		TypeSeasonThumb			= 11,
		TypeTVBanner			= 12,
		TypeHDMovieLogo			= 13,
		TypeMovieDisc			= 14,
		TypeMovieLogo			= 15,
		TypeMoviePoster			= 16,
		TypeHDMovieClearArt		= 17,
		TypeMovieArt			= 18,
		TypeMovieBackground		= 19,
		TypeMovieBanner			= 20,
		TypeMovieThumb			= 21,
	};

	cFanart(Type type = TypeUnknown);

	void		setType(const Type& type);
	Type		type();

	void		setID(const qint32& iID);
	qint32		id();

	void		setURL(const QString& szURL);
	QString		url();

	void		setLanguage(const QString& szLanguage);
	QString		language();

	void		setLikes(const qint32& iLikes);
	qint32		likes();

	void		setSeason(const qint16& iSeason);
	qint16		season();

	void		setDisc(const QString& szDisc);
	QString		disc();

	void		setDiscType(const QString& szDiscType);
	QString		discType();

	void		setActive(const bool& bActive);
	bool		active();
private:
	Type		m_type;
	qint32		m_iID;
	QString		m_szURL;
	QString		m_szLanguage;
	qint32		m_iLikes;
	qint16		m_iSeason;
	QString		m_szDisc;
	QString		m_szDiscType;
	bool		m_bActive;
};

Q_DECLARE_METATYPE(cFanart*)

class cFanartList : public QList<cFanart*>
{
public:
	cFanart*		add(const cFanart::Type& type);
	cFanart*		search(const cFanart::Type& type, const QString& szLanguage = "");
	cFanart*		search(const cFanart::Type& type, const bool bActive, const QString& szLanguage = "");
};

#endif // CFANART_H
