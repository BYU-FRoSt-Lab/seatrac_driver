#ifndef _DEF_SEATRAC_DRIVER_MESSAGES_NAV_QUERY_RESP_H_
#define _DEF_SEATRAC_DRIVER_MESSAGES_NAV_QUERY_RESP_H_

#include <seatrac_driver/SeatracTypes.h>
#include <seatrac_driver/messages/MessageBase.h>

namespace narval { namespace seatrac { namespace messages {


struct NavQueryResp : public Message<NavQueryResp>
{
    static const CID_E Identifier = CID_NAV_QUERY_RESP;
    ACOFIX_T    acoFix;
    NAV_QUERY_E queryFlags;

    //Depth Fields
    int32_t     remoteDepth;

    //Supply Fields
    uint16_t    remoteSupply;

    //Temperature Fields
    uint16_t    remoteTemp;

    //Attitude Fields
    int16_t     remoteYaw;
    int16_t     remotePitch;
    int16_t     remoteRoll;

    //Data Fields
    uint8_t     packetLen;
    uint8_t     packetData[29];

    //Final Fields
    bool        localFlag;

    NavQueryResp& operator=(const std::vector<uint8_t>& other)
    {
        if(other[0] != this->msgId) {
            throw std::runtime_error("Wrong message for decoding.");
        }

        uint8_t acoFixSize = acoFix.assign(other.size() - 1, other.data() + 1);
        const uint8_t* p   = other.data() + 1 + acoFixSize; //pointer to start of rest of message
        this->queryFlags   = (NAV_QUERY_E)*p; p++;
        if(this->queryFlags & NAV_QUERY_E::QRY_DEPTH) {
            this->remoteDepth  = *((int32_t*)p);  p += 4;
        }
        if(this->queryFlags & NAV_QUERY_E::QRY_SUPPLY) {
            this->remoteSupply = *((uint16_t*)p); p += 2;
        }
        if(this->queryFlags & NAV_QUERY_E::QRY_TEMP) {
            this->remoteTemp   = *((uint16_t*)p); p += 2;
        }
        if(this->queryFlags & NAV_QUERY_E::QRY_ATTITUDE) {
            this->remoteYaw    = *((int16_t*)p);  p += 2;
            this->remotePitch  = *((int16_t*)p);  p += 2;
            this->remoteRoll   = *((int16_t*)p);  p += 2;
        }
        if(this->queryFlags & NAV_QUERY_E::QRY_DATA) {
            this->packetLen = *p;
            std::memcpy(this->packetData, p+1, this->packetLen);
            p += 1+this->packetLen;
        }
        this->localFlag = *p;

        return *this;
    }

}__attribute__((packed));




inline std::ostream& operator<<(std::ostream& os,
                                const narval::seatrac::messages::NavQueryResp& msg)
{
    os << "\nNavQueryResp: \n" 
       << msg.acoFix;

    if(msg.queryFlags & narval::seatrac::QRY_DEPTH) 
         os << "\n- remote depth: " << msg.remoteDepth;
    else os << "\n- remote depth: no data";
    if(msg.queryFlags & narval::seatrac::QRY_SUPPLY) 
         os << "\n- remote supply voltage: " << msg.remoteSupply;
    else os << "\n- remote supply voltage: no data";
    if(msg.queryFlags & narval::seatrac::QRY_TEMP)
         os << "\n- remote temperature: " << msg.remoteTemp;
    else os << "\n- remote temperature: no data";
    if(msg.queryFlags & narval::seatrac::QRY_ATTITUDE) {
        os << "\n- attitude:"
           << "\n\t- remote yaw: " << msg.remoteYaw
           << "\n\t- remote pitch: " << msg.remotePitch
           << "\n\t- remote roll: " << msg.remoteRoll;
    } else os << "\n- attitude: no data";
    if(msg.queryFlags & narval::seatrac::QRY_DATA) {
        os << "\n- Packet Length: " << (int)msg.packetLen
        << "\n- Packet Data:\n\t- (char):\t";
        for(uint8_t i=0; i<msg.packetLen; i++) {
            os << msg.packetData[i];
        }
        os << "\n\t- (hex):\t";
        for(uint8_t i=0; i<msg.packetLen; i++) {
            printf("%02X ", msg.packetData[i]);
        }
        os << "\n\t- (int):\t";
        for(uint8_t i=0; i<msg.packetLen; i++) {
            printf("%d ", msg.packetData[i]);
        }
        os << "\nLocal Flag: " << (msg.localFlag ? "True":"False");
    }
    else os << "\n- packet data: no data";
    return os;
}

}; //namespace messages
}; //namespace seatrac
}; //namespace narval

#endif //_DEF_SEATRAC_DRIVER_MESSAGES_NAV_QUERY_RESP_H_

