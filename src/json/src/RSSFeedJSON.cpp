/*
 * Copyright 2010  Open Source & Linux Lab (OSLL) osll@osll.spb.ru
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * 3. The name of the author may not be used to endorse or promote
 *    products derived from this software without specific prior written
 *    permission.
 *
 * The advertising clause requiring mention in adverts must never be included.
 */

/*! ---------------------------------------------------------------
 * $Id$
 *
 * \file RSSFeedJSON.cpp
 * \brief RSSFeedJSON implementation
 *
 * File description
 *
 * PROJ: OSLL/geo2tag
 * ---------------------------------------------------------------- */

#include <qjson/parser.h>
#include <qjson/serializer.h>

#include <QVariant>
#include <QDebug>
#include "RSSFeedJSON.h"
#include "User.h"

#include "JsonUser.h"
#include "JsonChannel.h"
#include "JsonDataMark.h"

RSSFeedResponseJSON::RSSFeedResponseJSON()
{
}

void RSSFeedResponseJSON::parseJson(const QByteArray &data)
{
    clearContainers();

    QJson::Parser parser;
    bool ok;
    QVariantMap result = parser.parse(data, &ok).toMap();

    if (!ok)
    {
        qFatal("An error occured during parsing json with rss feed");
        return;
    }

    QVariantMap rss = result["rss"].toMap();
    QVariantMap channelVariant = rss["channel"].toMap();
    QVariantList marksList = channelVariant["items"].toList();

    int size = marksList.size();
    for (int i = 0; i < size; i++)
    {
        QVariantMap markMap = marksList.at(i).toMap();

        QString title = markMap["title"].toString();
        QString link = markMap["link"].toString();
        QString description = markMap["description"].toString();
        double latitude = markMap["latitude"].toString().toDouble();
        double longitude = markMap["longitude"].toString().toDouble();
        QString userName = markMap["user"].toString();
        QString timeStr =  markMap["pubDate"].toString();
        QDateTime time = QDateTime::fromString(timeStr, "dd MM yyyy HH:mm:ss.zzz");


        QVector<QSharedPointer<User> > v = m_usersContainer->vector();
        QSharedPointer<User> user(new JsonUser(userName));
        m_usersContainer->push_back(user);

        QSharedPointer<JsonDataMark> newMark(new JsonDataMark(latitude,
                                                 longitude,
                                                 title,
                                                 description,
                                                 link,
                                                 time));
        newMark->setUser(user);
        m_tagsContainer->push_back(newMark);
    }
}

QByteArray RSSFeedResponseJSON::getJson() const
{
    QJson::Serializer serializer;
    QVariantMap obj, rss, channel;
    QVariantList tags;
    for(int i=0; i<m_tagsContainer->size(); i++)
    {
        QSharedPointer<DataMark> tag = m_tagsContainer->at(i);
        QVariantMap jtag;
        jtag["title"] = tag->getLabel();
        jtag["link"] = tag->getUrl();
        jtag["description"] = tag->getDescription();
        jtag["latitude"] = tag->getLatitude();
        jtag["longitude"] = tag->getLongitude();
        jtag["user"] = tag->getUser()->getLogin();
        jtag["pubDate"] = tag->getTime().toString("dd MM yyyy HH:mm:ss.zzz");
        tags.append(jtag);
    }
    channel["items"] = tags;
    rss["channel"] = channel;
    obj["rss"] = rss;
    return serializer.serialize(rss);
}

RSSFeedResponseJSON::~RSSFeedResponseJSON()
{
}

/* ===[ End of file $HeadURL$ ]=== */
