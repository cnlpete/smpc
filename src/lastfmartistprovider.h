#ifndef LastFMArtistProvider_H
#define LastFMArtistProvider_H

#include <QObject>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QXmlStreamReader>

#include "mpdartist.h"
#include "common.h"
#include "artistinformation.h"

#define COVERSIZE "mega"


class LastFMArtistProvider : public QObject
{
    Q_OBJECT
public:
    LastFMArtistProvider(QString artistName,QObject *parent=0);
    LastFMArtistProvider(MpdArtist &artist);
    ~LastFMArtistProvider();

    void startDownload();


    void setArtist(QString artist);

    QString getImageURL();

    ArtistInformation* getLastInformation();

public slots:
    void requestDownload(MpdArtist artist);

signals:
    void ready(ArtistInformation *artistInfo);
    void readyRead();
    void failed();

private:
    QString mArtistName;
    QString mImageURL;
    QString mArtistInfo;
    QByteArray *mImageData;
    QNetworkAccessManager *mXMLNetAccess;
    QNetworkAccessManager *mArtistArtAccess;
    ArtistInformation *mLastInformation;

    void parseArtist(QXmlStreamReader &xmlReader);
    void parseWikiInformation(QXmlStreamReader &xmlReader);
    void downloadImageData(QUrl imageURL);

private slots:
    void xmlDownloaded(QNetworkReply*);
    void imageDownloaded(QNetworkReply*);
//    void downloadError(QNetworkReply*);

};

#endif // LASTFMURLPROVIDER_H
