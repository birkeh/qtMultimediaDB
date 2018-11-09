#include "cthemoviedbv3.h"


#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>
#include <QByteArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include <QApplication>


cTheMovieDBV3::cTheMovieDBV3()
{
	m_szToken	= "a33271b9e54cdcb9a80680eaf5522f1b";
}

cTheMovieDBV3::~cTheMovieDBV3()
{
}

QList<cMovie*> cTheMovieDBV3::searchMovie(const QString& szMovie, const qint16& year, const QString& szLanguage)
{
	if(m_genres.isEmpty())
		m_genres	= genresMovie("de-DE");

	QList<cMovie*>			movieList;
	QNetworkAccessManager	networkManager;
	QString					szRequest	= QString("https://api.themoviedb.org/3/search/movie?api_key=%1").arg(m_szToken);
	qint16					page		= 1;

	if(!szLanguage.contains("all"))
		szRequest.append(QString("&language=%1").arg(szLanguage));

	szRequest.append(QString("&query=%1").arg(szMovie));

	if(year != -1)
		szRequest.append(QString("&year=%1").arg(year));

	szRequest.append("&include_adult=false");

	for(;;)
	{
		QNetworkRequest			request(QUrl(QString("%1&page=%2").arg(szRequest).arg(page)));

		QNetworkReply*			reply   = networkManager.get(request);
		QEventLoop				loop;

		QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
		loop.exec();

		if (reply->error() == QNetworkReply::NoError)
		{
			QString			strReply		= (QString)reply->readAll();
			QJsonDocument	jsonResponse	= QJsonDocument::fromJson(strReply.toUtf8());
			QJsonObject		jsonObj			= jsonResponse.object();
			QJsonArray		jsonArray		= jsonObj["results"].toArray();

			for(int z = 0;z < jsonArray.count();z++)
			{
				QJsonObject	movie			= jsonArray[z].toObject();
				cMovie*		lpMovie			= new cMovie;
				lpMovie->setMovieTitle(movie["title"].toString());
				lpMovie->setMovieID(movie["id"].toInt());
				lpMovie->setOriginalTitle(movie["original_title"].toString());
				lpMovie->setReleaseDate(movie["release_date"].toString());
				lpMovie->setVoteCount(movie["vote_count"].toInt());
				lpMovie->setVideo(movie["video"].toBool());
				lpMovie->setVoteAverage(movie["vote_average"].toDouble());
				lpMovie->setPopularity(movie["popularity"].toDouble());
				lpMovie->setPosterPath(movie["poster_path"].toString());
				lpMovie->setOriginalLanguage(movie["original_language"].toString());

				QJsonArray	genresArray		= movie["genre_ids"].toArray();
				QList<qint32>	genresIDs;
				for(int y = 0;y < genresArray.count();y++)
					genresIDs.append(genresArray[y].toInt());
				if(genresIDs.count())
					lpMovie->setGenres(genresFromID(genresIDs));
				lpMovie->setBackdropPath(movie["backdrop_path"].toString());
				lpMovie->setAdult(movie["adult"].toBool());
				lpMovie->setOverview(movie["overview"].toString());
				lpMovie->setReleaseDate(movie["release_date"].toString());

				movieList.append(lpMovie);
			}
			if(jsonObj["total_pages"].toInt() == page)
				break;

			page++;
			if(page > 20)
				break;

			delete reply;
		}
		else
		{
			qDebug() << reply->errorString();
			delete reply;
		}
	}
	return(movieList);
}

