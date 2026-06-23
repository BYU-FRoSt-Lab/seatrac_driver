#ifndef _DEF_SEATRAC_DRIVER_MESSAGES_XCVR_ANALYSE_H_
#define _DEF_SEATRAC_DRIVER_MESSAGES_XCVR_ANALYSE_H_

#include <seatrac_driver/SeatracTypes.h>
#include <seatrac_driver/messages/MessageBase.h>

namespace narval { namespace seatrac { namespace messages {

struct XcvrAnalyse : public Message<XcvrAnalyse>
{
    using Message<XcvrAnalyse>::operator=;

    static const CID_E Identifier = CID_XCVR_ANALYSE;
    struct Request : public Message<Request> {
        static const CID_E Identifier = CID_XCVR_ANALYSE;
    };

    CST_E    statusCode;
    int16_t  adcMean;
    uint16_t adcPkPk;
    uint32_t adcRMS;
    int16_t  rxLevelPkPk;
    int16_t  rxLevelRMS;
                
}__attribute__((packed));




inline std::ostream& operator<<(std::ostream& os,
                                const narval::seatrac::messages::XcvrAnalyse& msg)
{
    using namespace narval::seatrac;
    static const char* prefix = "\n- ";
    os << "XcvrAnalyse :"
       << prefix << "statusCode  : " << msg.statusCode
       << prefix << "adcMean     : " << msg.adcMean
       << prefix << "adcPkPk     : " << msg.adcPkPk
       << prefix << "adcRMS      : " << msg.adcRMS
       << prefix << "rxLevelPkPk : " << msg.rxLevelPkPk
       << prefix << "rxLevelRMS  : " << msg.rxLevelRMS;
    return os;
}

}; //namespace messages
}; //namespace seatrac
}; //namespace narval

#endif //_DEF_SEATRAC_DRIVER_MESSAGES_XCVR_ANALYSE_h_

