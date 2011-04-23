#include "MapsUploadThread.h"
#include <math.h>
#include <QNetworkReply>
#include <QNetworkDiskCache>
#include <QDesktopServices>
#include <QVector>
#include <QVectorIterator>
#include <QDebug>
#include <QDir>
#include <QBuffer>


MapsUploadThread::MapsUploadThread(QVector<TilePoint> & tiles, QObject * parent) :
        QThread(parent), m_tiles(tiles)
{
    qDebug() << "Parent thread" << this->thread();
}

void MapsUploadThread::uploadingFinished()
{
    this->exit(0);
}

void MapsUploadThread::run()
{
    MapsUploader * uploader = new MapsUploader(0);
    //connect(uploader, SIGNAL(uploadingFinished()), this, SLOT(uploadingFinished()));
    qDebug() << "Children thread" << uploader->thread();
    uploader->uploadTilesBG(m_tiles);

    exec();
}
