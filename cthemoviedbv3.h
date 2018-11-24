#ifndef CTHEMOVIEDBV3_H
#define CTHEMOVIEDBV3_H


#include "cmovie.h"
#include "cserie.h"

#include <QString>
#include <QList>
#include <QStringList>
#include <QMap>


/*!
 \brief

 \class cTheMovieDBV3 cthemoviedbv3.h "cthemoviedbv3.h"
*/
class cTheMovieDBV3
{
public:
	cTheMovieDBV3();
	/*!
	 \brief

	 \fn ~cTheMovieDBV3
	*/
	~cTheMovieDBV3();

	/*!
	 \brief

	 \fn searchMovie
	 \param szMovie
	 \param year
	 \param szLanguage
	 \return QList<cMovie *>
	*/
	QList<cMovie*>			searchMovie(cMovieList& movieListOri, const QString& szMovie, const qint32& year = -1, const QString& szLanguage = "all");
	/*!
	 \brief

	 \fn loadMovie
	 \param iID
	 \param szLanguage
	 \return cMovie
	*/
	cMovie*					loadMovie(const qint32 &iID, const QString& szLanguage);
	/*!
	 \brief

	 \fn genresMovie
	 \param szLanguage
	 \return QMap<qint32, QString>
	*/
	QMap<qint32, QString>	genresMovie(const QString& szLanguage = "all");
	/*!
	 \brief

	 \fn discoverMovie
	 \param szText
	 \param bAdult
	 \param iYear
	 \param genres
	 \param voteMin
	 \param voteMax
	 \param szLanguage
	 \return QList<cMovie *>
	*/
	QList<cMovie*>			discoverMovie(cMovieList& movieListOri, const QString& szText, const bool& bAdult, const qint32& iYear, const QList<qint32>& genres, const qreal& voteMin, const qreal& voteMax, const QString& szLanguage = "all");
	/*!
	 \brief

	 \fn loadCastMovie
	 \param lpMovie
	*/
	void					loadCastMovie(cMovie* lpMovie);

	/*!
	 \brief

	 \fn searchSerie
	 \param szSerie
	 \param year
	 \param szLanguage
	 \return QList<cSerie *>
	*/
	QList<cSerie*>			searchSerie(cSerieList& serieListOri, const QString& szSerie, const qint32& year = -1, const QString& szLanguage = "all");
	/*!
	 \brief

	 \fn loadSerie
	 \param iID
	 \param szLanguage
	 \return cSerie
	*/
	cSerie*					loadSerie(const qint32 &iID, const QString& szLanguage);
	/*!
	 \brief

	 \fn loadSerie
	 \param szIMDBID
	 \return cSerie
	*/
	cSerie*					loadSerie(const QString& szIMDBID);
	/*!
	 \brief

	 \fn genresSerie
	 \param szLanguage
	 \return QMap<qint32, QString>
	*/
	QMap<qint32, QString>	genresSerie(const QString& szLanguage = "all");
	/*!
	 \brief

	 \fn discoverSerie
	 \param szText
	 \param iYear
	 \param genres
	 \param voteMin
	 \param voteMax
	 \param szLanguage
	 \return QList<cSerie *>
	*/
	QList<cSerie*>			discoverSerie(cSerieList& serieListOri, const QString& szText, const qint32& iYear, const QList<qint32>& genres, const qreal& voteMin, const qreal& voteMax, const QString& szLanguage = "all");
	/*!
	 \brief

	 \fn loadCastSerie
	 \param lpSerie
	*/
	void					loadCastSerie(cSerie* lpSerie);
private:
	QString					m_szToken; /*!< TODO: describe */
	QMap<qint32, QString>	m_genres; /*!< TODO: describe */

	/*!
	 \brief

	 \fn genresFromID
	 \param genres
	 \return QStringList
	*/
	QStringList				genresFromID(QList<qint32> genres);
};

#endif // CTHEMOVIEDBV3_H
