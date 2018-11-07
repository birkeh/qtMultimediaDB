#ifndef CFANARTTV_H
#define CFANARTTV_H


#include "cfanart.h"

#include <QString>


/*!
 \brief

 \class cFanartTV cfanarttv.h "cfanarttv.h"
*/
class cFanartTV
{
public:
	cFanartTV();

	/*!
	 \brief

	 \fn loadFanartSerie
	 \param iID
	 \return cFanartList
	*/
	cFanartList loadFanartSerie(const qint32 &iID);
	/*!
	 \brief

	 \fn loadFanartMovie
	 \param szIMDBID
	 \return cFanartList
	*/
	cFanartList loadFanartMovie(const QString& szIMDBID);
private:
	QString		m_szAPIKey; /*!< TODO: describe */

	/*!
	 \brief

	 \fn processArray
	 \param array
	 \param fanartList
	 \param type
	*/
	void		processArray(const QJsonArray& array, cFanartList& fanartList, cFanart::Type type);
};

#endif // CFANARTTV_H
