#ifndef CTHEMOVIEDBV3_H
#define CTHEMOVIEDBV3_H


#include "cmovie.h"
#include "cserie.h"

#include <QString>
#include <QList>
#include <QStringList>
#include <QMap>


class cTheMovieDBV3
{
public:
	cTheMovieDBV3();
	~cTheMovieDBV3();

	QList<cMovie*>			searchMovie(const QString& szMovie, const qint16& year = -1, const QString& szLanguage = "all");
	cMovie*					loadMovie(const qint32 &iID, const QString& szLanguage);
	QMap<qint32, QString>	genresMovie(const QString& szLanguage = "all");
	QList<cMovie*>			discoverMovie(const QString& szText, const bool& bAdult, const qint16& iYear, const QList<qint32>& genres, const qreal& voteMin, const qreal& voteMax, const QString& szLanguage = "all");
	void					loadCastMovie(cMovie* lpMovie);

	QList<cSerie*>			searchSerie(const QString& szSerie, const qint16& year = -1, const QString& szLanguage = "all");
	cSerie*					loadSerie(const qint32 &iID, const QString& szLanguage);
	cSerie*					loadSerie(const QString& szIMDBID);
	QMap<qint32, QString>	genresSerie(const QString& szLanguage = "all");
private:
	QString					m_szToken;
	QMap<qint32, QString>	m_genres;

	QStringList				genresFromID(QList<qint32> genres);
};

#endif // CTHEMOVIEDBV3_H
