#include "cmainwindow.h"
#include <QApplication>
#include <QSettings>
#include <QSplashScreen>


#define SHOW_SPLASH


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	QCoreApplication::setOrganizationName("WIN-DESIGN");
	QCoreApplication::setOrganizationDomain("windesign.at");
	QCoreApplication::setApplicationName("qtMovies");

	QSettings	settings;

#ifdef SHOW_SPLASH
	QPixmap			pixmap(":/splash.jpg");
#else
	QPixmap			pixmap(":/splashEmpty.png");
#endif

	QSplashScreen	splash(pixmap);
	splash.show();
	splash.showMessage("initializing...");
	a.processEvents();

	cMainWindow w;
	if(settings.value("main/maximized").toBool())
		w.showMaximized();
	else
		w.show();

	splash.finish(&w);

	return a.exec();
}
