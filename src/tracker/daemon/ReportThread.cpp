#include <QEventLoop>
#include <QStringList>
#include <QDebug>
#include "ReportThread.h"

ControlThread::ControlThread(QTcpSocket *socket, Control *control, QObject *parent):
        QObject(parent), m_client(socket), m_device(new QTextStream(socket)), m_daemon(control)
{
    m_processors.insert("start", &ControlThread::processStartQuery);
    m_processors.insert("stop", &ControlThread::processStopQuery);
    m_processors.insert("logs", &ControlThread::processLogsQuery);
    m_processors.insert("status", &ControlThread::processStatusQuery);
    connect(m_client,SIGNAL(readyRead()), SLOT(run()));
}


void ControlThread::run()
{
    QString query = m_device->readAll();
    qDebug() << "ControlThread running, query =" << query;
    QStringList commands=query.split(" ",QString::SkipEmptyParts);
    for (int i=0;i<commands.size();i++){
            qDebug() << "processing " << i << " command = " << commands.at(i);
            if(!commands.at(i).isEmpty() && m_processors.contains(commands.at(i)))
            {
                ProcessMethod method = m_processors.value(commands.at(i));
                (*this.*method)();
            }
    }
}

void ControlThread::processStartQuery()
{
    m_daemon->startTracking();
    (*m_device) << "<status>started</status>";
    m_device->flush();
}

void ControlThread::processStopQuery()
{
    m_daemon->stopTracking();
    (*m_device) << "<status>stoped</status>";
    m_device->flush();
}

void ControlThread::processStatusQuery()
{
    if(m_daemon->isTracking())
        (*m_device) << "<status>started</status>";
    else
        (*m_device) << "<status>stoped</status>";
    m_device->flush();
}


void ControlThread::processLogsQuery()
{
    QStringList list = m_daemon->getLog();
    (*m_device) << "<log>";
    for(int i=0;i<list.size();i++)
        (*m_device) << list.at(i);
    (*m_device) << "</log>";
    m_device->flush();
}