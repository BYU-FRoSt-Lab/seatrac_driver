#ifndef _DEF_SEATRAC_DRIVER_MESSAGES_STATUSCONFIGSET_H_
#define _DEF_SEATRAC_DRIVER_MESSAGES_STATUSCONFIGSET_H_

#include <seatrac_driver/SeatracTypes.h>
#include <seatrac_driver/messages/MessageBase.h>

namespace narval { namespace seatrac { namespace messages {

struct StatusConfigSet : public Message<StatusConfigSet>
{
    using Message<StatusConfigSet>::operator=;

    static const CID_E Identifier = CID_STATUS_CFG_SET;
    struct Request : public Message<Request> {
        static const CID_E Identifier = CID_STATUS_CFG_SET;

        STATUS_BITS_E statusOutput;
        STATUSMODE_E  statusMode;
    };
            
    CST_E statusCode;
}__attribute__((packed));




inline std::ostream& operator<<(std::ostream& os,
                                const narval::seatrac::messages::StatusConfigSet& msg)
{
    static const char* prefix = "\n- ";
    os << "StatusConfigSet : " << msg.statusCode;
    return os;
}

}; //namespace messages
}; //namespace seatrac
}; //namespace narval

#endif //_DEF_SEATRAC_DRIVER_MESSAGES_STATUSCONFIGSET_H_

