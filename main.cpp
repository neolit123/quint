#include <QtCore/qdebug.h>
#include <QtCore/qabstractanimation.h>
#include <QtDeclarative/qdeclarative.h>
#include <QtDeclarative/qdeclarativeengine.h>
#include <QtDeclarative/qdeclarativecomponent.h>
#include <QtCore/qdir.h>
#include <QtDeclarative/qdeclarativecontext.h>

#include <QGuiApplication>
#include <QtGui/QCursor>

#include <QtCore/qmath.h>

#include "codemodel.h"

#include "quintview.h"

struct Options
{
    Options() :
          maximized(false)
        , fullscreen(false)
        , vsync(true)
    {
    }

    QUrl file;
    bool maximized;
    bool fullscreen;
    bool vsync;
};

static void usage()
{
    qWarning("Usage: quint [options] <filename>");
    qWarning(" ");
    qWarning(" options:");
    qWarning("  --maximized ............................... run maximized");
    qWarning("  --fullscreen .............................. run fullscreen");
    qWarning("  --no-multisample .......................... Disable multisampling (anti-aliasing)");
    qWarning("  --continuous-update ....................... Continuously render the scene");
    qWarning("  --nonblocking-swap ........................ Do not wait for v-sync to swap buffers");
    qWarning("  --stereo .................................. Enable stereo on the GL context");
    qWarning("  --no-version-detection .................... Do not try to detect the version of the .qml file");
    qWarning("  --no-vsync-animations ..................... Do not use vsync based animations");

    qWarning(" ");
    exit(1);
}

int main(int argc, char ** argv)
{
    Options options;

    options.file = QUrl::fromLocalFile("test.qml");

    QStringList imports;
    for (int i = 1; i < argc; ++i) {
        if (*argv[i] != '-' && QFileInfo(QFile::decodeName(argv[i])).exists()) {
            options.file = QUrl::fromLocalFile(argv[i]);
        } else {
            const QString lowerArgument = QString::fromLatin1(argv[i]).toLower();
            if (lowerArgument == QLatin1String("--maximized"))
                options.maximized = true;
            else if (lowerArgument == QLatin1String("--fullscreen"))
                options.fullscreen = true;
            else if (lowerArgument == QLatin1String("-i") && i + 1 < argc)
                imports.append(QString::fromLatin1(argv[++i]));
            else if (lowerArgument == QLatin1String("--no-vsync-animations"))
                options.vsync = false;
            else if (lowerArgument == QLatin1String("--help")
                     || lowerArgument == QLatin1String("-help")
                     || lowerArgument == QLatin1String("--h")
                     || lowerArgument == QLatin1String("-h"))
                usage();
        }
    }

    QGuiApplication app(argc, argv);
    QWindow *window = 0;
    QDeclarativeEngine *engine = 0;
    CodeModel *model = 0;
    model = new CodeModel();

    int exitCode = 0;

    // Want nicer fonts
    qputenv("QT_DF_RANGE",QByteArray("0.15"));
    //qputenv("QML_FIXED_ANIMATION_STEP",QByteArray("1"));

    if (!options.file.isEmpty()) {
        QQuickView *qxView = new QuintView();
        qxView->setVSyncAnimations(options.vsync);
        engine = qxView->engine();
        for (int i = 0; i < imports.size(); ++i)
            engine->addImportPath(imports.at(i));
        window = qxView;
        qxView->rootContext()->setContextProperty("codemodel",model);
        qxView->rootContext()->setContextProperty("view",qxView);
        qxView->setSource(options.file);

        QObject::connect(engine, SIGNAL(quit()), QCoreApplication::instance(), SLOT(quit()));

        //window->setWindowFlags(Qt::Window | Qt::WindowSystemMenuHint | Qt::WindowTitleHint | Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint);
        window->setWindowFlags(Qt::Window);
        //window->setMouseGrabEnabled(true);
        app.setOverrideCursor( QCursor( Qt::BlankCursor ) );
        if (options.fullscreen)
            window->showFullScreen();
        else if (options.maximized)
            window->showMaximized();
        else
            window->show();
        window->setVisible(true);

        exitCode = app.exec();

        delete window;
    }

    return exitCode;
}
