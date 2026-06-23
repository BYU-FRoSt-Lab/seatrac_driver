#ifndef _DEF_SEATRAC_DRIVER_MESSAGES_SETTINGS_LOAD_H_
#define _DEF_SEATRAC_DRIVER_MESSAGES_SETTINGS_LOAD_H_

#include <seatrac_driver/SeatracTypes.h>
#include <seatrac_driver/messages/MessageBase.h>

namespace narval { namespace seatrac { namespace messages {

struct SettingsLoad : public Message<SettingsLoad>
{
    using Message<SettingsLoad>::operator=;

    static const CID_E Identifier = CID_SETTINGS_LOAD;
    struct Request : public Message<Request> {
        static const CID_E Identifier = CID_SETTINGS_LOAD;
    };
            
    CST_E statusCode;

}__attribute__((packed));




inline std::ostream& operator<<(std::ostream& os,
                                const narval::seatrac::messages::SettingsLoad& msg)
{
    os << "SettingsLoad : " << msg.statusCode;
    return os;
}

}; //namespace messages
}; //namespace seatrac
}; //namespace narval

#endif //_DEF_SEATRAC_DRIVER_MESSAGES_SETTINGS_LOAD_H_

