#ifndef _DEF_SEATRAC_DRIVER_MESSAGES_PING_RESP_H_
#define _DEF_SEATRAC_DRIVER_MESSAGES_PING_RESP_H_

#include <seatrac_driver/SeatracTypes.h>
#include <seatrac_driver/messages/MessageBase.h>

namespace narval { namespace seatrac { namespace messages {

struct PingResp : public Message<PingResp>
{
    static const CID_E Identifier = CID_PING_RESP;
    ACOFIX_T acoFix;

    PingResp& operator=(const std::vector<uint8_t>& other)
    {
        if(other[0] != this->msgId) {
            throw std::runtime_error("Wrong message for decoding.");
        }
        acoFix.assign(other.size() - 1, other.data() + 1);
        return *this;
    }
}__attribute__((packed));




inline std::ostream& operator<<(std::ostream& os,
                                const narval::seatrac::messages::PingResp& msg)
{
    os << "PingResp : " << msg.acoFix;
    return os;
}

}; //namespace messages
}; //namespace seatrac
}; //namespace narval

#endif //_DEF_SEATRAC_DRIVER_MESSAGES_PING_RESP_H_





