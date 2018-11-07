#ifndef CMOVIEIMAGE_H
#define CMOVIEIMAGE_H


#include <QPixmap>


/*!
 \brief

 \class cMovieImage cmovieimage.h "cmovieimage.h"
*/
class cMovieImage
{
public:
	cMovieImage();
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

#endif // CMOVIEIMAGE_H
