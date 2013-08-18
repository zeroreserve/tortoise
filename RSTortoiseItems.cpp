#include "RSTortoiseItems.h"
#include "serialiser/rsbaseserial.h"


#include <iostream>
#include <stdexcept>


const uint16_t RS_SERVICE_TYPE_TORTOISE_PLUGIN = 0xDEAD;       // gotta be unique among all plugins
const uint32_t CONFIG_TYPE_TORTOISE_PLUGIN     = 0x0000BEEF;

#define CURRENCY_STRLEN 3
#define HOLLERITH_LEN_SPEC 4

RsItem* TortoiseSerialiser::deserialise(void *data, uint32_t *pktsize)
{
    std::cerr << "Tortoise: deserialise()" << std::endl;

    /* get the type and size */
    uint32_t rstype = getRsItemId(data);

    if ((RS_PKT_VERSION_SERVICE != getRsItemVersion(rstype)) || (RS_SERVICE_TYPE_TORTOISE_PLUGIN != getRsItemService(rstype)))
        return NULL ;

    try{
        switch(getRsItemSubType(rstype))
        {
        case TortoiseItem::TORTOISE_ITEM:
            return new TortoiseItem(data, *pktsize);
        default:
            return NULL;
        }
    }
    catch(std::exception& e){
        std::cerr << "RsTortoiseSerialiser: deserialization error: " << e.what() << std::endl;
        return NULL;
    }
}





std::ostream& TortoiseItem::print(std::ostream &out, uint16_t indent)
{
    printRsItemBase(out, "RsTortoiseItem", indent);
    uint16_t int_Indent = indent + 2;
    printIndent(out, int_Indent);

    out << "Message  : " << m_msg << std::endl;

    printIndent(out, int_Indent);
    printRsItemEnd(out, "RsTortoiseItem", indent);
    return out;
}

uint32_t TortoiseItem::serial_size()
{
    uint32_t s = 8; /* header */
    s += m_msg.length() + HOLLERITH_LEN_SPEC; // strings need the length of the string + 32 bit to specify the length (Hollerith format)

    return s;
}

bool TortoiseItem::serialize(void *data, uint32_t& pktsize)
{
    uint32_t tlvsize = serial_size() ;

    if (pktsize < tlvsize)
        return false; /* not enough space */

    pktsize = tlvsize;

    bool ok = true;

    ok &= setRsItemHeader(data, tlvsize, PacketId(), tlvsize);

    uint32_t offset = 8;  // skip header

    ok &= setRawString( data, tlvsize, &offset, m_msg );

    if (offset != tlvsize){
        ok = false;
        std::cerr << "RsTortoiseItem::serialise() Size Error! " << std::endl;
    }

    return ok;
}

TortoiseItem::TortoiseItem(void *data, uint32_t pktsize)
        : RsTurtleGenericTunnelItem( TORTOISE_ITEM )
{   
    /* get the type and size */
    uint32_t rstype = getRsItemId(data);
    uint32_t rssize = getRsItemSize(data);

    uint32_t offset = 8;


    if ((RS_PKT_VERSION_SERVICE != getRsItemVersion(rstype)) || (RS_SERVICE_TYPE_TORTOISE_PLUGIN != getRsItemService(rstype)) || (TORTOISE_ITEM != getRsItemSubType(rstype)))
        throw std::runtime_error("Wrong packet type!") ;

    if (pktsize < rssize)    /* check size */
        throw std::runtime_error("Not enough size!") ;

    bool ok = true;


    ok &= getRawString(data, rssize, &offset, m_msg );

    if (offset != rssize || !ok )
        throw std::runtime_error("Deserialisation error!") ;
}


