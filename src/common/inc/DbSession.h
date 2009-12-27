/*!
 * \file DbSession.h
 * \brief Header of DbSession
 * \todo add comment here
 *
 * File description
 *
 * PROJ: OSLL/geo2tag
 * ---------------------------------------------------------------- */


#ifndef _DbSession_H_9BF6A8FE_DA47_4F7A_B008_2EA2842C490F_INCLUDED_
#define _DbSession_H_9BF6A8FE_DA47_4F7A_B008_2EA2842C490F_INCLUDED_

#include "Db.h"
#include "DataMarks.h"
#include "Channel.h"

namespace common
{
  /*!
   * \brief session with database
   */
  class DbSession: protected ODBC::CDbEnv, public ODBC::CDbConn
  {
    CHandlePtr<DataMarks> m_marks;
    CHandlePtr<Channels> m_channels;
    CHandlePtr<std::vector<CHandlePtr<common::User> > > m_users;

    unsigned long m_currtentUserId;

    void loadUsers(const std::string &login, const std::string &password);
    void loadChannels();
    void loadMarks();
    void loadRelations();

    void saveChannels();
    void saveMarks();
    void saveRelations();
    

    DbSession();


  public:

    ~DbSession();
    
    CHandlePtr<DataMarks> getMarks() const;

    CHandlePtr<Channels> getChannels() const;

    void loadData(const std::string &login, const std::string &password);

    void saveData();

    void storeMark(CHandlePtr<common::DataMark> m); //! this routine will be in private area
    void updateChannel(unsigned long long channel_id,  CHandlePtr<common::DataMark> m); //! this routine will be in private area

    CHandlePtr<common::User> getCurrentUser() const;

    static DbSession& getInstance();

  private:    
    DbSession(const DbSession& obj);
    DbSession& operator=(const DbSession& obj);

  }; // class DbSession
  
} // namespace common

#endif //_DbSession_H_9BF6A8FE_DA47_4F7A_B008_2EA2842C490F_INCLUDED_

/* ===[ End of file ]=== */
