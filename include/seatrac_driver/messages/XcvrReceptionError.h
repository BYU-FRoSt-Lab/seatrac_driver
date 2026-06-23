#ifndef _DEF_SEATRAC_DRIVER_MESSAGES_XCVR_RECEPTION_ERROR_H_
#define _DEF_SEATRAC_DRIVER_MESSAGES_XCVR_RECEPTION_ERROR_H_

#include <seatrac_driver/SeatracTypes.h>
#include <seatrac_driver/messages/MessageBase.h>

namespace narval { namespace seatrac { namespace messages {

struct XcvrReceptionError : public Message<XcvrReceptionError>
{
    static const CID_E Identifier = CID_XCVR_RX_ERR;
    XcvrReceptionError& operator=(const std::vector<uint8_t>& data)
    {
        if(data[0] != this->msgId) {
            throw std::runtime_error("Wrong message for decoding.");
        }
        statusCode = (CST_E)data[1];
        acousticFix.assign(data.size() - 2, data.data() + 2);
        return *this;
    }

    CST_E    statusCode;
    ACOFIX_T acousticFix;
                
}__attribute__((packed));




inline std::ostream& operator<<(std::ostream& os,
                                const narval::seatrac::messages::XcvrReceptionError& msg)
{
    using namespace narval::seatrac;
    static const char* prefix = "\n- ";
    os << "XcvrReceptionError : " << msg.statusCode
       << prefix << "acousticFix : " << print_utils::indent(msg.acousticFix);
    return os;
}

}; //namespace messages
}; //namespace seatrac
}; //namespace narval

#endif //_DEF_SEATRAC_DRIVER_MESSAGES_XCVR_RECEPTION_ERROR_h_

