#ifndef _DEF_SEATRAC_DRIVER_MESSAGES_PING_SEND_H_
#define _DEF_SEATRAC_DRIVER_MESSAGES_PING_SEND_H_

#include <seatrac_driver/SeatracTypes.h>
#include <seatrac_driver/messages/MessageBase.h>

namespace narval { namespace seatrac { namespace messages {

struct PingSend : public Message<PingSend>
{
    using Message<PingSend>::operator=;

    static const CID_E Identifier = CID_PING_SEND;
    struct Request : public Message<Request> {
        static const CID_E Identifier = CID_PING_SEND;
        BID_E      target;
        AMSGTYPE_E pingType;
    };
            
    CST_E statusCode;
    BID_E target;

}__attribute__((packed));




inline std::ostream& operator<<(std::ostream& os,
                                const narval::seatrac::messages::PingSend& msg)
{
    os << "PingSend : " << msg.statusCode << ", target : " << msg.target;
    return os;
}

}; //namespace messages
}; //namespace seatrac
}; //namespace narval

#endif //_DEF_SEATRAC_DRIVER_MESSAGES_PING_SEND_H_



