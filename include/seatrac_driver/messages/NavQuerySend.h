#ifndef _DEF_SEATRAC_DRIVER_MESSAGES_NAV_QUERY_SEND_H_
#define _DEF_SEATRAC_DRIVER_MESSAGES_NAV_QUERY_SEND_H_

#include <seatrac_driver/SeatracTypes.h>
#include <seatrac_driver/messages/MessageBase.h>

namespace narval { namespace seatrac { namespace messages {

struct NavQuerySend : public Message<NavQuerySend> {

    using Message<NavQuerySend>::operator=;

    static const CID_E Identifier = CID_NAV_QUERY_SEND;
    struct Request : public Message<Request> {
        static const CID_E Identifier = CID_NAV_QUERY_SEND;
        BID_E destId;
        NAV_QUERY_E queryFlags;
        uint8_t packetLen;
        uint8_t packetData[29]; //Nav packets only go up to 29 characters
    }__attribute__((packed));

    CST_E status;
    BID_E beaconId;

}__attribute__((packed));



inline std::ostream& operator<<(std::ostream& os,
                                const narval::seatrac::messages::NavQuerySend::Request& msg)
{
    os << "NavQuerySend Request: " 
       << "\n- target:\t"        << msg.destId
       << "\n- query flags:\t"   << msg.queryFlags
       << "\n- packet length:\t" << (int)msg.packetLen
       << "\nPacket Data:\n- (char):\t";
    for(uint8_t i=0; i<msg.packetLen; i++) {
        os << msg.packetData[i];
    }
    os << "\n- (hex):\t";
    for(uint8_t i=0; i<msg.packetLen; i++) {
        printf("%02X ", msg.packetData[i]);
    }
    os << "\n- (int):\t";
    for(uint8_t i=0; i<msg.packetLen; i++) {
        printf("%d ", msg.packetData[i]);
    }
    return os;
}

inline std::ostream& operator<<(std::ostream& os,
                                const narval::seatrac::messages::NavQuerySend& msg)
{
    os << "NavQuerySend Response: " << std::endl
       << "- status: " << msg.status << std::endl
       << "- dest Id: " << msg.beaconId << std::endl;
    return os;
}


}; //namespace messages
}; //namespace seatrac
}; //namespace narval

#endif //_DEF_SEATRAC_DRIVER_MESSAGES_NAV_QUERY_SEND_H_