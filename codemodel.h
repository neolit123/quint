/*
quint: codemodel.h

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

#ifndef CODEMODEL_H
#define CODEMODEL_H

#include <QtCore/QString>
#include <QtCore/QStringList>

class CodeModel : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString program READ program WRITE setProgram NOTIFY published)
    Q_PROPERTY(QStringList list READ list NOTIFY listChanged)
    Q_PROPERTY(QString preamble READ preamble)
    Q_PROPERTY(QString postamble READ postamble)

public:
    CodeModel();
    QString preamble() { return m_preamble; }
    QString postamble() { return m_postamble; }
    QString program() { return m_programString; }
    void setProgram(QString program);
    QStringList list() { return m_program; }

public Q_SLOTS:
    // Publish the current program for testing
    void publish();

Q_SIGNALS:
    void published();
    void listChanged();

private:
    QStringList m_program;
    QString m_programString;
    QString m_preamble;
    QString m_postamble;
};

#endif // CODEMODEL_H
