/*
 * Copyright 2010  OSLL osll@osll.spb.ru
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
 * \file UserInternal.h
 * \brief Header of UserInternal
 *
 * PROJ: OSLL/geo2tag
 * ---------------------------------------------------------------- */


#ifndef _UserInternal_H_530385AA_47B5_4EFA_92BF_1C79CEC156BC_INCLUDED_
#define _UserInternal_H_530385AA_47B5_4EFA_92BF_1C79CEC156BC_INCLUDED_

#include "User.h"
#include "ChannelInternal.h"

namespace loader
{
 /*!
   * 
   */
  class User: public common::User
  {
    unsigned long m_id;
    std::string m_token;

  public:
    User(const std::string& login, const std::string& pass, unsigned long id, const std::string& token);
    
    unsigned long getId() const;
    
    const std::string& getToken() const;

    void subscribe(const CHandlePtr<loader::Channel>& channel);
    void unsubscribe(const CHandlePtr<loader::Channel>& channel);

    ~User();
  }; // class UserInternal
  
} // namespace loader

#endif //_UserInternal_H_530385AA_47B5_4EFA_92BF_1C79CEC156BC_INCLUDED_

/* ===[ End of file ]=== */
