#ifndef _DEF_SEATRAC_DRIVER_MESSAGES_ECHO_ERROR_H_
#define _DEF_SEATRAC_DRIVER_MESSAGES_ECHO_ERROR_H_

#include <seatrac_driver/SeatracTypes.h>
#include <seatrac_driver/messages/MessageBase.h>

namespace narval { namespace seatrac { namespace messages {

struct EchoError : public Message<EchoError> {
    using Message<EchoError>::operator=;
    static const CID_E Identifier = CID_DAT_ERROR;
    CST_E status;
    BID_E beaconId;
}__attribute__((packed));



inline std::ostream& operator<<(std::ostream& os,
                                const narval::seatrac::messages::EchoError& msg)
{
    os << "EchoError: " 
       << "- beaconId: " << msg.beaconId
       << "- status (error type): " << msg.status;
    return os;
}

}; //namespace messages
}; //namespace seatrac
}; //namespace narval

#endif //_DEF_SEATRAC_DRIVER_MESSAGES_ECHO_ERROR_H_