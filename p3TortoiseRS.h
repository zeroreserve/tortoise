#ifndef P3TORTOISERRS_H
#define P3TORTOISERRS_H


#include "RSTortoiseItems.h"

#include "retroshare/rspeers.h"
#include "turtle/turtleclientservice.h"
#include "turtle/p3turtle.h"

#include <set>
#include <string>


class RsPluginHandler;
class RsPeers;

class p3TortoiseRS : public RsTurtleClientService  // the interface of the turtle router
{
public:
    p3TortoiseRS(RsPluginHandler *, RsPeers*);

    // turtle functions
    virtual void addVirtualPeer(const TurtleFileHash& hash,const TurtleVirtualPeerId & virtual_peer_id,RsTurtleGenericTunnelItem::Direction dir);
    virtual void removeVirtualPeer(const TurtleFileHash& hash,const TurtleVirtualPeerId & virtual_peer_id);
    virtual void receiveTurtleData(RsTurtleGenericTunnelItem * item ,const std::string& hash,const std::string& virtual_peer_id,RsTurtleGenericTunnelItem::Direction direction);
    virtual bool handleTunnelRequest(const std::string & hash,const std::string & peer_id);
    virtual RsTurtleGenericTunnelItem *deserialiseItem(void * data, uint32_t pktsize) const;

    // calls from the GUI
    void addMonitor( const std::string & hash );
    void setListener(const std::string & hash );
    void sendMessage(const std::string & message );


private:
    /** the hash the server is watchin out for */
    std::string m_hash;
    /** list of current virtual peers */
    std::set< std::string > m_vPeerList;

    p3turtle * m_Turtle;
};

#endif // P3TORTOISERRS_H
