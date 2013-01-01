/*
 * Copyright 2012  Mark Zaslavskiy  mark.zaslavskiy@gmail.com
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
 * \file ProfilerThread.h
 * \brief Header of ProfilerThread
 * \todo add comment here
 *
 * File description
 *
 * PROJ: OSLL/geo2tag
 * ---------------------------------------------------------------- */

#ifndef _ProfilerThread_H_FF30C939_DBCD_4AC8_AE14_506674F6D5B6_INCLUDED_
#define _ProfilerThread_H_FF30C939_DBCD_4AC8_AE14_506674F6D5B6_INCLUDED_

/*!
 * Class description. May use HTML formatting
 *
 */

#include <QThread>
#include <QTimer>
#include "DefaultQuery.h"

class ProfilerThread: public QThread
{
  Q_OBJECT;

  static int m_counter;
  QDateTime m_sendTime;
  void run();
  public:
    static int m_number_of_requests;
    static double m_requests_per_second;
    ProfilerThread();
    ~ProfilerThread();

    DefaultQuery * m_query;
    void setConnections();

    static int getCounter() ;
    static void incCounter() ;

    signals:

    void doRequest();

  public slots:

    void sendRequest();
    void responseReceived();

};                                      // class ProfilerThread
#endif                                  //_ProfilerThread_H_FF30C939_DBCD_4AC8_AE14_506674F6D5B6_INCLUDED_