QList<cSerie*> cTheMovieDBV3::searchSerie(const QString& szSerie, const qint16& year, const QString& szLanguage)
{
	QList<cSerie*>			serieList;
	QNetworkAccessManager	networkManager;
	QString					szRequest	= QString("https://api.themoviedb.org/3/search/tv?api_key=%1").arg(m_szToken);
	qint16					page		= 1;

	if(!szLanguage.contains("all"))
		szRequest.append(QString("&language=%1").arg(szLanguage));

	szRequest.append(QString("&query=%1").arg(szSerie));

	if(year != -1)
		szRequest.append(QString("&year=%1").arg(year));

	szRequest.append("&include_adult=false");

	for(;;)
	{
		QNetworkRequest			request(QUrl(QString("%1&page=%2").arg(szRequest).arg(page)));

		QNetworkReply*			reply   = networkManager.get(request);
		QEventLoop				loop;

		QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
		loop.exec();

		if (reply->error() == QNetworkReply::NoError)
		{
			QString			strReply		= (QString)reply->readAll();
			QJsonDocument	jsonResponse	= QJsonDocument::fromJson(strReply.toUtf8());
			QJsonObject		jsonObj			= jsonResponse.object();
			QJsonArray		jsonArray		= jsonObj["results"].toArray();
			QJsonArray		tmpArray;
			QStringList		tmpList;

			for(int z = 0;z < jsonArray.count();z++)
			{
				QJsonObject	serie			= jsonArray[z].toObject();
				cSerie*		lpSerie			= new cSerie;

				lpSerie->setSeriesID(serie["id"].toInt());
				lpSerie->setBackdropPath(serie["backdrop_path"].toString());
				tmpArray	= serie["created_by"].toArray();
				for(int x = 0;x < tmpArray.count();x++)
					tmpList.append(tmpArray.at(x).toObject()["name"].toString());
				lpSerie->setCreatedBy(tmpList);
				tmpList.clear();
				lpSerie->setFirstAired(serie["first_air_date"].toString());
				tmpArray	= serie["genres"].toArray();
				for(int x = 0;x < tmpArray.count();x++)
					tmpList.append(tmpArray.at(x).toObject()["name"].toString());
				lpSerie->setGenre(tmpList);
				tmpList.clear();
				lpSerie->setHomepage(serie["homepage"].toString());
				lpSerie->setLastAired(serie["last_air_date"].toString());
				tmpArray	= serie["languages"].toArray();
				for(int x = 0;x < tmpArray.count();x++)
					tmpList.append(tmpArray.at(x).toString());
				lpSerie->setLanguages(tmpList);
				tmpList.clear();
				lpSerie->setSeriesName(serie["name"].toString());
				tmpArray	= serie["networks"].toArray();
				for(int x = 0;x < tmpArray.count();x++)
					tmpList.append(tmpArray.at(x).toObject()["name"].toString());
				lpSerie->setNetworks(tmpList);
				tmpList.clear();
				lpSerie->setEpisodes(serie["number_of_episodes"].toInt());
				lpSerie->setSeasons(serie["number_of_seasons"].toInt());
				tmpArray	= serie["origin_country"].toArray();
				for(int x = 0;x < tmpArray.count();x++)
					tmpList.append(tmpArray.at(x).toString());
				lpSerie->setOriginCountries(tmpList);
				tmpList.clear();
				lpSerie->setOriginalLanguage(serie["original_language"].toString());
				lpSerie->setOriginalName(serie["original_name"].toString());
				lpSerie->setOverview(serie["overview"].toString());
				lpSerie->setPopularity(serie["popularity"].toDouble());
				lpSerie->setPosterPath(serie["poster_path"].toString());
				tmpArray	= serie["production_companies"].toArray();
				for(int x = 0;x < tmpArray.count();x++)
					tmpList.append(tmpArray.at(x).toObject()["name"].toString());
				lpSerie->setProductionCompanies(tmpList);
				tmpList.clear();
				lpSerie->setStatus(serie["status"].toString());
				lpSerie->setType(serie["type"].toString());
				lpSerie->setVoteAverage(serie["vote_average"].toDouble());
				lpSerie->setVoteCount(serie["vote_count"].toInt());

				serieList.append(lpSerie);
			}
			if(jsonObj["total_pages"].toInt() == page)
				break;

			page++;
			if(page > 20)
				break;

			delete reply;
		}
		else
		{
			qDebug() << reply->errorString();
			delete reply;
		}
	}
	return(serieList);
}

