#pragma once

#include <QDomNode>
#include <QMouseEvent>
#include <QString>
#include <QWidget>

#include "skin/skincontext.h"
#include "util/parented_ptr.h"
#include "widget/wcuemenupopup.h"
#include "widget/wpushbutton.h"

class WHotcueButton : public WPushButton {
    Q_OBJECT
  public:
    WHotcueButton(const QString& group, QWidget* pParent);

    void setup(const QDomNode& node, const SkinContext& context) override;

    Q_PROPERTY(bool light MEMBER m_isCueColorLight);
    Q_PROPERTY(bool dark MEMBER m_isCueColorDark);
    Q_PROPERTY(QString type MEMBER m_type);

  protected:
    void mousePressEvent(QMouseEvent* e) override;
    void restyleAndRepaint() override;

  private slots:
    void slotColorChanged(double color);
    void slotTypeChanged(double type);

  private:
    ConfigKey createConfigKey(const QString& name);
    void updateStyleSheet();

    const QString m_group;
    int m_hotcue;
    bool m_hoverCueColor;
    parented_ptr<ControlProxy> m_pCoColor;
    parented_ptr<ControlProxy> m_pCoType;
    parented_ptr<WCueMenuPopup> m_pCueMenuPopup;
    bool m_cueColorDimmed;
    bool m_isCueColorLight;
    bool m_isCueColorDark;
    QString m_type;
};
