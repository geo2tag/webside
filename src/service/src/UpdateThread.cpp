#include <QDebug>
#include "UpdateThread.h"

UpdateThread::UpdateThread(const QSharedPointer<DataMarks> &tags,
                           const QSharedPointer<Users> &users,
                           const QSharedPointer<Channels> &channels,
                           QObject *parent):
    QThread(parent),
    m_channelsContainer(channels),
    m_tagsContainer(tags),
    m_usersContainer(users)
{
    m_database = QSqlDatabase::addDatabase("QPSQL");
    m_database.setHostName("localhost");
    m_database.setDatabaseName("geo2tag");
    m_database.setUserName("geo2tag");
    m_database.setPassword("");
}

void UpdateThread::run()
{
    for(;;)
    {
        qDebug("trying to connect to database..., file: %s, line: %d", __FILE__, __LINE__);
        bool result = m_database.open();
        if(!result)
        {
            qDebug() << "connection error" << m_database.lastError();
            QThread::msleep(1000);
            continue;
        }
        qDebug() << "connected...";
        Users       usersContainer(*m_usersContainer);
        DataMarks   tagsContainer(*m_tagsContainer);
        Channels    channelsContainer(*m_channelsContainer);

        loadUsers(usersContainer);
        loadTags(tagsContainer);
        loadChannels(channelsContainer);

        m_updateLock.lockForWrite();
        m_usersContainer->merge(usersContainer);
        m_tagsContainer->merge(tagsContainer);
        m_channelsContainer->merge(channelsContainer);
        m_updateLock.unlock();

        qDebug() << "current users' size = " << m_usersContainer->size();
        qDebug() << "current tags' size = " << m_tagsContainer->size();
        qDebug() << "current channels' size = " << m_channelsContainer->size();
        m_database.close();
        QThread::msleep(10000);
    }
}

void UpdateThread::loadUsers(Users &container)
{
    QSqlQuery query(m_database);
    query.exec("select id, login, password, token from users order by id;");
    while (query.next())
    {
        qlonglong id = query.record().value("id").toLongLong();
        if(container.exist(id))
        {
            // skip record
            continue;
        }
        QString login = query.record().value("login").toString();
        QString password = query.record().value("password").toString();
        QString token = query.record().value("token").toString();
        DbUser *newUser = new DbUser(login,password,id,token);
        QSharedPointer<DbUser> pointer(newUser);
        container.push_back(pointer);
    }
}

void UpdateThread::loadChannels(Channels &container)
{
    QSqlQuery query(m_database);
    query.exec("select id, description, name, url from channel order by id;");
    while (query.next())
    {
        qlonglong id = query.record().value("id").toLongLong();
        if(container.exist(id))
        {
            // skip record
            continue;
        }
        QString name = query.record().value("name").toString();
        QString description = query.record().value("description").toString();
        QString url = query.record().value("url").toString();
        DbChannel *newChannel = new DbChannel(id,name,description,url);
        QSharedPointer<DbChannel> pointer(newChannel);
        container.push_back(pointer);
    }
}

void UpdateThread::loadTags(DataMarks &container)
{
    QSqlQuery query(m_database);
    query.exec("select id, time, latitude, longitude, label, description, url, user_id from tag order by time;");
    while (query.next())
    {
        qlonglong id = query.record().value("id").toLongLong();
        if(container.exist(id))
        {
            // skip record
            continue;
        }
        QDateTime time = query.record().value("time").toDateTime();
        qreal latitude = query.record().value("latitude").toReal();
        qreal longitude = query.record().value("longitude").toReal();
        QString label = query.record().value("label").toString();
        QString description = query.record().value("description").toString();
        QString url = query.record().value("url").toString();
        qlonglong userId = query.record().value("user_id").toLongLong();

        DbDataMark *newMark = new DbDataMark(id,
                                                         latitude,
                                                         longitude,
                                                         label,
                                                         description,
                                                         url,
                                                         time,
                                                         userId);
        QSharedPointer<DbDataMark> pointer(newMark);
        container.push_back(pointer);
    }
}

void UpdateThread::updateReflections(DataMarks &tags, Users &users, Channels &channels)
{
    {
        QSqlQuery query(m_database);
        query.exec("select user_id, channel_id from subscribe;");
        while (query.next())
        {
            qlonglong user_id = query.record().value("user_id").toLongLong();
            qlonglong channel_id = query.record().value("channel_id").toLongLong();
            users.item(user_id)->subscribe(channels.item(channel_id));
        }
    }
    {
        QSqlQuery query(m_database);
        query.exec("select tag_id, channel_id from tags;");
        while (query.next())
        {
            qlonglong tag_id = query.record().value("tag_id").toLongLong();
            qlonglong channel_id = query.record().value("channel_id").toLongLong();
            tags.item(tag_id)->setChannel(channels.item(channel_id));
        }
    }
    for(int i=0; i<tags.size(); i++)
    {
        tags[i]->setUser(users.item(tags.at(i).dynamicCast<DbDataMark>()->getUserId()));
    }

}
