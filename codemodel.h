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
