#ifndef _DEF_SEATRAC_DRIVER_MESSAGES_SETTINGS_SAVE_H_
#define _DEF_SEATRAC_DRIVER_MESSAGES_SETTINGS_SAVE_H_

#include <seatrac_driver/SeatracTypes.h>
#include <seatrac_driver/messages/MessageBase.h>

namespace narval { namespace seatrac { namespace messages {

struct SettingsSave : public Message<SettingsSave>
{
    using Message<SettingsSave>::operator=;

    static const CID_E Identifier = CID_SETTINGS_SAVE;
    struct Request : public Message<Request> {
        static const CID_E Identifier = CID_SETTINGS_SAVE;
    };
            
    CST_E statusCode;

}__attribute__((packed));




inline std::ostream& operator<<(std::ostream& os,
                                const narval::seatrac::messages::SettingsSave& msg)
{
    os << "SettingsSave : " << msg.statusCode;
    return os;
}

}; //namespace messages
}; //namespace seatrac
}; //namespace narval

#endif //_DEF_SEATRAC_DRIVER_MESSAGES_SETTINGS_SAVE_H_

