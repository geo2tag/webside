/*
 * Copyright 2010  Open Source & Linux Lab (OSLL)  osll@osll.spb.ru
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
/*!
 * \file AvailableChannelsResponseJSON.h
 * \brief header of AvailableChannelsResponseJSON
 *
 * File description
 *
 *  PROJ: OSLL/geo2tag
 * ------------------------------------------------------------------------ */

#ifndef _AvailableChannelsResponseJSON_H_4A2A94B8_1FF7_4618_B070_AE30B225EB95_INCLUDED_
#define _AvailableChannelsResponseJSON_H_4A2A94B8_1FF7_4618_B070_AE30B225EB95_INCLUDED_

#include "json/inc/JsonSerializer.h"

class AvailableChannelsResponseJSON: public JsonSerializer
{
  public:
    AvailableChannelsResponseJSON(QObject *parent=0);

    void setChannels(QSharedPointer<Channels> channels);

    virtual QByteArray getJson() const;

    virtual bool parseJson(const QByteArray&);

    virtual ~AvailableChannelsResponseJSON();

    //class AvailableChannelsResponseJSON
};
//_AvailableChannelsResponseJSON_H_4A2A94B8_1FF7_4618_B070_AE30B225EB95_INCLUDED_
#endif

/* ===[ End of file $HeadURL$ ]=== */
