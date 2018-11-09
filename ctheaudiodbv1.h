#ifndef CTHEAUDIODBV1_H
#define CTHEAUDIODBV1_H


#include "cartist.h"

#include <QString>
#include <QList>
#include <QStringList>
#include <QMap>


class cTheAudioDBV1
{
public:
	cTheAudioDBV1();
	~cTheAudioDBV1();

	QList<cArtist*>		searchArtist(const QString& szArtist);
private:
	QString				m_szToken;
};

#endif // CTHEAUDIODBV1_H
