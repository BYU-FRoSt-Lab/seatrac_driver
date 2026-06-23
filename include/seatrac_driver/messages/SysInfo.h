#ifndef _DEF_SEATRAC_DRIVER_MESSAGES_SYSINFO_H_
#define _DEF_SEATRAC_DRIVER_MESSAGES_SYSINFO_H_

#include <seatrac_driver/SeatracTypes.h>
#include <seatrac_driver/messages/MessageBase.h>

namespace narval { namespace seatrac { namespace messages {

struct SysInfo : public Message<SysInfo>
{
    static const CID_E Identifier = CID_SYS_INFO;
    using Request = Message;
    using Message<SysInfo>::operator=;

    uint32_t   alivedFor;
    uint8_t    currentApp;
    HARDWARE_T hardware;
    FIRMWARE_T bootFirmware;
    FIRMWARE_T mainFirmware;
    uint8_t    boardRev;

}__attribute__((packed));




inline std::ostream& operator<<(std::ostream& os,
                                const narval::seatrac::messages::SysInfo& msg)
{
    using namespace narval::seatrac;
    static const char* prefix = "\n- ";
    os << "SysInfo :"
       << prefix << "msgId        : " << (uint32_t)msg.msgId
       << prefix << "alivedFor    : " << (uint32_t)msg.alivedFor
       << prefix << "currentApp   : " << (uint32_t)msg.currentApp
       << prefix << "hardware     : " << print_utils::indent(msg.hardware)
       << prefix << "bootFirmware : " << print_utils::indent(msg.bootFirmware)
       << prefix << "mainFirmware : " << print_utils::indent(msg.mainFirmware)
       << prefix << "boardRev     : " << (uint32_t)msg.boardRev;
    return os;
}

}; //namespace messages
}; //namespace seatrac
}; //namespace narval

#endif //_DEF_SEATRAC_DRIVER_MESSAGES_SYSINFO_H_
