/*
quint: codemodel.cpp

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

#include "codemodel.h"
#include <QFile>
#include <QDebug>

CodeModel::CodeModel() {
    // Put some programs there
    QFile f("Scratchpad.qml"); f.open(QIODevice::ReadOnly); m_program << f.readAll(); f.close();
    f.setFileName("HelloWorld.qml"); f.open(QIODevice::ReadOnly); m_program << f.readAll(); f.close();
    f.setFileName("Raspberry.qml"); f.open(QIODevice::ReadOnly); m_program << f.readAll(); f.close();
    f.setFileName("Julia.qml"); f.open(QIODevice::ReadOnly); m_program << f.readAll(); f.close();
    f.setFileName("Fly.qml"); f.open(QIODevice::ReadOnly); m_program << f.readAll(); f.close();
    f.setFileName("VideoFx.qml"); f.open(QIODevice::ReadOnly); m_program << f.readAll(); f.close();
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

