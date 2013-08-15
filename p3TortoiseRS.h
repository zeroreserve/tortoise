

#ifndef P3TORTOISERRS_H
#define P3TORTOISERRS_H


#include "RSTortoiseItems.h"

#include "retroshare/rspeers.h"
#include "plugins/rspqiservice.h"
#include "pqi/pqimonitor.h"
#include "tortoise/tortoiseclientservice.h"




class RsPluginHandler;
class RsPeers;

class p3TortoiseRS : public RsPQIService,   // the service interface calls tick()
                    public pqiMonitor,     // the monitor tells us when friends changed their status
                    public RsTortoiseClientService
{
public:
    p3TortoiseRS(RsPluginHandler *pgHandler, RsPeers* peers);

    virtual int tick();
    virtual void statusChange(const std::list<pqipeer> &plist);

    virtual void addVirtualPeer(const TortoiseFileHash& hash,const TortoiseVirtualPeerId& virtual_peer_id,RsTortoiseGenericTunnelItem::Direction dir);
    virtual void removeVirtualPeer(const TortoiseFileHash& hash,const TortoiseVirtualPeerId& virtual_peer_id);
    virtual void receiveTortoiseData(RsTortoiseGenericTunnelItem */*item*/,const std::string& /*hash*/,const std::string& /*virtual_peer_id*/,RsTortoiseGenericTunnelItem::Direction /*direction*/);
    virtual bool handleTunnelRequest(const std::string& /*hash*/,const std::string& /*peer_id*/);


private:
    void handleMessage( TortoiseItem *item );
    void handleTortoiseItem( TortoiseItem * item );

private:

    RsPeers * m_peers;
};

#endif // P3TORTOISERRS_H
