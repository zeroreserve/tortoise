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
#include "RSTortoiseItems.h"

#include "pqi/p3linkmgr.h"
#include "retroshare/rsturtle.h"

#include <iostream>


p3TortoiseRS::p3TortoiseRS(RsPluginHandler *pgHandler, RsPeers* peers ) :
        m_peers(peers)
{
    m_hash = "";
    m_Turtle = static_cast< p3turtle* >( rsTurtle );
    m_Turtle->registerTunnelService(this);
}


void p3TortoiseRS::addMonitor(const std::string & hash )
{
    std::cerr << "Tortoise: Monitoring tunnels for hash " << hash << std::endl;
    m_Turtle->monitorTunnels( hash, this ) ;
}

void p3TortoiseRS::setListener(const std::string & hash )
{
    std::cerr << "Tortoise: Listening to hash " << hash << std::endl;
    m_hash = hash;
}

void p3TortoiseRS::sendMessage(const std::string & message )
{
    for( std::set< std::string>::const_iterator it = m_vPeerList.begin(); it != m_vPeerList.end(); it++ ){
        m_Turtle->sendTurtleData( *it, new TortoiseItem( message ) );
    }
}

//////////////


void p3TortoiseRS::handleTortoiseItem( TortoiseItem * item )
{
    std::cerr << "Tortoise: " << item->PeerId() << " said: " << item->getMessage() << std::endl;
}


// implemented from the Turtle interface
// do not use any of these functions as a convenient place to call turtle functions
// like sending a message. This will result in a deadlock


void p3TortoiseRS::addVirtualPeer( const TurtleFileHash& hash,const TurtleVirtualPeerId & virtual_peer_id,RsTurtleGenericTunnelItem::Direction dir )
{
    std::cerr << "Tortoise:  Adding virtual peer " << virtual_peer_id << " for hash " << hash << "  --  Direction " << dir << std::endl;
    m_vPeerList.insert( virtual_peer_id );
}



void p3TortoiseRS::removeVirtualPeer( const TurtleFileHash& hash,const TurtleVirtualPeerId & virtual_peer_id )
{
    std::cerr << "Tortoise:  Removing virtual peer " << virtual_peer_id << " for hash " << hash << std::endl;
    m_vPeerList.erase( virtual_peer_id );
}


void p3TortoiseRS::receiveTurtleData( RsTurtleGenericTunnelItem * item,const std::string& hash,const std::string & virtual_peer_id,RsTurtleGenericTunnelItem::Direction direction )
{
    std::cerr << "Tortoise:  Received Data from Turtle router" << std::endl;
    item->print( std::cerr );
}

bool p3TortoiseRS::handleTunnelRequest(const std::string & hash, const std::string & peer_id)
{
    if( hash == m_hash ){
        std::cerr << "Tortoise: Handling tunnel request: hash: " << hash << " -- ID: " << peer_id << std::endl;
        return true;
    }
    else{
        std::cerr << "Tortoise: NOT handling tunnel request: hash: " << hash << " -- ID: " << peer_id << std::endl;
        return false;
    }
}


RsTurtleGenericTunnelItem * p3TortoiseRS::deserialiseItem(void * data, uint32_t pktsize) const
{
    std::cerr << "Tortoise: Attempting  to deserialise Item" << std::endl;

    /* get the type and size */
    uint32_t rstype = getRsItemId(data);

    try{
        switch(getRsItemSubType(rstype))
        {
        case TortoiseItem::TORTOISE_ITEM:
        {
             TortoiseItem * tortoiseItem = new TortoiseItem(data, pktsize);
             tortoiseItem->print( std::cerr );
             return tortoiseItem;
        }
        default:
            return NULL;
        }
    }
    catch(std::exception& e){
        std::cerr << "RsTortoiseSerialiser: deserialization error: " << e.what() << std::endl;
        return NULL;
    }
}
