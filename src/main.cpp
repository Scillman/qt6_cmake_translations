#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QLocale>
#include <QTranslator>

#include <QDebug>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "app_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            qDebug() << "Loaded translation:" << baseName;
            app.installTranslator(&translator);
            break;
        }
        else {
            qDebug() << "Failed translation:" << baseName;
        }
    }

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/App/qml/main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
