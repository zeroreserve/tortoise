#ifndef TORTOISEDIALOG_H
#define TORTOISEDIALOG_H


#include "ui_TortoiseDialog.h"

#include "retroshare-gui/mainpage.h"


class TortoiseDialog : public MainPage
{
    Q_OBJECT

public:
    TortoiseDialog( QWidget *parent = 0 );


private:

    Ui::TortoiseDialog ui;

};

#endif // TORTOISEDIALOG_H
