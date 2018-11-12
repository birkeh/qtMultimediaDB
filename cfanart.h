#ifndef CFANART_H
#define CFANART_H


#include <QString>
#include <QMetaType>
#include <QList>


/*!
 \brief

 \class cFanart cfanart.h "cfanart.h"
*/
class cFanart
{
public:
	/*!
	 \brief

	 \enum Type
	*/
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

	/*!
	 \brief

	 \fn setType
	 \param type
	*/
	void		setType(const Type& type);
	/*!
	 \brief

	 \fn type
	 \return Type
	*/
	Type		type();

	/*!
	 \brief

	 \fn setID
	 \param iID
	*/
	void		setID(const qint32& iID);
	/*!
	 \brief

	 \fn id
	 \return qint32
	*/
	qint32		id();

	/*!
	 \brief

	 \fn setURL
	 \param szURL
	*/
	void		setURL(const QString& szURL);
	/*!
	 \brief

	 \fn url
	 \return QString
	*/
	QString		url();

	/*!
	 \brief

	 \fn setLanguage
	 \param szLanguage
	*/
	void		setLanguage(const QString& szLanguage);
	/*!
	 \brief

	 \fn language
	 \return QString
	*/
	QString		language();

	/*!
	 \brief

	 \fn setLikes
	 \param iLikes
	*/
	void		setLikes(const qint32& iLikes);
	/*!
	 \brief

	 \fn likes
	 \return qint32
	*/
	qint32		likes();

	/*!
	 \brief

	 \fn setSeason
	 \param iSeason
	*/
	void		setSeason(const qint32& iSeason);
	/*!
	 \brief

	 \fn season
	 \return qint32
	*/
	qint32		season();

	/*!
	 \brief

	 \fn setDisc
	 \param szDisc
	*/
	void		setDisc(const QString& szDisc);
	/*!
	 \brief

	 \fn disc
	 \return QString
	*/
	QString		disc();

	/*!
	 \brief

	 \fn setDiscType
	 \param szDiscType
	*/
	void		setDiscType(const QString& szDiscType);
	/*!
	 \brief

	 \fn discType
	 \return QString
	*/
	QString		discType();

	/*!
	 \brief

	 \fn setActive
	 \param bActive
	*/
	void		setActive(const bool& bActive);
	/*!
	 \brief

	 \fn active
	 \return bool
	*/
	bool		active();
private:
	Type		m_type; /*!< TODO: describe */
	qint32		m_iID; /*!< TODO: describe */
	QString		m_szURL; /*!< TODO: describe */
	QString		m_szLanguage; /*!< TODO: describe */
	qint32		m_iLikes; /*!< TODO: describe */
	qint32		m_iSeason; /*!< TODO: describe */
	QString		m_szDisc; /*!< TODO: describe */
	QString		m_szDiscType; /*!< TODO: describe */
	bool		m_bActive; /*!< TODO: describe */
};

Q_DECLARE_METATYPE(cFanart*)
Q_DECLARE_METATYPE(cFanart::Type)

/*!
 \brief

 \class cFanartList cfanart.h "cfanart.h"
*/
class cFanartList : public QList<cFanart*>
{
public:
	/*!
	 \brief

	 \fn add
	 \param type
	 \return cFanart
	*/
	cFanart*		add(const cFanart::Type& type);
	/*!
	 \brief

	 \fn search
	 \param type
	 \param szLanguage
	 \return cFanart
	*/
	cFanart*		search(const cFanart::Type& type, const QString& szLanguage = "");
	/*!
	 \brief

	 \fn search
	 \param type
	 \param bActive
	 \param szLanguage
	 \return cFanart
	*/
	cFanart*		search(const cFanart::Type& type, const bool bActive, const QString& szLanguage = "");
};

#endif // CFANART_H
