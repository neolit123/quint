/*
quint: main.cpp

Copyright (C) 2012 Andrew Baldwin

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
of the Software, and to permit persons to whom the Software is furnished to do
so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

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

int main(int argc, char ** argv)
{
    QGuiApplication app(argc, argv);
    QWindow *window = 0;
    QDeclarativeEngine *engine = 0;
    CodeModel *model = 0;
    model = new CodeModel();

    int exitCode = 0;

    // Want nicer fonts
    qputenv("QT_DF_RANGE",QByteArray("0.15"));
    //qputenv("QML_FIXED_ANIMATION_STEP",QByteArray("1"));

    QQuickView *qxView = new QuintView();
    engine = qxView->engine();
    window = qxView;
    qxView->rootContext()->setContextProperty("codemodel",model);
    qxView->rootContext()->setContextProperty("view",qxView);
    qxView->setSource(QUrl::fromLocalFile("quint.qml"));

    QObject::connect(engine, SIGNAL(quit()), QCoreApplication::instance(), SLOT(quit()));

    //window->setWindowFlags(Qt::Window | Qt::WindowSystemMenuHint | Qt::WindowTitleHint | Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint);
    window->setWindowFlags(Qt::Window);
    //window->setMouseGrabEnabled(true);
    app.setOverrideCursor( QCursor( Qt::BlankCursor ) );
    //window->showFullScreen();
    //window->showMaximized();
    window->show();
    window->setVisible(true);

    exitCode = app.exec();

    delete window;

    return exitCode;
}
