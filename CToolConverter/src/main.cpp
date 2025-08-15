#include <QCoreApplication>
#include <CTI_Project.h>

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	
	QStringList args = a.arguments();
    if (args.size() > 1) {
		QString arg = args.at(1); // first argument after program name
		qDebug() << "Got argument:" << arg;

		if (arg.endsWith(".json", Qt::CaseInsensitive)) {
			CTI::Project prj;
			prj.test(arg);
			return 0;
		}
    }
    
	
	return a.exec();
}
