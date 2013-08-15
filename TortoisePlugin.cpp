
#include "TortoisePlugin.h"
#include "TortoiseDialog.h"

#include "p3TortoiseRS.h"


#include <retroshare/rsplugin.h>
#include <util/rsversion.h>
#include <QTranslator>
#include <QMessageBox>


TortoisePlugin * g_TortoisePlugin;

extern "C" {
	void *RETROSHARE_PLUGIN_provide()
	{
        g_TortoisePlugin = new TortoisePlugin() ;
        return (void*) g_TortoisePlugin;
	}
	// This symbol contains the svn revision number grabbed from the executable. 
	// It will be tested by RS to load the plugin automatically, since it is safe to load plugins
	// with same revision numbers, assuming that the revision numbers are up-to-date.
	//
	uint32_t RETROSHARE_PLUGIN_revision = SVN_REVISION_NUMBER ;

	// This symbol contains the svn revision number grabbed from the executable. 
	// It will be tested by RS to load the plugin automatically, since it is safe to load plugins
	// with same revision numbers, assuming that the revision numbers are up-to-date.
	//
	uint32_t RETROSHARE_PLUGIN_api = RS_PLUGIN_API_VERSION ;
}

#define IMAGE_LINKS ":/images/bitcoin.png"

void TortoisePlugin::getPluginVersion(int& major,int& minor,int& svn_rev) const
{
    major = 5 ;
    minor = 4 ;
    svn_rev = SVN_REVISION_NUMBER ;
}

TortoisePlugin::TortoisePlugin()
{
    mainpage = NULL ;
    mIcon = NULL ;
    mPlugInHandler = NULL;
    m_Tortoise = NULL;
    m_peers = NULL;

}

void TortoisePlugin::setInterfaces(RsPlugInInterfaces &interfaces)
{
    m_peers = interfaces.mPeers;
}

MainPage *TortoisePlugin::qt_page() const
{
    if(mainpage == NULL){
        mainpage = new TortoiseDialog( );
    }

    return mainpage ;
}


void TortoisePlugin::setPlugInHandler(RsPluginHandler *pgHandler)
{
    mPlugInHandler = pgHandler;
}

QIcon *TortoisePlugin::qt_icon() const
{
    if(mIcon == NULL)
    {
        Q_INIT_RESOURCE(Tortoise_images) ;

        mIcon = new QIcon(IMAGE_LINKS) ;
    }

    return mIcon ;
}

RsPQIService * TortoisePlugin::rs_pqi_service() const
{
    if(m_Tortoise == NULL){
        m_Tortoise = new p3TortoiseRS(mPlugInHandler, m_peers ) ;
    }

    return m_Tortoise ;
}

std::string TortoisePlugin::getShortPluginDescription() const
{
    return QApplication::translate("TortoisePlugin", "This plugin says \"hello\"").toUtf8().constData();
}

std::string TortoisePlugin::getPluginName() const
{
    return QApplication::translate("TortoisePlugin", "Tortoise" ).toUtf8().constData();
}

QTranslator* TortoisePlugin::qt_translator(QApplication */*app*/, const QString& languageCode, const QString& externalDir) const
{
    if (languageCode == "en") {
        return NULL;
    }

    QTranslator* translator = new QTranslator();

    if (translator->load(externalDir + "/Tortoise_" + languageCode + ".qm")) {
        return translator;
    } else if (translator->load(":/lang/Tortoise_" + languageCode + ".qm")) {
        return translator;
    }

    delete(translator);
    return NULL;
}

QDialog * TortoisePlugin::qt_about_page() const
{
    static QMessageBox *about_dialog = NULL;

    if(about_dialog == NULL)
    {
        about_dialog = new QMessageBox() ;

        QString text ;
        text += QObject::tr("<h3>RetroShare Tortoise plugin</h3><br/>   * This example code is in the public domain<br/>" ) ;
        text += QObject::tr("<br/>Saying hello to each friend coming on-line") ;

        about_dialog->setText(text) ;
        about_dialog->setStandardButtons(QMessageBox::Ok) ;
    }

    return about_dialog ;
}

void TortoisePlugin::stop() const
{
    std::cerr << "Tortoise Plugin: Closing Database" << std::endl;

}
