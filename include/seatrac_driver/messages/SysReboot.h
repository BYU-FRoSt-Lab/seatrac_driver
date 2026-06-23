#ifndef _DEF_SEATRAC_DRIVER_MESSAGES_SYSREBOOT_H_
#define _DEF_SEATRAC_DRIVER_MESSAGES_SYSREBOOT_H_

#include <seatrac_driver/SeatracTypes.h>
#include <seatrac_driver/messages/MessageBase.h>

namespace narval { namespace seatrac { namespace messages {

struct SysReboot : public Message<SysReboot>
{
    static const CID_E Identifier = CID_SYS_REBOOT;

    struct Request : public Message<Request> {
        static const CID_E Identifier = CID_SYS_REBOOT;
        const uint16_t check;
        Request() : check(0x6A95) {}
    };

    using Message<SysReboot>::operator=;

    CST_E status;

}__attribute__((packed));




inline std::ostream& operator<<(std::ostream& os,
                                const narval::seatrac::messages::SysReboot& msg)
{
    static const char* prefix = "\n- ";
    os << "SysReboot :"
       << prefix << "msgId  : " << (uint32_t)msg.msgId
       << prefix << "status : " << (uint32_t)msg.status;
    return os;
}

}; //namespace messages
}; //namespace seatrac
}; //namespace narval

#endif //_DEF_SEATRAC_DRIVER_MESSAGES_SYSREBOOT_H_


