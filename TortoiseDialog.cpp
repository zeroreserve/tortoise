

#include "TortoiseDialog.h"
#include "p3TortoiseRS.h"

#include <QMenu>
#include <QStandardItem>
#include <list>


#define IMAGE_FRIENDINFO ":/images/peerdetails_16x16.png"


TortoiseDialog::TortoiseDialog(p3TortoiseRS * tortoiseRS , QWidget *parent)
    : MainPage(parent),
      m_Tortoise( tortoiseRS )
{
    ui.setupUi(this);

    connect( ui.clientHashButton, SIGNAL( clicked() ), this, SLOT( addMonitor() ) );
    connect( ui.serverHashButton, SIGNAL( clicked() ), this, SLOT( setListener() ) );
    connect( ui.sendMessageButton, SIGNAL( clicked() ), this, SLOT( sendMessage() ) );
}


void TortoiseDialog::addMonitor()
{
    m_Tortoise->addMonitor( ui.clientHash->text().toStdString() );
}

void TortoiseDialog::setListener()
{
    m_Tortoise->setListener( ui.serverHash->text().toStdString() );
}

void TortoiseDialog::sendMessage()
{
    m_Tortoise->sendMessage( ui.message->text().toStdString() );
}
