#ifndef _DEF_SEATRAC_DRIVER_MESSAGES_ECHO_RESP_H_
#define _DEF_SEATRAC_DRIVER_MESSAGES_ECHO_RESP_H_

#include <seatrac_driver/SeatracTypes.h>
#include <seatrac_driver/messages/MessageBase.h>

namespace narval { namespace seatrac { namespace messages {

struct EchoResp : public Message<EchoResp>
{
    static const CID_E Identifier = CID_ECHO_RESP;
    ACOFIX_T acoFix;
    uint8_t packetLen;  // The number of bytes sent in the acoustic
                        // packet. Valid values are from 0 to 31.
                        // A value of 0 indicate no data is present.
    uint8_t packetData[30]; // The array of data received in the acoustic packet

    EchoResp& operator=(const std::vector<uint8_t>& other)
    {
        if(other[0] != this->msgId) {
            throw std::runtime_error("Wrong message for decoding.");
        }
        uint8_t acoFixSize = acoFix.assign(other.size() - 1, other.data() + 1);
        const uint8_t* p   = other.data() + 1 + acoFixSize; //pointer to start of rest of message
        this->packetLen = p[0];
        std::memcpy(this->packetData, p+1, this->packetLen);

        return *this;
    }

}__attribute__((packed));




inline std::ostream& operator<<(std::ostream& os,
                                const narval::seatrac::messages::EchoResp& msg)
{
    os << "\nEchoResp: \n" 
       << msg.acoFix
       << "\nPacket Length: " << (int)msg.packetLen
       << "\nPacket Data:\n- (char):\t";
    for(uint8_t i=0; i<msg.packetLen; i++) {
        os << msg.packetData[i];
    }
    os << "\n- (hex):\t";
    for(uint8_t i=0; i<msg.packetLen; i++) {
        printf("%02X ", msg.packetData[i]);
    }
    os << "\n- (int):\t";
    for(uint8_t i=0; i<msg.packetLen; i++) {
        printf("%d ", msg.packetData[i]);
    }
    return os;
}

}; //namespace messages
}; //namespace seatrac
}; //namespace narval

#endif //_DEF_SEATRAC_DRIVER_MESSAGES_ECHO_RESP_H_

