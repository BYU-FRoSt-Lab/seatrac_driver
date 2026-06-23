#ifndef _DEF_SEATRAC_DRIVER_MESSAGES_XCVR_STATUS_H_
#define _DEF_SEATRAC_DRIVER_MESSAGES_XCVR_STATUS_H_

#include <seatrac_driver/SeatracTypes.h>
#include <seatrac_driver/messages/MessageBase.h>

namespace narval { namespace seatrac { namespace messages {

struct XcvrStatus : public Message<XcvrStatus>
{
    using Message<XcvrStatus>::operator=;

    static const CID_E Identifier = CID_XCVR_STATUS;
    struct Request : public Message<Request> {
        static const CID_E Identifier = CID_XCVR_STATUS;
    };

    CST_E    statusCode;
}__attribute__((packed));




inline std::ostream& operator<<(std::ostream& os,
                                const narval::seatrac::messages::XcvrStatus& msg)
{
    os << "XcvrStatus : " << msg.statusCode;
    return os;
}

}; //namespace messages
}; //namespace seatrac
}; //namespace narval

#endif //_DEF_SEATRAC_DRIVER_MESSAGES_XCVR_STATUS_h_

