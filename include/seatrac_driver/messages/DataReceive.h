#ifndef _DEF_SEATRAC_DRIVER_MESSAGES_DATA_RECEIVE_H_
#define _DEF_SEATRAC_DRIVER_MESSAGES_DATA_RECEIVE_H_

#include <seatrac_driver/SeatracTypes.h>
#include <seatrac_driver/messages/MessageBase.h>

namespace narval { namespace seatrac { namespace messages {

struct DataReceive : public Message<DataReceive>
{
    static const CID_E Identifier = CID_DAT_RECEIVE;
    ACOFIX_T acoFix;
    bool ackFlag;   // Flag is true if this message has been generated as a
                    // response to a CID_DAT_SEND command which
                    // requested an ACK – in which case, remotely queued
                    // data may have also been transmitted back and in
                    // included in this message.
    uint8_t packetLen;  // The number of bytes sent in the DAT acoustic
                        // packet. Valid values are from 0 to 31.
                        // A value of 0 indicate no data is present.
    uint8_t packetData[30]; // The array of data received in the DAT acoustic packet

    bool localFlag; // True if an acoustic DAT message has been received that is
                    // address for this local beacon (or a broadcast to all).
                    // This flag is the same as the Boolean result of logical test
                    // “ACO_FIX.DEST_ID = LOCAL_BEACON_ID or BEACON_ALL”

    DataReceive& operator=(const std::vector<uint8_t>& other)
    {
        if(other[0] != this->msgId) {
            throw std::runtime_error("Wrong message for decoding.");
        }
        uint8_t acoFixSize = acoFix.assign(other.size() - 1, other.data() + 1);

        const uint8_t* p   = other.data() + 1 + acoFixSize; //pointer to start of rest of message
        this->ackFlag = p[0];
        this->packetLen = p[1];
        std::memcpy(this->packetData, p+2, this->packetLen);
        this->localFlag = p[2+this->packetLen];

        return *this;
    }

}__attribute__((packed));




inline std::ostream& operator<<(std::ostream& os,
                                const narval::seatrac::messages::DataReceive& msg)
{
    os << "\nDataReceive: \n" 
       << msg.acoFix
       << "\nRequires Acknowledgement: " << (msg.ackFlag ? "True":"False")
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
    os << "\nLocal Flag: " << (msg.localFlag ? "True":"False");
    return os;
}

}; //namespace messages
}; //namespace seatrac
}; //namespace narval

#endif //_DEF_SEATRAC_DRIVER_MESSAGES_DATA_RECEIVE_H_









