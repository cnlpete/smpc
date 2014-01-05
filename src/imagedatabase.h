#ifndef IMAGEDATABASE_H
#define IMAGEDATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QStringList>
#include <QDir>
#include <QStandardPaths>
#include <QImage>
#include <QEventLoop>
#include <QMutex>

#include "common.h"
#include "mpdalbum.h"
#include "mpdartist.h"
#include "albuminformation.h"
#include "artistinformation.h"
#include "lastfmalbumprovider.h"
#include "databasefilljob.h"
#include "databasestatistic.h"
#include "imagedownloader.h"

class ImageDatabase : public QObject
{
    Q_OBJECT

public:
    explicit ImageDatabase(QObject *parent = 0);
    ~ImageDatabase();



    bool syncAlbums(QList<MpdAlbum*> *albums,MpdArtist *artist);
    bool syncArtists(QList<MpdAlbum*> &artists);
    bool hasAlbumArt(QString album,QString artist);
    bool hasArtistArt(QString artist);

    int imageIDFromHash(QString hashValue);
    int imageIDFromAlbumArtist(QString album,QString artist);
    int imageIDFromAlbum(QString album);
    int imageIDFromArtist(QString artist);


    QImage getAlbumImage(QString album, QString artist, bool download=false);
    QImage getAlbumImage(QString album, bool download=false);
    QImage getAlbumImage(int artworkID);

    QImage getArtistImage(QString artist,bool download=false);
    QImage getArtistImage(int artworkID);


public slots:
    void albumReady(AlbumInformation *albumInformation);
    void fillDatabase(QMap<MpdArtist*, QList<MpdAlbum*>* > *map);
    void fillDatabase(QList<MpdArtist*> *artistList);
    void enterAlbumInformation(AlbumInformation *info);
    void enterArtistInformation(ArtistInformation *info);

    void requestCoverImage(MpdAlbum album);
    void requestCoverArtistImage(MpdArtist artist);

    void requestStatisticUpdate();

    // Cleanups
    void cleanUPBlacklistedAlbums();
    void cleanupAlbums();
    void cleanupArtists();

    void cleanupDatabase();


private:
    QSqlDatabase *mDB;

    bool mAlbumSyncRunning;
    int mAlbumNo;
    LastFMAlbumProvider *mCurrentAlbumProvider;
    QList<MpdAlbum*>* mAlbums;
    MpdArtist *mAlbumArtist;
    DatabaseFillJob *mFiller;

    ImageDownloader *mDownloader;

    // Holds the currently playing album for cover image retrieval
    MpdAlbum mCoverAlbum;
    MpdArtist mCoverArtist;

    // Statistical variables
    int mAlbumCount;
    int mImageCount;
    int mArtistCount;
    int mAlbumBlacklistCount;

    int getArtistCount();
    int getAlbumCount();
    int getImageCount();
    int getBlacklistCount();

    DatabaseStatistic *updateStatistic();

signals:
    void requestAlbumDownload(MpdAlbum album);
    void coverAlbumArtReady(QVariant url);

    void requestArtistDownload(MpdArtist artist);
    void coverArtistArtReady(QVariant url);

    void albumEntered(QString name);

    void newStasticReady(DatabaseStatistic *statistic);


public slots:

};

#endif // IMAGEDATABASE_H
