#ifndef _DEF_SEATRAC_DRIVER_MESSAGES_STATUSCONFIGGET_H_
#define _DEF_SEATRAC_DRIVER_MESSAGES_STATUSCONFIGGET_H_

#include <seatrac_driver/SeatracTypes.h>
#include <seatrac_driver/messages/MessageBase.h>

namespace narval { namespace seatrac { namespace messages {

struct StatusConfigGet : public Message<StatusConfigGet>
{
    using Message<StatusConfigGet>::operator=;

    static const CID_E Identifier = CID_STATUS_CFG_GET;
    struct Request : public Message<Request> {
        static const CID_E Identifier = CID_STATUS_CFG_GET;
    };
            
    STATUS_BITS_E statusOutput;
    STATUSMODE_E  statusMode;

}__attribute__((packed));




inline std::ostream& operator<<(std::ostream& os,
                                const narval::seatrac::messages::StatusConfigGet& msg)
{
    using namespace narval::seatrac;
    static const char* prefix = "\n- ";
    os << "StatusConfigGet :"
       << prefix << "statusOutput : " << print_utils::indent(msg.statusOutput)
       << prefix << "statusMode   : " << msg.statusMode;
    return os;
}

}; //namespace messages
}; //namespace seatrac
}; //namespace narval

#endif //_DEF_SEATRAC_DRIVER_MESSAGES_STATUSCONFIGGET_H_

