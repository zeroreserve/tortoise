#ifndef P3TORTOISERRS_H
#define P3TORTOISERRS_H


#include "RSTortoiseItems.h"

#include "retroshare/rspeers.h"
#include "plugins/rspqiservice.h"
#include "pqi/pqimonitor.h"
#include "turtle/turtleclientservice.h"
#include "turtle/p3turtle.h"


class RsPluginHandler;
class RsPeers;

class p3TortoiseRS : public RsPQIService,          // the service interface calls tick()
                     public RsTurtleClientService  // the interface of the turtle router
{
public:
    p3TortoiseRS(RsPluginHandler *pgHandler, RsPeers* peers);

    virtual int tick();

    // turtle functions
    virtual void addVirtualPeer(const TurtleFileHash& hash,const TurtleVirtualPeerId & virtual_peer_id,RsTurtleGenericTunnelItem::Direction dir);
    virtual void removeVirtualPeer(const TurtleFileHash& hash,const TurtleVirtualPeerId & virtual_peer_id);
    virtual void receiveTurtleData(RsTurtleGenericTunnelItem * item ,const std::string& hash,const std::string& virtual_peer_id,RsTurtleGenericTunnelItem::Direction direction);
    virtual bool handleTunnelRequest(const std::string & hash,const std::string & peer_id);

    void addMonitor( const std::string & hash );
    void setListener(const std::string & hash );

private:
    void handleMessage( TortoiseItem *item );
    void handleTortoiseItem( TortoiseItem * item );

private:
    /** the hash the server is watchin out for */
    std::string m_hash;

    RsPeers * m_peers;
    p3turtle * m_Turtle;
};

#endif // P3TORTOISERRS_H