cMovie* cTheMovieDBV3::loadMovie(const qint32 &iID, const QString &szLanguage)
{
	cMovie*					lpMovie	= 0;
	QNetworkAccessManager	networkManager;
	QNetworkRequest			request(QUrl(QString("https://api.themoviedb.org/3/movie/%1?api_key=%2&language=%3").arg(iID).arg(m_szToken).arg(szLanguage)));

	request.setRawHeader("Content-Type", "application/json");
	request.setRawHeader("Authorization", QString("Bearer %1").arg(m_szToken).toUtf8());
	if(!szLanguage.contains("all"))
		request.setRawHeader("Accept-Language", szLanguage.toUtf8());
	else
		request.setRawHeader("Accept-Language", "en");

	QNetworkReply*			reply   = networkManager.get(request);
	QEventLoop				loop;

	QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
	loop.exec();

	if (reply->error() == QNetworkReply::NoError)
	{
		QString			strReply		= (QString)reply->readAll();
		QJsonDocument	jsonResponse	= QJsonDocument::fromJson(strReply.toUtf8());
		QJsonObject		jsonObj			= jsonResponse.object();

		QJsonArray		genreArray		= jsonObj["genres"].toArray();
		QStringList		genreList;

		QJsonArray		productionCompaniesArray	= jsonObj["production_companies"].toArray();
		QStringList		productionCompaniesList;

		QJsonArray		productionCountriesArray	= jsonObj["production_countries"].toArray();
		QStringList		productionCountriesList;

		QJsonArray		spokenLanguagesArray		= jsonObj["spoken_languages"].toArray();
		QStringList		spokenLanguagesList;

		QJsonObject		tmpObj;

		delete reply;

		lpMovie	= new cMovie;

		lpMovie->setMovieTitle(jsonObj["title"].toString());
		lpMovie->setMovieID(jsonObj["id"].toInt());
		lpMovie->setOriginalTitle(jsonObj["original_title"].toString());
		lpMovie->setReleaseDate(jsonObj["release_date"].toString());
		lpMovie->setAdult(jsonObj["adult"].toBool());
		lpMovie->setBackdropPath(jsonObj["backdrop_path"].toString());
		tmpObj	= jsonObj["belongs_to_collection"].toObject();
		lpMovie->setBelongsToCollection(tmpObj["name"].toString());
		lpMovie->setBudget(jsonObj["budget"].toDouble());
		for(int z = 0;z < genreArray.count();z++)
		{
			tmpObj	= genreArray[z].toObject();
			genreList.append(tmpObj["name"].toString());
		}
		lpMovie->setGenres(genreList);
		lpMovie->setHomepage(jsonObj["homepage"].toString());
		lpMovie->setIMDBID(jsonObj["imdb_id"].toString());
		lpMovie->setOriginalLanguage(jsonObj["original_language"].toString());
		lpMovie->setOverview(jsonObj["overview"].toString());
		lpMovie->setPopularity(jsonObj["popularity"].toDouble());
		lpMovie->setPosterPath(jsonObj["poster_path"].toString());
		for(int z = 0;z < productionCompaniesArray.count();z++)
		{
			tmpObj	= productionCompaniesArray[z].toObject();
			productionCompaniesList.append(tmpObj["name"].toString());
		}
		lpMovie->setProductionCompanies(productionCompaniesList);
		for(int z = 0;z < productionCountriesArray.count();z++)
		{
			tmpObj	= productionCountriesArray[z].toObject();
			productionCountriesList.append(tmpObj["name"].toString());
		}
		lpMovie->setProductionCountries(productionCountriesList);
		lpMovie->setRevenue(jsonObj["revenue"].toDouble());
		lpMovie->setRuntime(jsonObj["runtime"].toInt());
		for(int z = 0;z < spokenLanguagesArray.count();z++)
		{
			tmpObj	= spokenLanguagesArray[z].toObject();
			spokenLanguagesList.append(tmpObj["name"].toString());
		}
		lpMovie->setSpokenLanguages(spokenLanguagesList);
		lpMovie->setStatus(jsonObj["status"].toString());
		lpMovie->setTagline(jsonObj["tagline"].toString());
		lpMovie->setVideo(jsonObj["video"].toBool());
		lpMovie->setVoteAverage(jsonObj["vote_average"].toDouble());
		lpMovie->setVoteCount(jsonObj["vote_count"].toInt());
		lpMovie->setState(cMovie::StateInit);

		request.setUrl(QUrl(QString("https://api.themoviedb.org/3/movie/%1/credits?api_key=%2").arg(iID).arg(m_szToken)));

		request.setRawHeader("Content-Type", "application/json");
		if(!szLanguage.contains("all"))
			request.setRawHeader("Accept-Language", szLanguage.toUtf8());
		else
			request.setRawHeader("Accept-Language", "en");

		reply   = networkManager.get(request);

		QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
		loop.exec();

		if (reply->error() == QNetworkReply::NoError)
		{
			strReply		= (QString)reply->readAll();
			jsonResponse	= QJsonDocument::fromJson(strReply.toUtf8());
			QJsonObject		jsonCast		= jsonResponse.object();
			QJsonArray		jsonArrayCast	= jsonCast["cast"].toArray();
			QJsonArray		jsonArrayCrew	= jsonCast["crew"].toArray();

			QStringList		szCast;
			QStringList		szCrew;

			delete reply;

			for(int x = 0;x < jsonArrayCast.count();x++)
			{
				tmpObj	= jsonArrayCast.at(x).toObject();
				szCast.append(QString("%1,%2").arg(tmpObj["name"].toString()).arg(tmpObj["character"].toString()));
			}
			if(szCast.count())
				lpMovie->setCast(szCast);

			for(int x = 0;x < jsonArrayCrew.count();x++)
			{
				tmpObj	= jsonArrayCrew.at(x).toObject();
				szCrew.append(QString("%1,%2").arg(tmpObj["name"].toString()).arg(tmpObj["job"].toString()));
			}
			if(szCrew.count())
				lpMovie->setCrew(szCrew);
		}
	}
	else
	{
		qDebug() << reply->errorString();
		delete reply;
	}
	return(lpMovie);
}

