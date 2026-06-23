#ifndef _DEF_SEATRAC_DRIVER_MESSAGES_SYSALIVE_H_
#define _DEF_SEATRAC_DRIVER_MESSAGES_SYSALIVE_H_

#include <seatrac_driver/SeatracTypes.h>
#include <seatrac_driver/messages/MessageBase.h>

namespace narval { namespace seatrac { namespace messages {

struct SysAlive : public Message<SysAlive>
{
    static const CID_E Identifier = CID_SYS_ALIVE;
    using Message<SysAlive>::operator=;

    uint32_t alivedFor;

}__attribute__((packed));




inline std::ostream& operator<<(std::ostream& os,
                                const narval::seatrac::messages::SysAlive& msg)
{
    static const char* prefix = "\n- ";
    os << "SysAlive :"
       << prefix << "msgId        : " << (uint32_t)msg.msgId
       << prefix << "alivedFor    : " << (uint32_t)msg.alivedFor;
    return os;
}

}; //namespace messages
}; //namespace seatrac
}; //namespace narval

#endif //_DEF_SEATRAC_DRIVER_MESSAGES_SYSALIVE_H_

