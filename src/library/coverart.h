#ifndef COVERART_H
#define COVERART_H

#include <QObject>

#include "trackinfoobject.h"
#include "util/singleton.h"

class CoverArt : public QObject, public Singleton<CoverArt> {
    Q_OBJECT
  public:
    void setConfig(ConfigObject<ConfigValue>* pConfig);

    QString getStoragePath() const;
    QString getDefaultCoverLocation(QString coverArtName);
    QString getDefaultCoverName(QString artist,
                                    QString album,
                                    QString filename);

    bool deleteFile(const QString& location);
    bool saveFile(QImage cover, QString location);
    QString searchCoverArtFile(TrackInfoObject* pTrack);

  protected:
    CoverArt();
    virtual ~CoverArt();

    friend class Singleton<CoverArt>;

  private:
    ConfigObject<ConfigValue>* m_pConfig;

    const char* m_cDefaultImageFormat;

    QString searchInDiskCache(QString coverArtName);
    QString searchInTrackDirectory(QString directory);
};

#endif // COVERART_H