cSerie* cTheMovieDBV3::loadSerie(const QString& szIMDBID)
{
	qint32					iID;
	QNetworkAccessManager	networkManager;
	QNetworkRequest			request(QUrl(QString("https://api.themoviedb.org/3/find/%1?api_key=%2&external_source=imdb_id").arg(szIMDBID).arg(m_szToken)));

	request.setRawHeader("Content-Type", "application/json");
	request.setRawHeader("Authorization", QString("Bearer %1").arg(m_szToken).toUtf8());

	QNetworkReply*			reply   = networkManager.get(request);
	QEventLoop				loop;

	QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
	loop.exec();

	if (reply->error() == QNetworkReply::NoError)
	{
		QString			strReply		= (QString)reply->readAll();
		QJsonDocument	jsonResponse	= QJsonDocument::fromJson(strReply.toUtf8());
		QJsonObject		jsonObj			= jsonResponse.object();

		QJsonArray		tmpArray;
		QJsonObject		tmpObj;

		delete reply;

		tmpArray	= jsonObj["tv_results"].toArray();
		tmpObj		= tmpArray.at(0).toObject();
		iID			= tmpObj["id"].toInt();

		return(loadSerie(iID, "de-DE"));
	}
	else
		qDebug() << reply->errorString();
	return(0);
}

