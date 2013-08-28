#ifndef RSTORTOISEITEMS_H
#define RSTORTOISEITEMS_H

#include "turtle/rsturtleitem.h"
#include <string>



const uint8_t QOS_PRIORITY_RS_TORTOISE = 3;


class TortoiseItem: public RsTurtleGenericTunnelItem
{
public:
    TortoiseItem( const std::string & msg )
        : RsTurtleGenericTunnelItem( TORTOISE_ITEM )
    {
        setPriorityLevel(QOS_PRIORITY_RS_TORTOISE);
        m_msg = msg;
    }
    TortoiseItem(void *data, uint32_t pktsize);

    enum RS_PKT_SUBTYPE {
        TORTOISE_ITEM = 0xAA
        // add any number of item types here
    };

    virtual ~TortoiseItem() {};
    virtual void clear() {};
    virtual std::ostream& print(std::ostream &out, uint16_t indent = 0);
    virtual bool shouldStampTunnel() const { return true; }

    virtual bool serialize(void *data,uint32_t& size);
    virtual uint32_t serial_size();

    const std::string & getMessage(){ return m_msg; }
private:
    std::string m_msg;
};



#endif // RSTORTOISEITEMS_H
