#include "LoginThread.h"
#include "TrackThread.h"
#include "LoadTagsThread.h"
#include "ProfilerThread.h"
#include <time.h>
#include <QDebug>
#include "JsonUser.h"
#include "JsonChannel.h"
#include "JsonDataMark.h"
#include <QCoreApplication>
//#include "ThreadCleaner.h"


// Usage 
/* ./profiler @number_of_iterations@ @method@ @token@ @channel@ 
 @number_of_iterations@ - number of iterations that should be performed(or -1 if it should work till infinity);
 @method@ - performed operation - login | writeTag | loadTags;
 @token@ - auth_token for track operation;
 @channel@ - channel for track operation; 
*/ 


int main(int argc,char** argv)
{
  QCoreApplication app(argc,argv);
  if (argc >= 3)
  {
    QEventLoop loop;
    int number_of_op = QString(argv[1]).toInt();
    ProfilerThread::m_number_of_requests = number_of_op;
    if (QString(argv[2]) == "login") //perform login testing
    {
      srand ( time(NULL) );
      for (int i=0;i<4;i++)
      {
	LoginThread * thread = new LoginThread();
        QObject::connect(thread,SIGNAL(terminated()),&loop,SLOT(quit()));
        QObject::connect(thread,SIGNAL(finished()),&loop,SLOT(quit()));
        thread->start(); 
      }
    }else if (QString(argv[2]) == "writeTag") // perform track testing
    {
      QSharedPointer<DataMark> tag(new JsonDataMark(0.0,0.0,0.0,"","","",QDateTime::currentDateTime()));
      QSharedPointer<common::User> user(new JsonUser("","",argv[3]));
      QSharedPointer<Channel> channel(new JsonChannel(argv[4],"",""));
      tag->setChannel(channel);
      tag->setUser(user);
      for (int i=0;i<4;i++)
      {
	TrackThread * thread = new TrackThread(tag);
        QObject::connect(thread,SIGNAL(terminated()),&loop,SLOT(quit()));
        QObject::connect(thread,SIGNAL(finished()),&loop,SLOT(quit()));
        thread->start(); 
      }
    }else if (QString(argv[2]) == "loadTags") // perform track testing
    {
      QSharedPointer<common::User> user(new JsonUser("","",argv[3]));
      for (int i=0;i<4;i++)
      {
	LoadTagsThread * thread = new LoadTagsThread(user);
        QObject::connect(thread,SIGNAL(terminated()),&loop,SLOT(quit()));
        QObject::connect(thread,SIGNAL(finished()),&loop,SLOT(quit()));
        thread->start(); 
      }
    } else 
    {
       qDebug() <<"unknown request";
       return 1;
    }

    loop.exec();
    return 0;

  }else    qDebug() << "not enough args!";

  return 1;

} 