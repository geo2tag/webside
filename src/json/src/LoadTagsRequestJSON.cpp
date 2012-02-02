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

#include <QVariant>
#include <QDebug>
#include "LoadTagsRequestJSON.h"

#include "JsonUser.h"
#include "JsonChannel.h"
#include "JsonDataMark.h"

#ifndef Q_OS_SYMBIAN
#include <qjson/parser.h>
#include <qjson/serializer.h>
#else
#include "parser.h"
#include "serializer.h"
#endif

LoadTagsRequestJSON::LoadTagsRequestJSON(double latitude, double longitude, double radius, QObject *parent):
JsonSerializer(parent), m_latitude(latitude), m_longitude(longitude), m_radius(radius)
{
}


LoadTagsRequestJSON::LoadTagsRequestJSON(QObject *parent) :JsonSerializer(parent)
{
}


bool LoadTagsRequestJSON::parseJson(const QByteArray &data)
{
  clearContainers();

  QJson::Parser parser;
  bool ok;
  QVariantMap result = parser.parse(data, &ok).toMap();

  if (!ok) return false;

  QString authToken = result["auth_token"].toString();
  m_usersContainer->push_back(QSharedPointer<common::User>(new JsonUser("dummyUser[LoadTagsRequest]","dummyPassword",authToken)));

  result["latitude"].toDouble(&ok);
  if (!ok) return false;
  m_latitude = result["latitude"].toDouble(&ok);

  result["longitude"].toDouble(&ok);
  if (!ok) return false;
  m_longitude = result["longitude"].toDouble(&ok);

  result["radius"].toDouble(&ok);
  if (!ok) return false;
  m_radius = result["radius"].toDouble(&ok);

  return true;
}


QByteArray LoadTagsRequestJSON::getJson() const
{
  QJson::Serializer serializer;
  QVariantMap obj;
  obj.insert("auth_token", getAuthToken());
  obj.insert("latitude", getLatitude());
  obj.insert("longitude", getLongitude());
  obj.insert("radius", getRadius());
  return serializer.serialize(obj);
}


QString LoadTagsRequestJSON::getAuthToken() const
{
  return m_usersContainer->at(0)->getToken();
}


double LoadTagsRequestJSON::getLatitude() const
{
  return m_latitude;
}


double LoadTagsRequestJSON::getLongitude() const
{
  return m_longitude;
}


double LoadTagsRequestJSON::getRadius() const
{
  return m_radius;
}


void LoadTagsRequestJSON::setLatitude(double latitude)
{
  m_latitude = latitude;
}


void LoadTagsRequestJSON::setLongitude(double longitude)
{
  m_longitude = longitude;
}


void LoadTagsRequestJSON::setRadius(double radius)
{
  m_radius = radius;
}


LoadTagsRequestJSON::~LoadTagsRequestJSON()
{
}


/* ===[ End of file $HeadURL$ ]=== */