cSerie* cTheMovieDBV3::loadSerie(const qint32 &iID, const QString& szLanguage)
{
	cSerie*					lpSerie	= 0;
	QNetworkAccessManager	networkManager;
	QNetworkRequest			request(QUrl(QString("https://api.themoviedb.org/3/tv/%1?api_key=%2&language=%3&append_to_response=credits,external_ids").arg(iID).arg(m_szToken).arg(szLanguage)));

	request.setRawHeader("Content-Type", "application/json");
	request.setRawHeader("Authorization", QString("Bearer %1").arg(m_szToken).toUtf8());
	if(!szLanguage.contains("all"))
		request.setRawHeader("Accept-Language", szLanguage.toUtf8());
	else
		request.setRawHeader("Accept-Language", "en");

	QNetworkReply*			reply   = networkManager.get(request);
	QEventLoop				loop;

	QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
	loop.exec();

	if (reply->error() == QNetworkReply::NoError)
	{
		QString			strReply		= (QString)reply->readAll();
		QJsonDocument	jsonResponse	= QJsonDocument::fromJson(strReply.toUtf8());
		QJsonObject		jsonObj			= jsonResponse.object();

		QJsonArray		tmpArray;
		QStringList		tmpList;

		QJsonObject		tmpObj;

		delete reply;

		lpSerie	= new cSerie;

		lpSerie->setSeriesID(iID);
		lpSerie->setBackdropPath(jsonObj["backdrop_path"].toString());
		tmpArray	= jsonObj["created_by"].toArray();
		for(int x = 0;x < tmpArray.count();x++)
			tmpList.append(tmpArray.at(x).toObject()["name"].toString());
		lpSerie->setCreatedBy(tmpList);
		tmpList.clear();
		lpSerie->setFirstAired(jsonObj["first_air_date"].toString());
		tmpArray	= jsonObj["genres"].toArray();
		for(int x = 0;x < tmpArray.count();x++)
			tmpList.append(tmpArray.at(x).toObject()["name"].toString());
		lpSerie->setGenre(tmpList);
		tmpList.clear();
		lpSerie->setHomepage(jsonObj["homepage"].toString());
		lpSerie->setLastAired(jsonObj["last_air_date"].toString());
		tmpArray	= jsonObj["languages"].toArray();
		for(int x = 0;x < tmpArray.count();x++)
			tmpList.append(tmpArray.at(x).toString());
		lpSerie->setLanguages(tmpList);
		tmpList.clear();
		lpSerie->setSeriesName(jsonObj["name"].toString());
		tmpArray	= jsonObj["networks"].toArray();
		for(int x = 0;x < tmpArray.count();x++)
			tmpList.append(tmpArray.at(x).toObject()["name"].toString());
		lpSerie->setNetworks(tmpList);
		tmpList.clear();
		lpSerie->setEpisodes(jsonObj["number_of_episodes"].toInt());
		lpSerie->setSeasons(jsonObj["number_of_seasons"].toInt());
		tmpArray	= jsonObj["origin_country"].toArray();
		for(int x = 0;x < tmpArray.count();x++)
			tmpList.append(tmpArray.at(x).toString());
		lpSerie->setOriginCountries(tmpList);
		tmpList.clear();
		lpSerie->setOriginalLanguage(jsonObj["original_language"].toString());
		lpSerie->setOriginalName(jsonObj["original_name"].toString());
		lpSerie->setOverview(jsonObj["overview"].toString());
		lpSerie->setPopularity(jsonObj["popularity"].toDouble());
		lpSerie->setPosterPath(jsonObj["poster_path"].toString());
		tmpArray	= jsonObj["production_companies"].toArray();
		for(int x = 0;x < tmpArray.count();x++)
			tmpList.append(tmpArray.at(x).toObject()["name"].toString());
		lpSerie->setProductionCompanies(tmpList);
		tmpList.clear();
		lpSerie->setStatus(jsonObj["status"].toString());
		lpSerie->setType(jsonObj["type"].toString());
		lpSerie->setVoteAverage(jsonObj["vote_average"].toDouble());
		lpSerie->setVoteCount(jsonObj["vote_count"].toInt());

		QJsonObject	idsObj			= jsonObj["external_ids"].toObject();
		if(!idsObj.isEmpty())
		{
			lpSerie->setIMDBID(idsObj["imdb_id"].toString());
			lpSerie->setFreebaseMID(idsObj["freebase_mid"].toString());
			lpSerie->setFreebaseID(idsObj["freebase_id"].toString());
			lpSerie->setTVDBID(idsObj["tvdb_id"].toInt());
			lpSerie->setTVRageID(idsObj["tvrage_id"].toInt());
		}

		QJsonObject	creditsObj		= jsonObj["credits"].toObject();
		if(!creditsObj.isEmpty())
		{
			QJsonArray		jsonArrayCast	= creditsObj["cast"].toArray();
			QJsonArray		jsonArrayCrew	= creditsObj["crew"].toArray();

			QStringList		szCast;
			QStringList		szCrew;

			for(int x = 0;x < jsonArrayCast.count();x++)
			{
				tmpObj	= jsonArrayCast.at(x).toObject();
				szCast.append(QString("%1,%2").arg(tmpObj["name"].toString()).arg(tmpObj["character"].toString()));
			}
			if(szCast.count())
				lpSerie->setCast(szCast);

			for(int x = 0;x < jsonArrayCrew.count();x++)
			{
				tmpObj	= jsonArrayCrew.at(x).toObject();
				szCrew.append(QString("%1,%2").arg(tmpObj["name"].toString()).arg(tmpObj["job"].toString()));
			}
			if(szCrew.count())
				lpSerie->setCrew(szCrew);
		}

		tmpArray	= jsonObj["seasons"].toArray();

		for(int x = 0; x < tmpArray.count();x++)
		{
			QJsonObject	seasonObj		= tmpArray.at(x).toObject();
			qint16		seasonNumber	= seasonObj["season_number"].toInt();
			cSeason*	lpSeason		= lpSerie->addSeason(seasonNumber);

			request.setUrl(QUrl(QString("https://api.themoviedb.org/3/tv/%1/season/%2?api_key=%3&language=%4").arg(iID).arg(seasonNumber).arg(m_szToken).arg(szLanguage)));

			request.setRawHeader("Content-Type", "application/json");
			if(!szLanguage.contains("all"))
				request.setRawHeader("Accept-Language", szLanguage.toUtf8());
			else
				request.setRawHeader("Accept-Language", "en");

			reply   = networkManager.get(request);

			QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
			loop.exec();

			if (reply->error() == QNetworkReply::NoError)
			{
				strReply		= (QString)reply->readAll();
				jsonResponse	= QJsonDocument::fromJson(strReply.toUtf8());
				QJsonObject		jsonEpisodes		= jsonResponse.object();
				QJsonArray		jsonArrayEpisodes	= jsonEpisodes["episodes"].toArray();

				delete reply;

				lpSeason->set_ID(jsonEpisodes["_id"].toInt());
				lpSeason->setAirDate(jsonEpisodes["air_date"].toString());
				lpSeason->setName(jsonEpisodes["name"].toString());
				lpSeason->setOverview(jsonEpisodes["overview"].toString());
				lpSeason->setID(jsonEpisodes["id"].toInt());
				lpSeason->setPosterPath(jsonEpisodes["poster_path"].toString());

				for(int x = 0;x < jsonArrayEpisodes.count();x++)
				{
					tmpObj	= jsonArrayEpisodes.at(x).toObject();

					cEpisode*	lpEpisode	= lpSeason->addEpisode(tmpObj["episode_number"].toInt());
					lpEpisode->setAirDate(tmpObj["air_date"].toString());
					lpEpisode->setName(tmpObj["name"].toString());
					lpEpisode->setOverview(tmpObj["overview"].toString());
					lpEpisode->setID(tmpObj["id"].toInt());
					lpEpisode->setProductionCode(tmpObj["production_code"].toString());
					lpEpisode->setSeasonNumber(tmpObj["season_number"].toInt());
					lpEpisode->setStillPath(tmpObj["still_path"].toString());
					lpEpisode->setVoteAverage(tmpObj["vote_average"].toDouble());
					lpEpisode->setVoteCount(tmpObj["vote_count"].toInt());
					lpEpisode->setSeriesID(lpSerie->seriesID());

					QJsonArray	jsonArrayCrew		= tmpObj["crew"].toArray();
					QJsonArray	jsonArrayGuestStars	= tmpObj["guest_stars"].toArray();

					QStringList	szCrew;
					QStringList	szGuestStars;

					for(int x = 0;x < jsonArrayCrew.count();x++)
					{
						tmpObj	= jsonArrayCrew.at(x).toObject();
						szCrew.append(QString("%1,%2").arg(tmpObj["name"].toString()).arg(tmpObj["job"].toString()));
					}
					if(szCrew.count())
						lpEpisode->setCrew(szCrew);

					for(int x = 0;x < jsonArrayGuestStars.count();x++)
					{
						tmpObj	= jsonArrayGuestStars.at(x).toObject();
						szGuestStars.append(QString("%1,%2").arg(tmpObj["name"].toString()).arg(tmpObj["character"].toString()));
					}
					if(szGuestStars.count())
						lpEpisode->setGuestStars(szGuestStars);
				}
			}
		}
	}
	else
	{
		qDebug() << reply->errorString();
		delete reply;
	}
	return(lpSerie);
}

