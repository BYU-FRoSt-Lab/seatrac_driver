#ifndef _DEF_SEATRAC_DRIVER_MESSAGES_SETTINGS_RESET_H_
#define _DEF_SEATRAC_DRIVER_MESSAGES_SETTINGS_RESET_H_

#include <seatrac_driver/SeatracTypes.h>
#include <seatrac_driver/messages/MessageBase.h>

namespace narval { namespace seatrac { namespace messages {

struct SettingsReset : public Message<SettingsReset>
{
    using Message<SettingsReset>::operator=;

    static const CID_E Identifier = CID_SETTINGS_RESET;
    struct Request : public Message<Request> {
        static const CID_E Identifier = CID_SETTINGS_RESET;
    };
            
    CST_E statusCode;

}__attribute__((packed));




inline std::ostream& operator<<(std::ostream& os,
                                const narval::seatrac::messages::SettingsReset& msg)
{
    os << "SettingsReset : " << msg.statusCode;
    return os;
}

}; //namespace messages
}; //namespace seatrac
}; //namespace narval

#endif //_DEF_SEATRAC_DRIVER_MESSAGES_SETTINGS_RESET_H_

