#ifndef CFANARTIMAGE_H
#define CFANARTIMAGE_H


#include <QPixmap>


/*!
 \brief

 \class cFanartImage cfanartimage.h "cfanartimage.h"
*/
class cFanartImage
{
public:
	cFanartImage();
	/*!
	 \brief

	 \fn getImage
	 \param szFileName
	 \return QPixmap
	*/
	QPixmap	getImage(const QString& szFileName);
private:
	/*!
	 \brief

	 \fn downloadFile
	 \param szFileName
	 \return QPixmap
	*/
	QPixmap	downloadFile(const QString& szFileName);
};

#endif // CFANARTIMAGE_H