QMap<qint32, QString> cTheMovieDBV3::genresMovie(const QString& szLanguage)
{
	QMap<qint32, QString>	genres;
	QNetworkAccessManager	networkManager;
	QString					szRequest	= QString("https://api.themoviedb.org/3/genre/movie/list?api_key=%1").arg(m_szToken);

	if(!szLanguage.contains("all"))
		szRequest.append(QString("&language=%1").arg(szLanguage));

	QNetworkReply*			reply   = networkManager.get(QNetworkRequest(QUrl(szRequest)));
	QEventLoop				loop;

	QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
	loop.exec();

	if(reply->error() == QNetworkReply::NoError)
	{
		QString			strReply		= (QString)reply->readAll();
		QJsonDocument	jsonResponse	= QJsonDocument::fromJson(strReply.toUtf8());
		QJsonObject		jsonObj			= jsonResponse.object();
		QJsonArray		jsonArray		= jsonObj["genres"].toArray();

		for(int z = 0;z < jsonArray.count();z++)
		{
			QJsonObject	genre			= jsonArray[z].toObject();

			genres.insert(genre["id"].toInt(), genre["name"].toString());
		}
	}
	else
	{
		qDebug() << reply->errorString();
		delete reply;
	}

	delete reply;

	return(genres);
}

QList<cMovie*> cTheMovieDBV3::discoverMovie(const QString& szText, const bool& bAdult, const qint16& iYear, const QList<qint32>& genres, const qreal& voteMin, const qreal& voteMax, const QString& szLanguage)
{
	if(m_genres.isEmpty())
		m_genres	= genresMovie("de-DE");

	QList<cMovie*>			movieList;
	QNetworkAccessManager	networkManager;
	QString					szRequest	= QString("https://api.themoviedb.org/3/discover/movie?api_key=%1").arg(m_szToken);
	qint16					page		= 1;

	if(!szLanguage.contains("all"))
		szRequest.append(QString("&language=%1").arg(szLanguage));

	if(!szText.isEmpty())
		szRequest.append(QString("&with_keywords=%1").arg(szText));
	szRequest.append(QString("&include_adult=%1").arg(bAdult?"true":"false"));
	szRequest.append(QString("&include_video=false"));
	if(iYear != -1)
		szRequest.append(QString("&year=%1").arg(iYear));
	if(genres.count())
	{
		QString	tmp	= QString::number(genres[0]);

		for(int x = 1;x < genres.count();x++)
			tmp.append(QString(",%1").arg(genres[x]));
		szRequest.append(QString("&with_genres=%1").arg(tmp));
	}
	szRequest.append(QString("&vote_average.gte=%1").arg(voteMin));
	szRequest.append(QString("&vote_average.lte=%1").arg(voteMax));

	for(;;)
	{
		QNetworkRequest			request(QUrl(QString("%1&page=%2").arg(szRequest).arg(page)));

		QNetworkReply*			reply   = networkManager.get(request);
		QEventLoop				loop;

		QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
		loop.exec();

		if (reply->error() == QNetworkReply::NoError)
		{
			QString			strReply		= (QString)reply->readAll();
			QJsonDocument	jsonResponse	= QJsonDocument::fromJson(strReply.toUtf8());
			QJsonObject		jsonObj			= jsonResponse.object();
			QJsonArray		jsonArray		= jsonObj["results"].toArray();

			for(int z = 0;z < jsonArray.count();z++)
			{
				QJsonObject	movie			= jsonArray[z].toObject();
				cMovie*		lpMovie			= new cMovie;
				lpMovie->setMovieTitle(movie["title"].toString());
				lpMovie->setMovieID(movie["id"].toInt());
				lpMovie->setOriginalTitle(movie["original_title"].toString());
				lpMovie->setReleaseDate(movie["release_date"].toString());
				lpMovie->setVoteCount(movie["vote_count"].toInt());
				lpMovie->setVideo(movie["video"].toBool());
				lpMovie->setVoteAverage(movie["vote_average"].toDouble());
				lpMovie->setPopularity(movie["popularity"].toDouble());
				lpMovie->setPosterPath(movie["poster_path"].toString());
				lpMovie->setOriginalLanguage(movie["original_language"].toString());

				QJsonArray	genresArray		= movie["genre_ids"].toArray();
				QList<qint32>	genresIDs;
				for(int y = 0;y < genresArray.count();y++)
					genresIDs.append(genresArray[y].toInt());
				if(genresIDs.count())
					lpMovie->setGenres(genresFromID(genresIDs));
				lpMovie->setBackdropPath(movie["backdrop_path"].toString());
				lpMovie->setAdult(movie["adult"].toBool());
				lpMovie->setOverview(movie["overview"].toString());
				lpMovie->setReleaseDate(movie["release_date"].toString());

				movieList.append(lpMovie);
			}
			if(jsonObj["total_pages"].toInt() == page)
				break;

			page++;
			if(page > 20)
				break;

			delete reply;
		}
		else
		{
			qDebug() << reply->errorString();
			delete reply;
		}
	}

	return(movieList);
}

