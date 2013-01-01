/*
 * Copyright 2011  bac1ca  bac1ca89@gmail.com
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
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AS IS'' AND ANY EXPRESS OR
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
 *
 * \file FilterRectangleRequestJSON.cpp
 * \brief FilterRectangleRequestJSON implementation
 *
 * File description
 *
 * PROJ: OSLL/geo2tag
 * ---------------------------------------------------------------- */

#include <syslog.h>
#include "json/inc/FilterRectangleRequestJSON.h"

#include "json/inc/JsonSession.h"
#include "common/inc/FShape.h"
#include "common/inc/FShapeRectangle.h"

#ifndef Q_WS_SYMBIAN
#include <qjson/parser.h>
#include <qjson/serializer.h>
#else
#include "parser.h"
#include "serializer.h"
#endif

FilterRectangleRequestJSON::FilterRectangleRequestJSON(QObject *parent) : FilterRequestJSON(parent)
{
}


QByteArray FilterRectangleRequestJSON::getJson() const
{
  // TODO it's necessary for symbian client
  QJson::Serializer serializer;
  QVariantMap obj;
  obj.insert("auth_token", m_sessionsContainer->at(0)->getSessionToken());
  return serializer.serialize(obj);
}


bool FilterRectangleRequestJSON::parseJson(const QByteArray&data)
{
  clearContainers();
  FilterRequestJSON::parseJson(data);

  QJson::Parser parser;
  bool ok;
  QVariantMap result = parser.parse(data, &ok).toMap();
  if (!ok) return false;
  QString auth_token = result["auth_token"].toString();
  setTimeFrom(QDateTime::fromString(result["time_from"].toString(), "dd MM yyyy HH:mm:ss.zzz"));
  setTimeTo(QDateTime::fromString(result["time_to"].toString(), "dd MM yyyy HH:mm:ss.zzz"));

  double lat1, lat2, lon1, lon2;
  QVariantMap latData = result["latitude_shift"].toMap();
  lat1 = latData["latitude1"].toDouble(&ok);
  if (!ok) return false;

  lat2 = latData["latitude2"].toDouble(&ok);
  if (!ok) return false;

  QVariantMap lonData = result["longitude_shift"].toMap();
  lon1 = lonData["longitude1"].toDouble(&ok);
  if (!ok) return false;

  lon2 = lonData["longitude2"].toDouble(&ok);
  if (!ok) return false;

  syslog(LOG_INFO, "rect %f ,%f ,%f ,%f ", lat1, lat2, lon2, lon2);

  FShapeRectangle * shape = new FShapeRectangle(lat1, lon1, lat2, lon2);
  setShape(QSharedPointer<FShape>(shape));
  m_sessionsContainer->push_back(QSharedPointer<Session>(new JsonSession(auth_token, QDateTime::currentDateTime(), QSharedPointer<common::User>(NULL))));
  return true;
}
