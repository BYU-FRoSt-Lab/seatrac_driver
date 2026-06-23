#ifndef _DEF_SEATRAC_DRIVER_MESSAGES_PING_REQ_H_
#define _DEF_SEATRAC_DRIVER_MESSAGES_PING_REQ_H_

#include <seatrac_driver/SeatracTypes.h>
#include <seatrac_driver/messages/MessageBase.h>

namespace narval { namespace seatrac { namespace messages {

struct PingReq : public Message<PingReq>
{
    static const CID_E Identifier = CID_PING_REQ;
    ACOFIX_T acoFix;

    PingReq& operator=(const std::vector<uint8_t>& other)
    {
        if(other[0] != this->msgId) {
            throw std::runtime_error("Wrong message for decoding.");
        }
        acoFix.assign(other.size() - 1, other.data() + 1);
        return *this;
    }
}__attribute__((packed));




inline std::ostream& operator<<(std::ostream& os,
                                const narval::seatrac::messages::PingReq& msg)
{
    const char* prefix = "\n- ";
    //os << "PingReq : " << msg.acoFix;
    os << "PingReq";
    return os;
}

}; //namespace messages
}; //namespace seatrac
}; //namespace narval

#endif //_DEF_SEATRAC_DRIVER_MESSAGES_PING_REQ_H_