QMap<qint32, QString> cTheMovieDBV3::genresSerie(const QString& szLanguage)
{
	QMap<qint32, QString>	genres;
	QNetworkAccessManager	networkManager;
	QString					szRequest	= QString("https://api.themoviedb.org/3/genre/tv/list?api_key=%1").arg(m_szToken);

	if(!szLanguage.contains("all"))
		szRequest.append(QString("&language=%1").arg(szLanguage));

	QNetworkReply*			reply   = networkManager.get(QNetworkRequest(QUrl(szRequest)));
	QEventLoop				loop;

	QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
	loop.exec();

	if(reply->error() == QNetworkReply::NoError)
	{
		QString			strReply		= (QString)reply->readAll();
		QJsonDocument	jsonResponse	= QJsonDocument::fromJson(strReply.toUtf8());
		QJsonObject		jsonObj			= jsonResponse.object();
		QJsonArray		jsonArray		= jsonObj["genres"].toArray();

		for(int z = 0;z < jsonArray.count();z++)
		{
			QJsonObject	genre			= jsonArray[z].toObject();

			genres.insert(genre["id"].toInt(), genre["name"].toString());
		}
	}
	else
	{
		qDebug() << reply->errorString();
		delete reply;
	}

	delete reply;

	return(genres);
}

QStringList cTheMovieDBV3::genresFromID(QList<qint32> genres)
{
	QStringList	szGenres;

	for(int x = 0;x < genres.count();x++)
	{
		qint32	genre	= genres[x];

		QMapIterator<qint32, QString> iterator(m_genres);
		while(iterator.hasNext())
		{
			iterator.next();

			if(iterator.key() == genre)
			{
				szGenres.append(iterator.value());
				break;
			}
		}
	}

	return(szGenres);
}

void cTheMovieDBV3::loadCastMovie(cMovie* lpMovie)
{
	QNetworkAccessManager	networkManager;
	QNetworkRequest			request(QUrl(QString("https://api.themoviedb.org/3/movie/%1/credits?api_key=%2").arg(lpMovie->movieID()).arg(m_szToken)));

	request.setRawHeader("Content-Type", "application/json");
//	if(!szLanguage.contains("all"))
//		request.setRawHeader("Accept-Language", szLanguage.toUtf8());
//	else
//		request.setRawHeader("Accept-Language", "en");
		request.setRawHeader("Accept-Language", "de");

	QNetworkReply*			reply   = networkManager.get(request);
	QEventLoop				loop;

	QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
	loop.exec();

	if (reply->error() == QNetworkReply::NoError)
	{
		QString			strReply		= (QString)reply->readAll();
		QJsonDocument	jsonResponse	= QJsonDocument::fromJson(strReply.toUtf8());
		QJsonObject		jsonCast		= jsonResponse.object();
		QJsonArray		jsonArrayCast	= jsonCast["cast"].toArray();
		QJsonArray		jsonArrayCrew	= jsonCast["crew"].toArray();
		QJsonObject		tmpObj;

		QStringList		szCast;
		QStringList		szCrew;

		delete reply;

		for(int x = 0;x < jsonArrayCast.count();x++)
		{
			tmpObj	= jsonArrayCast.at(x).toObject();
			szCast.append(QString("%1,%2").arg(tmpObj["name"].toString()).arg(tmpObj["character"].toString()));
		}
		if(szCast.count())
			lpMovie->setCast(szCast);

		for(int x = 0;x < jsonArrayCrew.count();x++)
		{
			tmpObj	= jsonArrayCrew.at(x).toObject();
			szCrew.append(QString("%1,%2").arg(tmpObj["name"].toString()).arg(tmpObj["job"].toString()));
		}
		if(szCrew.count())
			lpMovie->setCrew(szCrew);
	}
}

