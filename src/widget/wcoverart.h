#ifndef WCOVERART_H
#define WCOVERART_H

#include <QColor>
#include <QDomNode>
#include <QMouseEvent>
#include <QWidget>

#include "configobject.h"
#include "skin/skincontext.h"
#include "trackinfoobject.h"
#include "widget/wbasewidget.h"

class WCoverArt : public QWidget, public WBaseWidget {
    Q_OBJECT
  public:
    WCoverArt(QWidget* parent, ConfigObject<ConfigValue>* pConfig);
    virtual ~WCoverArt();

    void setup(QDomNode node, const SkinContext& context);

  public slots:
    void slotHideCoverArt();
    void slotLoadCoverArt(QString coverLocation, int trackId);

  private slots:
    void slotPixmapFound(QString location, QPixmap pixmap);

  protected:
    void paintEvent(QPaintEvent*);
    void resizeEvent(QResizeEvent*);
    void mousePressEvent(QMouseEvent*);
    void mouseMoveEvent(QMouseEvent*);
    void leaveEvent(QEvent*);

  private:
    void loadDefaultStatus();
    QPixmap scaledCoverArt(QPixmap normal);

    ConfigObject<ConfigValue>* m_pConfig;

    bool m_bCoverIsHovered;
    bool m_bCoverIsVisible;
    bool m_bDefaultCover;

    QPixmap m_defaultCover;
    QString m_sCoverTitle;
    QPixmap m_currentCover;
    QPixmap m_currentScaledCover;

    QPixmap m_iconHide;
    QPixmap m_iconShow;
    QCursor m_zoomCursor;

    QString m_lastRequestedLocation;
};

#endif // WCOVERART_H