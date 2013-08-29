#include "RSTortoiseItems.h"
#include "serialiser/rsbaseserial.h"


#include <iostream>
#include <stdexcept>


#define HOLLERITH_LEN_SPEC 4



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
    std::cerr << "Tortoise: serialise() - Size = " << tlvsize << std::endl;

    if (pktsize < tlvsize)
        return false; /* not enough space */

    pktsize = tlvsize;

    bool ok = true;

    ok &= setRsItemHeader(data, tlvsize, PacketId(), tlvsize);

    uint32_t offset = 8;  // skip header

    // one of a set of utility functions to help with serialization
    ok &= setRawString( data, tlvsize, &offset, m_msg );

    if (offset != tlvsize){  // that should never happen
        ok = false;
        std::cerr << "RsTortoiseItem::serialise() Size Error! " << std::endl;
    }

    return ok;
}

TortoiseItem::TortoiseItem(void *data, uint32_t pktsize)
        : RsTurtleGenericTunnelItem( TORTOISE_ITEM )
{   
    std::cerr << "Tortoise: constructing item - size = " << pktsize << std::endl;
    /* get the type and size */
    uint32_t rstype = getRsItemId(data);
    uint32_t rssize = getRsItemSize(data);

    uint32_t offset = 8;

    if (pktsize < rssize)    /* check size */
        throw std::runtime_error("Not enough size!") ;

    bool ok = true;

    // must correspond to the setRawString() above
    ok &= getRawString(data, rssize, &offset, m_msg );

    if (offset != rssize || !ok )
        throw std::runtime_error("Deserialisation error!") ;
}


