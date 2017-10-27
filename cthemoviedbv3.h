#ifndef CTHEMOVIEDBV3_H
#define CTHEMOVIEDBV3_H


#include "cmovie.h"
#include "cserie.h"

#include <QString>
#include <QList>
#include <QStringList>


class cTheMovieDBV3
{
public:
	cTheMovieDBV3();

	QList<cMovie*>	searchMovie(const QString& szMovie, const qint16& year = -1, const QString& szLanguage = "all");
	cMovie*			loadMovie(const qint32 &iID, const QString& szLanguage);

	QList<cSerie*>	searchSerie(const QString& szSerie, const qint16& year = -1, const QString& szLanguage = "all");
	cSerie*			loadSerie(const qint32 &iID, const QString& szLanguage);
	cSerie*			loadSerie(const QString& szIMDBID);
private:
	QString			m_szToken;
//	QStringList		getActors(const qint32& iID);
//	void			getEpisodes(cSerie* lpSerie, const QString& szLanguage);
//	cEpisode*		getEpisode(const qint32& iID, const QString& szLanguage);
};

#endif // CTHEMOVIEDBV3_H
