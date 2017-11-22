#ifndef CWE_PARAMETERTAB_H
#define CWE_PARAMETERTAB_H

#include <QScrollArea>
#include <QMap>
#include <QJsonObject>
#include <SimCenter_widgets/sctrstates.h>

class CWE_StageTab;
class SCtr_MasterDataWidget;

namespace Ui {
class CWE_ParameterTab;
}

class CWE_ParameterTab : public QScrollArea
{
    Q_OBJECT

public:
    explicit CWE_ParameterTab(QWidget *parent = 0);
    ~CWE_ParameterTab();
    QWidget * getParameterSpace();
    void setViewState(SimCenterViewState);
    SimCenterViewState getViewState();
    void setData(QJsonObject &);

private:
    Ui::CWE_ParameterTab *ui;

    SimCenterViewState m_viewState;
    QJsonObject m_obj;
    QMap<QString, SCtr_MasterDataWidget *> *variableWidgets;
};

#endif // CWE_PARAMETERTAB_H