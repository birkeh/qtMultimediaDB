#include "cmainwindow.h"
#include <QApplication>
#include <QSettings>

#include "csplashscreen.h"


#define SHOW_SPLASH


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	QCoreApplication::setOrganizationName("WIN-DESIGN");
	QCoreApplication::setOrganizationDomain("windesign.at");
	QCoreApplication::setApplicationName("qtMultimediaDB");

	QSettings	settings;

#ifdef SHOW_SPLASH
	QPixmap			pixmap(":/splash.jpg");
#else
	QPixmap			pixmap(":/splashEmpty.png");
#endif

	QFont			splashFont;

	splashFont.setPixelSize(18);
	splashFont.setBold(true);

	cSplashScreen	splash(pixmap, splashFont);
	splash.setMessageRect(QRect(85, 310, 200, 100));

	splash.show();
	splash.showStatusMessage("<center><font color='white'>initializing...</font></center>");
	a.processEvents();

	cMainWindow w;
	if(settings.value("main/maximized").toBool())
		w.showMaximized();
	else
		w.show();

	splash.finish(&w);

	return a.exec();
}
