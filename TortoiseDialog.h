#ifndef TORTOISEDIALOG_H
#define TORTOISEDIALOG_H


#include "ui_TortoiseDialog.h"

#include "retroshare-gui/mainpage.h"

class p3TortoiseRS;

class TortoiseDialog : public MainPage
{
    Q_OBJECT

public:
    TortoiseDialog( p3TortoiseRS *tortoiseRS, QWidget *parent = 0 );

protected slots:
    void addMonitor();
    void setListener();

private:

    Ui::TortoiseDialog ui;
    p3TortoiseRS * m_Tortoise;

};

#endif // TORTOISEDIALOG_H
