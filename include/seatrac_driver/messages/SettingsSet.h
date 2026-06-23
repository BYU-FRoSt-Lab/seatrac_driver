#ifndef _DEF_SEATRAC_DRIVER_MESSAGES_SETTINGS_SET_H_
#define _DEF_SEATRAC_DRIVER_MESSAGES_SETTINGS_SET_H_

#include <seatrac_driver/SeatracTypes.h>
#include <seatrac_driver/messages/MessageBase.h>

namespace narval { namespace seatrac { namespace messages {

struct SettingsSet : public Message<SettingsSet>
{
    using Message<SettingsSet>::operator=;

    static const CID_E Identifier = CID_SETTINGS_SET;
    struct Request : public Message<Request> {
        static const CID_E Identifier = CID_SETTINGS_SET;
        SETTINGS_T settings;
    };
            
    CST_E statusCode;
}__attribute__((packed));




inline std::ostream& operator<<(std::ostream& os,
                                const narval::seatrac::messages::SettingsSet& msg)
{
    os << "SettingsSet : " << msg.statusCode;
    return os;
}

}; //namespace messages
}; //namespace seatrac
}; //namespace narval

#endif //_DEF_SEATRAC_DRIVER_MESSAGES_SETTINGS_SET_H_