QList<cSerie*> cTheMovieDBV3::discoverSerie(const QString& szText, const qint16& iYear, const QList<qint32>& genres, const qreal& voteMin, const qreal& voteMax, const QString& szLanguage)
{
	if(m_genres.isEmpty())
		m_genres	= genresMovie("de-DE");

	QList<cSerie*>			serieList;
	QNetworkAccessManager	networkManager;
	QString					szRequest	= QString("https://api.themoviedb.org/3/discover/tv?api_key=%1").arg(m_szToken);
	qint16					page		= 1;

	if(!szLanguage.contains("all"))
		szRequest.append(QString("&language=%1").arg(szLanguage));

	if(!szText.isEmpty())
		szRequest.append(QString("&with_keywords=%1").arg(szText));
	if(iYear != -1)
		szRequest.append(QString("&first_air_date_year=%1").arg(iYear));
	if(genres.count())
	{
		QString	tmp	= QString::number(genres[0]);

		for(int x = 1;x < genres.count();x++)
			tmp.append(QString(",%1").arg(genres[x]));
		szRequest.append(QString("&with_genres=%1").arg(tmp));
	}
	szRequest.append(QString("&vote_average.gte=%1").arg(voteMin));
	szRequest.append(QString("&vote_average.lte=%1").arg(voteMax));

	for(;;)
	{
		QNetworkRequest			request(QUrl(QString("%1&page=%2").arg(szRequest).arg(page)));

		QNetworkReply*			reply   = networkManager.get(request);
		QEventLoop				loop;

		QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
		loop.exec();

		if (reply->error() == QNetworkReply::NoError)
		{
			QString			strReply		= (QString)reply->readAll();
			QJsonDocument	jsonResponse	= QJsonDocument::fromJson(strReply.toUtf8());
			QJsonObject		jsonObj			= jsonResponse.object();
			QJsonArray		jsonArray		= jsonObj["results"].toArray();
			QJsonArray		tmpArray;
			QStringList		tmpList;

			for(int z = 0;z < jsonArray.count();z++)
			{
				QJsonObject	serie			= jsonArray[z].toObject();
				cSerie*		lpSerie			= new cSerie;

				lpSerie->setSeriesID(serie["id"].toInt());
				lpSerie->setBackdropPath(serie["backdrop_path"].toString());
				tmpArray	= serie["created_by"].toArray();
				for(int x = 0;x < tmpArray.count();x++)
					tmpList.append(tmpArray.at(x).toObject()["name"].toString());
				lpSerie->setCreatedBy(tmpList);
				tmpList.clear();
				lpSerie->setFirstAired(serie["first_air_date"].toString());
				tmpArray	= serie["genres"].toArray();
				for(int x = 0;x < tmpArray.count();x++)
					tmpList.append(tmpArray.at(x).toObject()["name"].toString());
				lpSerie->setGenre(tmpList);
				tmpList.clear();
				lpSerie->setHomepage(serie["homepage"].toString());
				lpSerie->setLastAired(serie["last_air_date"].toString());
				tmpArray	= serie["languages"].toArray();
				for(int x = 0;x < tmpArray.count();x++)
					tmpList.append(tmpArray.at(x).toString());
				lpSerie->setLanguages(tmpList);
				tmpList.clear();
				lpSerie->setSeriesName(serie["name"].toString());
				tmpArray	= serie["networks"].toArray();
				for(int x = 0;x < tmpArray.count();x++)
					tmpList.append(tmpArray.at(x).toObject()["name"].toString());
				lpSerie->setNetworks(tmpList);
				tmpList.clear();
				lpSerie->setEpisodes(serie["number_of_episodes"].toInt());
				lpSerie->setSeasons(serie["number_of_seasons"].toInt());
				tmpArray	= serie["origin_country"].toArray();
				for(int x = 0;x < tmpArray.count();x++)
					tmpList.append(tmpArray.at(x).toString());
				lpSerie->setOriginCountries(tmpList);
				tmpList.clear();
				lpSerie->setOriginalLanguage(serie["original_language"].toString());
				lpSerie->setOriginalName(serie["original_name"].toString());
				lpSerie->setOverview(serie["overview"].toString());
				lpSerie->setPopularity(serie["popularity"].toDouble());
				lpSerie->setPosterPath(serie["poster_path"].toString());
				tmpArray	= serie["production_companies"].toArray();
				for(int x = 0;x < tmpArray.count();x++)
					tmpList.append(tmpArray.at(x).toObject()["name"].toString());
				lpSerie->setProductionCompanies(tmpList);
				tmpList.clear();
				lpSerie->setStatus(serie["status"].toString());
				lpSerie->setType(serie["type"].toString());
				lpSerie->setVoteAverage(serie["vote_average"].toDouble());
				lpSerie->setVoteCount(serie["vote_count"].toInt());

				serieList.append(lpSerie);
			}
			if(jsonObj["total_pages"].toInt() == page)
				break;

			page++;
			if(page > 20)
				break;

			delete reply;
		}
		else
		{
			qDebug() << reply->errorString();
			delete reply;
		}
	}

	return(serieList);
}

void cTheMovieDBV3::loadCastSerie(cSerie* lpSerie)
{
	cSerie*					lpSerie1	= loadSerie(lpSerie->seriesID(), "DE-de");

	lpSerie->setCast(lpSerie1->cast());
	lpSerie->setCrew(lpSerie1->crew());

	delete lpSerie1;
}
