

#ifndef P3TORTOISERRS_H
#define P3TORTOISERRS_H


#include "RSTortoiseItems.h"

#include "retroshare/rspeers.h"
#include "plugins/rspqiservice.h"
#include "pqi/pqimonitor.h"
#include "turtle/turtleclientservice.h"




class RsPluginHandler;
class RsPeers;

class p3TortoiseRS : public RsPQIService,   // the service interface calls tick()
                    public pqiMonitor,     // the monitor tells us when friends changed their status
                    public RsTurtleClientService
{
public:
    p3TortoiseRS(RsPluginHandler *pgHandler, RsPeers* peers);

    virtual int tick();
    virtual void statusChange(const std::list<pqipeer> &plist);

    virtual void addVirtualPeer(const TurtleFileHash& hash,const TurtleVirtualPeerId & virtual_peer_id,RsTurtleGenericTunnelItem::Direction dir);
    virtual void removeVirtualPeer(const TurtleFileHash& hash,const TurtleVirtualPeerId & virtual_peer_id);
    virtual void receiveTurtleData(RsTurtleGenericTunnelItem */*item*/,const std::string& /*hash*/,const std::string& /*virtual_peer_id*/,RsTurtleGenericTunnelItem::Direction /*direction*/);
    virtual bool handleTunnelRequest(const std::string& /*hash*/,const std::string& /*peer_id*/);


private:
    void handleMessage( TortoiseItem *item );
    void handleTortoiseItem( TortoiseItem * item );

private:

    RsPeers * m_peers;
};

#endif // P3TORTOISERRS_H
