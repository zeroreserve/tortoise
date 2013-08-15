/*
    This file is part of the Tortoise Plugin for Retroshare.

    Tortoise is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Tortoise is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with Tortoise.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "p3TortoiseRS.h"

#include "pqi/p3linkmgr.h"
#include "retroshare/rsturtle.h"

#include <iostream>

// after getting data from 3 peers, we believe we're complete
static const int INIT_THRESHOLD = 3;

p3TortoiseRS::p3TortoiseRS(RsPluginHandler *pgHandler, RsPeers* peers ) :
        RsPQIService( RS_SERVICE_TYPE_TORTOISE_PLUGIN, CONFIG_TYPE_TORTOISE_PLUGIN, 0, pgHandler ),

        m_peers(peers)
{
    addSerialType(new TortoiseSerialiser());
    pgHandler->getLinkMgr()->addMonitor( this );
    rsTurtle->registerTunnelService(this);
    rsTurtle->monitorTunnels( "Foobar", this ) ;
}


void p3TortoiseRS::statusChange(const std::list< pqipeer > &plist)
{
    std::cerr << "Tortoise: Status changed:" << std::endl;

    for (std::list< pqipeer >::const_iterator peerIt = plist.begin(); peerIt != plist.end(); peerIt++ ){
        if( RS_PEER_CONNECTED & (*peerIt).actions ){
            TortoiseItem * item = new TortoiseItem();
            item->PeerId( (*peerIt).id );
            sendItem( item );
        }
    }
}


int p3TortoiseRS::tick()
{
    RsItem *item = NULL;
    while(NULL != (item = recvItem())){
        switch( item->PacketSubType() )
        {
        case TortoiseItem::TORTOISE_ITEM:
            handleTortoiseItem( dynamic_cast<TortoiseItem*>( item ) );
            break;
        default:
            std::cerr << "Tortoise: Received Item unknown" << std::endl;
        }
        delete item;
    }
    return 0;
}


void p3TortoiseRS::handleTortoiseItem( TortoiseItem * item )
{
    std::cerr << item->PeerId() << " said: " << item->getMessage() << std::endl;
}



void p3TortoiseRS::addVirtualPeer(const TurtleFileHash& hash,const TurtleVirtualPeerId& virtual_peer_id,RsTurtleGenericTunnelItem::Direction dir)
{
    std::cerr << "Tortoise:  Adding virtual peer " << std::endl;
}



void p3TortoiseRS::removeVirtualPeer(const TurtleFileHash& hash,const TurtleVirtualPeerId& virtual_peer_id)
{
    std::cerr << "Tortoise:  Removing virtual peer " << std::endl;
}

void p3TortoiseRS::receiveTurtleData(RsTurtleGenericTunnelItem */*item*/,const std::string& /*hash*/,const std::string& /*virtual_peer_id*/,RsTurtleGenericTunnelItem::Direction /*direction*/)
{
    std::cerr << "Tortoise:  Received Data from Turtle router" << std::endl;
}

bool p3TortoiseRS::handleTunnelRequest(const std::string & hash, const std::string & peer_id)
{
    std::cerr << "Tortoise: handling tunnel request hash: " << hash << " ID: " << peer_id << std::endl;
    return false;
}
