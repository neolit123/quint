#include "codemodel.h"
#include <QFile>
#include <QDebug>

CodeModel::CodeModel() {
    // Put some programs there
    QFile f("Scratchpad.qml"); f.open(QIODevice::ReadOnly); m_program << f.readAll(); f.close();
}

void CodeModel::setProgram(QString program)
    {
    // Assume this is only called with a good program
    m_programString = program;
    // Save it to the scratchpad
    QFile f("Scratchpad.qml");
    f.open(QIODevice::ReadWrite|QIODevice::Truncate);
    f.write(program.toUtf8());
    f.close();
    emit published();
    }

void CodeModel::publish() {
    // Concatenate the program lines into one string
    QString cated;
    QStringList::const_iterator i = m_program.begin();
    while (i!=m_program.end())
    {
        cated.append(*i++);
        cated.append("\n");
    }
    m_programString = cated;
    emit published();
}

