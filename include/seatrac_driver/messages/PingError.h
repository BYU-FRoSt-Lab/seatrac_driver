#ifndef _DEF_SEATRAC_DRIVER_MESSAGES_PING_ERROR_H_
#define _DEF_SEATRAC_DRIVER_MESSAGES_PING_ERROR_H_

#include <seatrac_driver/SeatracTypes.h>
#include <seatrac_driver/messages/MessageBase.h>

namespace narval { namespace seatrac { namespace messages {

struct PingError : public Message<PingError>
{
    using Message<PingError>::operator=;
    static const CID_E Identifier = CID_PING_ERROR;
    
    CST_E statusCode;
    BID_E beaconId;

}__attribute__((packed));




inline std::ostream& operator<<(std::ostream& os,
                                const narval::seatrac::messages::PingError& msg)
{
    os << "PingError (" << msg.beaconId << ") : " << msg.statusCode;
    return os;
}

}; //namespace messages
}; //namespace seatrac
}; //namespace narval

#endif //_DEF_SEATRAC_DRIVER_MESSAGES_PING_ERROR_H_





