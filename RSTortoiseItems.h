#ifndef RSTORTOISEITEMS_H
#define RSTORTOISEITEMS_H

#include "serialiser/rsserial.h"
#include "turtle/rsturtleitem.h"
#include <string>



const uint8_t QOS_PRIORITY_RS_TORTOISE = 3;
extern const uint16_t RS_SERVICE_TYPE_TORTOISE_PLUGIN;
extern const uint32_t CONFIG_TYPE_TORTOISE_PLUGIN;


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
        TORTOISE_ITEM = 0x01
        // add any number of item types here
    };

    virtual ~TortoiseItem() {};
    virtual void clear() {};
    virtual std::ostream& print(std::ostream &out, uint16_t indent = 0);
    virtual bool shouldStampTunnel() const { return false; }

    virtual bool serialize(void *data,uint32_t& size);
    virtual uint32_t serial_size();

    const std::string & getMessage(){ return m_msg; }
private:
    std::string m_msg;
};


class TortoiseSerialiser: public RsSerialType
{
public:
    TortoiseSerialiser()
        :RsSerialType(RS_PKT_VERSION_SERVICE, RS_SERVICE_TYPE_TORTOISE_PLUGIN)
    {
    }
    virtual ~TortoiseSerialiser() {}

    virtual uint32_t 	size (RsItem *item)
    {
        return dynamic_cast<TortoiseItem *>(item)->serial_size() ;
    }

    virtual	bool serialise  (RsItem *item, void *data, uint32_t *size)
    {
        return dynamic_cast<TortoiseItem *>(item)->serialize(data,*size) ;
    }
    virtual	RsItem *deserialise(void *data, uint32_t *size);
};

#endif // RSTORTOISEITEMS_H
