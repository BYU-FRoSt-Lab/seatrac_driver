#ifndef _DEF_SEATRAC_DRIVER_MESSAGES_SETTINGS_GET_H_
#define _DEF_SEATRAC_DRIVER_MESSAGES_SETTINGS_GET_H_

#include <seatrac_driver/SeatracTypes.h>
#include <seatrac_driver/messages/MessageBase.h>

namespace narval { namespace seatrac { namespace messages {

struct SettingsGet : public Message<SettingsGet>
{
    using Message<SettingsGet>::operator=;

    static const CID_E Identifier = CID_SETTINGS_GET;
    struct Request : public Message<Request> {
        static const CID_E Identifier = CID_SETTINGS_GET;
    };
            
    SETTINGS_T settings;

}__attribute__((packed));




inline std::ostream& operator<<(std::ostream& os,
                                const narval::seatrac::messages::SettingsGet& msg)
{
    using namespace narval::seatrac;
    static const char* prefix = "\n- ";
    os << "SettingsGet :"
       << prefix << "settings : " << print_utils::indent(msg.settings);
    return os;
}

}; //namespace messages
}; //namespace seatrac
}; //namespace narval

#endif //_DEF_SEATRAC_DRIVER_MESSAGES_SETTINGS_GET_H_

