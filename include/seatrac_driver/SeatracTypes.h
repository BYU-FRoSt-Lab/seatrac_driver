#ifndef _DEF_SEATRAC_DRIVER_SEATRAC_TYPES_H_
#define _DEF_SEATRAC_DRIVER_SEATRAC_TYPES_H_

#include <sstream>
#include <cstring>
#include <seatrac_driver/SeatracEnums.h>
#include <seatrac_driver/print_utils.h>

namespace narval { namespace seatrac {

/**
 * ACOMSG_T : Acoustic Message
 *
 * The Acoustic Message structure described the contents of packets that are
 * transmitted between beacons acoustically, and form the basis for all
 * information transfer in higher level protocols.
 */
struct ACOMSG_T {
    BID_E msgDestId;           // Identifier for the beacon the message is or
                               // was the recipient of the message.
    BID_E msgSrcId;            // Identifier for the beacon that generated or
                               // sent the message.
    AMSGTYPE_E msgType;        // Value that indicates the type of message
                               // being sent.
    uint16_t msgDepth;         // Value that is only valid when MSG_TYPE is
                               // MSG_RESPX (an extended USBL response), and
                               // contains the depth sensor reading from the
                               // remote beacon. The depth is encoded 0.5m
                               // steps, and so should be divided by 2 to
                               // obtain a depth in metres.
    APAYLOAD_E msgPayloadId;   // Value that indicates the type of payload the
                               // message contains.
    uint8_t msgPayloadLen;     // Values specifying how many bytes in the
                               // payload array are valid and in use. Valid
                               // values are from 0 (for no payload) to 31.
    uint8_t msgPayload[31];    // Array of 31 bytes that contains the payload
                               // of the acoustic message. Only the number of
                               // bytes specified in the PAYLOAD_LEN parameter
                               // are valid, while the contents of the other
                               // locations are undefined. The exact function
                               // and definition of the PAYLOAD bytes depends
                               // on the type of payload specified in the
                               // PAYLOAD_ID parameter.
}__attribute__((packed));

/**
 * Range fields
 *
 * If the message ACOFIX_T.flags parameter contains the RANGE_VALID bit, then
 * the following fields are sequentially appended to the ACOFIX_T data.
 */
struct ACOFIXRANGE_T {
    uint32_t count; // The number of 16kHz timer intervals that were
                    // counted between Request message transmission and
                    // Response message reception.
    int32_t time;   // The time in seconds derived from the RANGE_COUNT
                    // value, and with internal timing offsets and
                    // compensation applied. Values are encoded in 100
                    // nanosecond multiples, so divide by 10000000 to
                    // obtain a value in seconds.
    uint16_t dist;  // The resolved line-of-sight distance to the remote
                    // beacon, based on the RANGE_TIME and VOS values.
                    // Values are encoded in decimetres, so divide by 10
                    // for a value in metres.
    
    unsigned int assign(unsigned int availableSize, const uint8_t* data)
    {
        if(availableSize < sizeof(ACOFIXRANGE_T)) {
            std::ostringstream oss;
            oss << "ACOFIXRANGE_T::assign : not enough data to decode binary";
            throw std::runtime_error(oss.str());
        }
        std::memcpy(this, data, sizeof(ACOFIXRANGE_T));
        return sizeof(ACOFIXRANGE_T);
    }
}__attribute__((packed));

/**
 * USBL fields
 *
 * If the message FLAGS parameter contains the USBL_VALID bit, then the
 * following fields are sequentially appended to the ACOFIX_T data.
 */
struct ACOFIXUSBL_T {
    uint8_t channelCount;  // The number of USBL receiver channels being used
                           // to compute the signal angle. Typically this value
                           // is either 3 or 4.
    int16_t rssi[4];   // An array of the received signal strengths for
                       // each of the USBL receiver channels, where "N" is
                       // the value defined by the CHANNELS field. Values
                       // are encoded in centi-Bels, so divide by 10 to
                       // obtain a value in decibels to a resolution of
                       // 0.1dB.
    int16_t azimuth;   // The incoming signal azimuth angle from 0deg to
                       // 360deg. Values are encoded as deci-Degrees, so
                       // divide by 10 for just degrees to a 0.1deg
                       // resolution.
    int16_t elevation; // The incoming signal elevation angle from -90deg
                       // to +90deg. Values are encoded as deci-Degrees, so
                       // divide by 10 for just degrees to a 0.1deg
                       // resolution.
    int16_t fitError;  // The fit error value returns a number that
                       // indicates the quality of fit (or confidence) of
                       // the signal azimuth and elevation values from the
                       // timing and phase-angle data available.Values are
                       // dimensionless. Divide the value by 100 to obtain
                       // a signed floating-point value to a resolution of
                       // 0.01. Smaller values towards 0.00 indicate a
                       // better fit, while larger values (increasing above
                       // 2.00-3.00) indicate poorer fits and larger error
                       // tolerances.
    unsigned int assign(unsigned int availableSize, const uint8_t* data)
    {
        const uint8_t* p = data;

        if(availableSize < 7) {
            std::ostringstream oss;
            oss << "ACOFIXUSBL_T::assign : not enough data to decode binary.";
            throw std::runtime_error(oss.str());
        }
        if(p[0] > 4) {
            std::ostringstream oss;
            oss << "ACOFIXUSBL_T::assing : Invalid number of USBL channels : "
                << (int)p[0];
            throw std::runtime_error(oss.str());
        }
        channelCount = p[0];
        p++;

        if(availableSize < 7 + channelCount*sizeof(int16_t)) {
            std::ostringstream oss;
            oss << "ACOFIXUSBL_T::assign : not enough data to decode binary.";
            throw std::runtime_error(oss.str());
        }

        std::memcpy(&rssi, p, channelCount*sizeof(int16_t));
        p += channelCount*sizeof(int16_t);
        std::memcpy(&azimuth, p, 3*sizeof(int16_t));
        p += 3*sizeof(int16_t);

        return std::distance(data, p);
    }
}__attribute__((packed));

/**
 * Position Fields
 *
 * If the message FLAGS parameter contains the POSITION_VALID bit, then the
 * following fields are sequentially appended to the ACOFIX_T data.
 */
struct ACOFIXPOSITION_T {
    int16_t easting;  // The Easting distance component of the relative
                      // position of the remote beacon to the local
                      // beacon computed from the range, incoming
                      // signal angle, local beacon depth, attitude and
                      // magnetic heading. Values are encoded in
                      // decimetres, so divide by 10 for a value in
                      // metres.
    int16_t northing; // The Northing distance component of the
                      // relative position of the remote beacon to the
                      // local beacon computed from the range, incoming
                      // signal angle, local beacon depth, attitude and
                      // magnetic heading. Values are encoded in
                      // decimetres, so divide by 10 for a value in
                      // metres.
    int16_t depth;    // The vertical Depth distance component of the
                      // remote beacon from the surface - computed from
                      // the range, incoming signal angle, local beacon
                      // depth, attitude and magnetic heading. Values
                      // are encoded in decimetres, so divide by 10 for
                      // a value in metres. 
                      // NB: If the 'Fix' has been obtained by a
                      // MSG_REQU (Usbl) type request, the this value
                      // is computed from the beacon's attitude and
                      // incoming signal angle. If a MSG_REQX
                      // (Enhanced) type request has been used, then
                      // this value is the remotely transmitted beacon
                      // depth sensor value.
    unsigned int assign(unsigned int availableSize, const uint8_t* data)
    {
        if(availableSize < sizeof(ACOFIXPOSITION_T)) {
            std::ostringstream oss;
            oss << "ACOFIXPOSITION_T::assign : not enough data to decode binary";
            throw std::runtime_error(oss.str());
        }
        std::memcpy(this, data, sizeof(ACOFIXPOSITION_T));
        return sizeof(ACOFIXPOSITION_T);
    }
}__attribute__((packed));
/**
 * ACOFIX_T : Acoustic Position and Range Fix Summary
 *
 * The Acoustic Fix structure is produced by the acoustic transceiver module
 * and contains a summary of any information relating to a received signal this
 * includes current beacon depth, beacon attitude, water VOS, signal strength
 * and any information that can be computed relating to the remote beacons
 * range and position.
 *
 * Possible values for the flags parameter :
 * - bit[0] = RANGE_VALID          If this bit is set, it indicates the record
 *                                 contains the Range fields.
 * - bit[1] = USBL_VALID           If this bit is set, it indicates the record
 *                                 contains the USBL fields.
 * - bit[2] = POSITION_VALID       If this bit is set, it indicates the record
 *                                 contains the Position fields.
 * - bit[3] = POSITION_ENHANCED    If this bit is set, it indicates the
 *                                 Position fix has been computed from an
 *                                 Enhanced USBL return this means the Depth
 *                                 will be the value from the remote beacons
 *                                 depth sensor rather than computed form the
 *                                 incoming signal angle.
 * - bit[4]   = POSITION_FLT_ERROR If this bit is true, it indicates the
 *                                 position filter has identified that the
 *                                 position specified in the fix may be invalid
 *                                 based on the beacons previous position, the
 *                                 define beacons motion limits and the time
 *                                 since last communication. However, the
 *                                 position fields still contain the USBL
 *                                 computed position and it is up to the user
 *                                 if they wish to reject this fix, or use it
 *                                 in some direct or weighted fashion.
 * - bit[7:5] = RESERVED
 *
 * The data record varies depending on the contents of the FLAGS field, with
 * required fields being appended to the end of the record as required.
 */
struct ACOFIX_T {

    BID_E destId;          // The ID code of the beacon that this data is sent
                           // to. Normally this is the local beacon ID code,
                           // but a value of BEACON_ALL indicates data has been
                           // transmitted to all beacons. Valid values are form
                           // 0 to 15.
    BID_E srcId;           // The ID code of the beacon that sent the data.
                           // Valid values are form 1 to 15.
    uint8_t flags;         // A bit-field of flags used to indicate what the
                           // rest of the record contains.
    AMSGTYPE_E msgType;    // The type of acoustic message received to generate
                           // this fix.
    int16_t attitudeYaw;   // The yaw angle (relative to magnetic north) of the
                           // local beacon when the fix was computed. Values
                           // are encoded as deci-Degrees, so divide by 10 for
                           // just degrees to a 0.1deg resolution.
    int16_t attitudePitch; // The pitch angle of the local beacon when the fix
                           // was computed. Values are encoded as deci-Degrees,
                           // so divide by 10 for just degrees to a 0.1deg
                           // resolution.
    int16_t attitudeRoll;  // The roll angle of the local beacon when the fix
                           // was computed. Values are encoded as deci-Degrees,
                           // so divide by 10 for just degrees to a 0.1deg
                           // resolution.
    uint16_t depthLocal;   // The reading from the local beacon depth sensor
                           // when the fix was calculated. Values are encoded
                           // in decimetres, so divide by 10 to obtain a value
                           // in metres to a 0.1m resolution.
    uint16_t vos;          // The velocity of sound value used for the
                           // computation of the Values are encoded in
                           // decimetres-per-second, so divide by 10 for a
                           // value in metres-per-second.
    int16_t rssi;          // The Received Signal Strength Indicator value for
                           // the received message, encoded in centibels. To
                           // decode, divide this value by 10 for decibels to a
                           // 0.1 dB resolution.

    ACOFIXRANGE_T    range;
    ACOFIXUSBL_T     usbl;
    ACOFIXPOSITION_T position;

    // This decodes data from a binary blob and returns how much data were used
    // in the blob for further parsing.
    unsigned int assign(unsigned int availableSize, const uint8_t* begin)
    {
        const uint8_t* p   = begin;
        const uint8_t* end = begin + availableSize;

        // Size in byte to be copied to fill the first fields of the struct.
        // UGLY...
        unsigned int minSize = std::distance((const uint8_t*)this,
                                             (const uint8_t*)&range);
        if(availableSize < minSize) {
            std::ostringstream oss;
            oss << "ACOFIX_T::assign : not enough data to decode binary "
                << "(needs at least " << minSize << "bytes, got "
                << availableSize << "bytes).";
            throw std::runtime_error(oss.str());
        }
        std::memcpy(this, p, minSize);
        p += minSize;
        
        if(flags & 0x1) {
            p += range.assign(std::distance(p,end), p);
        }
        if(flags & 0x2) {
            p += usbl.assign(std::distance(p,end), p);
        }
        if(flags & 0x4) {
            p += position.assign(std::distance(p,end), p);
        }
        
        // returning how many byte where used in the decoding.
        return std::distance(begin, p);
    }

}__attribute__((packed));


/**
 * AHRSCAL_T AHRS Calibration Coefficients
 *
 * An AHRS calibration structure contains all the coefficients required for the
 * accelerometer, magnetometer and gyroscope sensors to produce valid yaw,
 * pitch and roll attitude information.
 */
struct AHRSCAL_T {
    int16_t accMinX;     // The accelerometer X-axis sensor value that
                         // corresponds to -1G of gravitational force. Valid
                         // values lie in the range -1000 to +1000. Default
                         // value is -270.
    int16_t accMinY;     // The accelerometer Y-axis sensor value that
                         // corresponds to -1G of gravitational force. Valid
                         // values lie in the range -1000 to +1000. Default
                         // value is -270.
    int16_t accMinZ;     // The accelerometer Z-axis sensor value that
                         // corresponds to -1G of gravitational force. Valid
                         // values lie in the range -1000 to +1000. Default
                         // value is -270.
    int16_t accMaxX;     // The accelerometer X-axis sensor value that
                         // corresponds to +1G of gravitational force. Valid
                         // values lie in the range -1000 to +1000. Default
                         // value is 270.
    int16_t accMaxY;     // The accelerometer Y-axis sensor value that
                         // corresponds to +1G of gravitational force. Valid
                         // values lie in the range -1000 to +1000. Default
                         // value is 270.
    int16_t accMaxZ;     // The accelerometer Z-axis sensor value that
                         // corresponds to +1G of gravitational force. Valid
                         // values lie in the range -1000 to +1000. Default
                         // value is 270.
    bool magValid;       // Flag is true when the calibration contains (or
                         // represents) a valid set of coefficients. Writing an
                         // invalid calibration causes no compensation to be
                         // performed on sensor values. Reading this flag as
                         // false indicates no dynamic calibration has been
                         // computed or loaded from EEPROM memory.
    float magHardX;      // The magnetometer X-axis sensor offset value to
                         // compensate for Hard Iron effects. Valid values lie
                         // in the range -2000 to +2000. Default value is 0.
    float magHardY;      // The magnetometer Y-axis sensor offset value to
                         // compensate for Hard Iron effects. Valid values lie
                         // in the range -2000 to +2000. Default value is 0.
    float magHardZ;      // The magnetometer Z-axis sensor offset value to
                         // compensate for Hard Iron effects. Valid values lie
                         // in the range -2000 to +2000. Default value is 0.
    float magSoftX;      // The magnetometer X-axis sensor scaling value to
                         // compensate for Soft Iron effects. Valid values lie
                         // in the range -10 to +10. Default value is 1.
    float magSoftY;      // The magnetometer Y-axis sensor scaling value to
                         // compensate for Soft Iron effects. Valid values lie
                         // in the range -10 to +10. Default value is 1.
    float magSoftZ;      // The magnetometer Z-axis sensor scaling value to
                         // compensate for Soft Iron effects. Valid values lie
                         // in the range -10 to +10. Default value is 1.
    float magField;      // The normalised (not actual) magnetic field used for
                         // magnetometer calibration. Valid values lie between
                         // 0 and 100, with a typical value for idea fit being
                         // 50. Default value is 0.
    float magError;      // The fit error of the magnetic calibration. Values
                         // are expressed as a percentage between 0 and 100.
                         // Default value is 100 representing 100% error. 
    int16_t gyroOffsetX; // The rotational rate gyroscope X-axis sensor offset.
                         // Valid values lie in the range -1000 to +1000.
                         // Default value of 0.
    int16_t gyroOffsetY; // The rotational rate gyroscope Y-axis sensor offset.
                         // Valid values lie in the range -1000 to +1000.
                         // Default value of 0.
    int16_t gyroOffsetZ; // The rotational rate gyroscope Z-axis sensor offset.
                         // Valid values lie in the range -1000 to +1000.
                         // Default value of 0.
}__attribute__((packed));

/**
 * FIRMWARE_T : Firmware Information
 *
 * The FIRMWARE_T structure is used to describe configuration information for
 * the firmware that is currently loaded into memory.
 */
struct FIRMWARE_T {
    bool valid;            // Flag when true indicating the firmware is valid
                           // and allowed to execute.
    uint16_t partNumber;   // The part number of the Bootloader firmware.
    uint8_t versionMaj;    // The major version number of the firmware (when
                           // expressed in the form Version
                           // <major>.<minor>.<build>).
    uint8_t versionMin;    // The minor version number of the firmware (when
                           // expressed in the form Version
                           // <major>.<minor>.<build>).
    uint16_t versionBuild; // The sequentially assigned build number of the
                           // firmware (when expressed in the form Version
                           // <major>.<minor>.<build>).
    uint32_t checksum;     // The CRC32 checksum of the firmware.
}__attribute__((packed));

/**
 * HARDWARE_T : Hardware Information
 *
 * The HARDWARE_T structure is used to describe information related to the
 * hardware configuration of the beacon.
 */
struct HARDWARE_T {
    uint16_t partNumber;   // 795 = SeaTrac X150 USBL Beacon
                           // 843 = SeaTrac X110 Modem Beacon
    uint8_t partRev;       // The hardware product part revision.
    uint32_t serialNumber; // The unique serial number of the beacon.
    uint16_t flagsSys;     // Additional flags field defining factory set
                           // hardware capabilities and features. Currently
                           // reads as 0, reserved for future use.
    uint16_t flagsUser;    // Additional flags field defining user set hardware
                           // capabilities and features.
                           // FLAG_CMD_CSUM_DISABLE and FLAG_MAG_SENS_DISABLE
                           // are indicated in the specification but not
                           // defined...
}__attribute__((packed)); 

/**
 * IPADDR_T : IP v4 Address
 *
 * The network IP address structure can be defined either an array of 4
 * sequential bytes or a single uint32_t value (or a  union of both).
 */
struct IPADDR_T {
    // Little Endian representation of IP address fields stored in
    // "reverse order".
    // Example : ip address 192.168.0.1 is stored as as :
    // bytes[0] = 1; bytes[1] = 0; bytes[2] = 168; bytes[3] = 192;
    union {
        uint32_t addr;  
        uint8_t  bytes[4];
    };
}__attribute__((packed));

/**
 * MACADDR_T : MAC Address
 * 
 * Network MAC addresses normally only require 6-bytes of memory allocation.
 * However, for convenience the SeaTrac beacon treats MAC addresses as a uint64_t
 * type, but uses a union to allow overlaying with a 6-byte sequential array.
 */
struct MACADDR_T {
    // Little Endian representation of IP address fields stored in
    // "reverse order" (?).
    union {
        uint64_t addr;  
        uint8_t  bytes[6];
    };
}__attribute__((packed));

/**
 * SETTINGS_T : Settings Record Structure
 *
 * The Settings Record structure is used to either retrieve the current working
 * settings values in use from the beacon, or apply new changes to the beacon.
 *
 * As this structure contains current calibration and communication settings
 * for the beacon, it is always recommended to read the contents of the
 * structure from the beacon rather than populating a new structure from
 * scratch. See Settings manipulation commands in section 7.4 from 82 for
 * further details.
 */
struct SETTINGS_T {
    STATUSMODE_E statusFlags;    // Value containing flags that control the
                                 // generation and output CID_STATUS of
                                 // messages.
    STATUS_BITS_E status_output; // A bit-mask specifying which information
                                 // should be included in generated status
                                 // output messages. For each bit set in this
                                 // mask, a corresponding group of output
                                 // fields will be appended to status messages
                                 // (making them larger in size). For details
                                 // of how these fields affect the status
                                 // message content, see CID_STATUS.

    BAUDRATE_E uartMainBaud; // Specifies the serial baud rate to be used by
                             // the main communications port.
    BAUDRATE_E uartAuxBaud;  // Reserved for future use. When populating this
                             // field, use a default value of BAUD_115200.

    MACADDR_T netMacAddr;  // Reserved for future use. When populating this
                           // structure, use a default value of 0.
    IPADDR_T netIpAddr;    // Reserved for future use. When populating this
                           // structure, use a default value of 0xC0A801FA
                           // (192.168.1.250).
    IPADDR_T netIpSubnet;  // Reserved for future use. When populating this
                           // structure, use a value of 0xFFFF0000
                           // (255.255.0.0).
    IPADDR_T netIpGateway; // Reserved for future use. When populating this
                           // structure, use a default value of 0xC0A80101
                           // (192.168.1.1).
    IPADDR_T netIpDns;     // Reserved for future use. When populating this
                           // structure, use a default value of 0xC0A80101
                           // (192.168.1.1).
    uint16_t netTcpPort;   // Reserved for future use. When populating this
                           // structure, use a default value of 8100.

    ENV_FLAGS_E envFlags;   // This value contains flags that control the
                            // processing of the beacons environmental sensors
                            // (pressure, temperature, supply voltage etc).
    // int32_t envPressureOfs; // Specification says 32bits but they are
                               // probably liars (full decoding ok with 16bits).
    int16_t envPressureOfs; // The manually specified offset applied to readings
                            // take from the pressure sensor to compensate for
                            // altitude and atmospheric pressure changes.
                            // Values are encoded in milli-Bars, so divide by
                            // 1000 to obtain a value in Bars. Valid values lie
                            // in the range -1 to 1000 Bar. If auto-computation
                            // of pressure offset is enabled (in ENV_FLAGS),
                            // then any value written to this field will be
                            // lost the next time the offset is calculated.
    uint16_t envSalinity;   // The salinity value used when computing the
                            // velocity-of-sound from current pressure/depth.
                            // Values are encoded as deci-parts-per-thousand
                            // (i.e. a value of 345 represents 34.5 ppt), so
                            // divide this value by 10 to obtain a value in
                            // ppt. Typically a value of 0 represents fresh
                            // water, while 350 (35ppt) represents average sea
                            // water. Values are valid in the range 0 to
                            // 100ppt. If auto-computation of VOS is disabled
                            // (in ENV_FLAGS) then this value is not used.
    uint16_t envVos;        // The manually specified velocity of sound (VOS)
                            // to be used to convert range timing information
                            // into distances. Values are encoded in
                            // deci-metres-per-second, so divide by 10 to
                            // obtain a value in metres-per-second. Valid
                            // values are in the range 100ms -1 to 2000ms -1 .
                            // If auto-computation of VOS is enabled (in
                            // ENV_FLAGS), then any value written to this field
                            // will be lost the next time the VOS is
                            // calculated.

    AHRS_FLAGS_E ahrsFlags; // This value contains flags that control the
                            // operation of the beacons AHRS system.
    AHRSCAL_T ahrsCal;      // Structure containing the calibration data for
                            // the Attitude/Heading Reference System (AHRS).
    uint16_t ahrsYawOfs;    // A fixed attitude yaw offset that is applied to
                            // all AHRS reading. Offsets are applied to the
                            // AHRS output via a Direction-Cosine-Matrix, in
                            // the Euler sequence Yaw, Pitch then Roll.AValues
                            // are encoded as deci-degrees, so divide the value
                            // by 10 to obtain a value in degrees. Valid values
                            // are cyclically wrapped to the range 0deg to
                            // 359.9deg.
    uint16_t ahrsPitchOfs;  // A fixed attitude pitch offset that is applied to
                            // all AHRS reading. Offsets are applied to the
                            // AHRS output via a Direction-Cosine-Matrix, in
                            // the Euler sequence Yaw, Pitch then Roll. Values
                            // are encoded as deci-degrees, so divide the value
                            // by 10 to obtain a value in degrees. Valid values
                            // are clipped to the range -90.0deg to +90.0deg.
    uint16_t ahrsRollOfs;   // A fixed attitude roll offset that is applied to
                            // all AHRS reading. Offsets are applied to the
                            // AHRS output via a Direction-Cosine-Matrix, in
                            // the Euler sequence Yaw, Pitch then Roll. Values
                            // are encoded as deci-degrees, so divide the value
                            // by 10 to obtain a value in degrees. Valid values
                            // are clipped to the range -180.0deg to +180.0deg.

    XCVR_FLAGS_E xcvrFlags; // Value containing flags to control the operation
                            // of the acoustic transceiver.
    BID_E xcvrBeaconId;     // The identification code the local beacon will
                            // accept messages addressed to, or use as the
                            // source identifier when sending messages.
    uint16_t xcvrRangeTmo;  // The range timeout specifies a distance (related
                            // to time by the VOS setting) beyond which
                            // responses from beacons are ignored, and the
                            // remote beacon is considered to have timed out
                            // (see CID_XCVR_RX_RESP_ERROR messages). Values
                            // are encoded in metres. Valid values are in the
                            // range 100m to 3000m.
    uint16_t xcvrRespTime;  // The response turnaround time specifies how long
                            // the beacon will wait between receiving a request
                            // message and starting transmission of the
                            // response message. All beacons communicating
                            // acoustically within the same network must use
                            // the same value otherwise range errors will be
                            // observed. Typically, larger values than the
                            // default of 10ms can be used to reduce multi-path
                            // issues in confined spaces and allow echoes to
                            // die down before the response is sent, but should
                            // only be adjust if communication reliability
                            // issues are observed. Values are encoded in
                            // milliseconds. Valid values are in the range 10ms
                            // to 1000ms.
    uint16_t xcvrYaw;       // When the AHRS attitude is not used to specify
                            // the transceiver attitude, this value is used as
                            // the manually specified yaw attitude from which
                            // relative positions of remote beacons to the
                            // local beacon are computed. Attitudes are applied
                            // in the position calculation routine via a
                            // Direction-Cosine-Matrix, in the Euler sequence
                            // Yaw, Pitch then Roll. Values are encoded as
                            // deci-degrees, so divide the value by 10 to
                            // obtain a value in degrees. Valid values are
                            // cyclically wrapped to the range 0deg to
                            // 359.9deg.
    uint16_t xcvrPitch;     // When the AHRS attitude is not used to specify
                            // the transceiver attitude, this value is used as
                            // the manually specified pitch attitude from which
                            // relative positions of remote beacons to the
                            // local beacon are computed. Attitudes are applied
                            // in the position calculation routine via a
                            // Direction-Cosine-Matrix, in the Euler sequence
                            // Yaw, Pitch then Roll. Values are encoded as
                            // deci-degrees, so divide the value by 10 to
                            // obtain a value in degrees. Valid values are
                            // clipped to the range -90.0deg to +90.0deg.
    uint16_t xcvrRoll;      // When the AHRS attitude is not used to specify
                            // the transceiver attitude, this value is used as
                            // the manually specified roll attitude from which
                            // relative positions of remote beacons to the
                            // local beacon are computed. Attitudes are applied
                            // in the position calculation routine via a
                            // Direction-Cosine-Matrix, in the Euler sequence
                            // Yaw, Pitch then Roll. Values are encoded as
                            // deci-degrees, so divide the value by 10 to
                            // obtain a value in degrees. Valid values are
                            // clipped to the range -180.0deg to +180.0deg.
    uint8_t xcvrPosfltVel;  // The maximum velocity limit (in metres per
                            // second) that the position filter expects to see
                            // a beacon move at. Position Fix outputs for
                            // Beacons that have moved faster than this in the
                            // time between pings will be marked as a position
                            // error.
    uint8_t xcvrPosfltAng;  // For beacons that are further away, azimuth
                            // errors start to come into play. This value
                            // defines the angular limits that beacons can move
                            // (or position jitter) within without being marked
                            // as an error. Vales are specified in degrees, and
                            // typically this value is 10 degrees.
    uint8_t xcvrPosfltTmo;  // This timeout limit specified in seconds that
                            // maximum time that a beacon is not communicated
                            // with before its position filter is reset,
                            // allowing its next position (what ever that may
                            // be) to be marked as valid. For example, a value
                            // of 60 seconds means that if no communications
                            // have been made with the beacon for 60 seconds,
                            // then its position could be far outside the
                            // limits expected by the position filter, so allow
                            // its position and restart tracking on the next
                            // fix.
}__attribute__((packed));



inline std::ostream& operator<<(std::ostream& os,
                                const narval::seatrac::ACOFIXRANGE_T& msg)
{
    static const char* prefix = "\n- ";
    os << "AcofixRange :"
       << prefix << "count : " << msg.count
       << prefix << "time  : " << msg.time
       << prefix << "dist  : " << msg.dist;
    return os;
}

inline std::ostream& operator<<(std::ostream& os,
                                const narval::seatrac::ACOFIXUSBL_T& msg)
{
    static const char* prefix = "\n- ";
    os << "AcoFixUSBL :"
       << prefix << "channelCount : " << (int)msg.channelCount;
    for(int i = 0; i < msg.channelCount; i++) {
        os << prefix << "  rssi[" << i << "] : " << msg.rssi[i];
    }
    os << prefix << "azimuth      : " << msg.azimuth
       << prefix << "elevation    : " << msg.elevation
       << prefix << "fitError     : " << msg.fitError;
    return os;
}

inline std::ostream& operator<<(std::ostream& os,
                                const narval::seatrac::ACOFIXPOSITION_T& msg)
{
    static const char* prefix = "\n- ";
    os << "AcoFixPosition :"
       << prefix << "easting  : " << msg.easting 
       << prefix << "northing : " << msg.northing
       << prefix << "depth    : " << msg.depth;
    return os;
}

inline std::ostream& operator<<(std::ostream& os,
                                const narval::seatrac::ACOFIX_T& msg)
{
    using namespace narval::seatrac;
    static const char* prefix = "\n- ";

    os << "AcousticFix :"
       << prefix << "destId        : " << msg.destId
       << prefix << "srcId         : " << msg.srcId
       << prefix << "flags         : " << (int)msg.flags
       << prefix << "msgType       : " << msg.msgType
       << prefix << "attitudeYaw   : " << msg.attitudeYaw
       << prefix << "attitudePitch : " << msg.attitudePitch
       << prefix << "attitudeRoll  : " << msg.attitudeRoll
       << prefix << "depthLocal    : " << msg.depthLocal
       << prefix << "vos           : " << msg.vos
       << prefix << "rssi          : " << msg.rssi;
    if(msg.flags & 0x1) {
        os << prefix << "range    : " << print_utils::indent(msg.range);
    }
    else {
        os << prefix << "range    : No data.";
    }
    if(msg.flags & 0x2) {
        os << prefix << "usbl     : " << print_utils::indent(msg.usbl);
    }
    else {
        os << prefix << "usbl     : No data";
    }
    if(msg.flags & 0x4) {
        os << prefix << "position : " << print_utils::indent(msg.position);
    }
    else {
        os << prefix << "position : No data.";
    }
    return os;
}

inline std::ostream& operator<<(std::ostream& os,
                                const narval::seatrac::FIRMWARE_T& msg)
{
    static const char* prefix = "\n- ";
    os << "Firmware :"
       << prefix << "valid        : " << msg.valid
       << prefix << "partNumber   : " << (uint32_t)msg.partNumber
       << prefix << "versionMaj   : " << (uint32_t)msg.versionMaj
       << prefix << "versionMin   : " << (uint32_t)msg.versionMin
       << prefix << "versionBuild : " << (uint32_t)msg.versionBuild
       << prefix << "checksum     : " << (uint32_t)msg.checksum;
    return os;
}

inline std::ostream& operator<<(std::ostream& os,
                                const narval::seatrac::HARDWARE_T& msg)
{
    static const char* prefix = "\n- ";
    os << "Hardware :"
       << prefix << "partNumber   : " << (uint32_t)msg.partNumber
       << prefix << "partRev      : " << (uint32_t)msg.partRev
       << prefix << "serialNumber : " << (uint32_t)msg.serialNumber
       << prefix << "flagsSys     : " << (uint32_t)msg.flagsSys
       << prefix << "flagsUser    : " << (uint32_t)msg.flagsUser;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, narval::seatrac::IPADDR_T ip)
{
    os << ip.bytes[3]
       << "." << ip.bytes[2]
       << "." << ip.bytes[1]
       << "." << ip.bytes[0];
    return os;
}

inline std::ostream& operator<<(std::ostream& os, narval::seatrac::MACADDR_T mac)
{
    os << mac.bytes[5]
       << ":" << mac.bytes[4]
       << ":" << mac.bytes[3]
       << ":" << mac.bytes[2]
       << ":" << mac.bytes[1]
       << ":" << mac.bytes[0];
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const narval::seatrac::AHRSCAL_T& cal)
{
    static const char* prefix = "\n- ";
    os << "AHRS Calibration data :"
       << prefix << "accMinX     : " << cal.accMinX
       << prefix << "accMinY     : " << cal.accMinY
       << prefix << "accMinZ     : " << cal.accMinZ
       << prefix << "accMaxX     : " << cal.accMaxX
       << prefix << "accMaxY     : " << cal.accMaxY
       << prefix << "accMaxZ     : " << cal.accMaxZ
       << prefix << "magValid    : " << cal.magValid
       << prefix << "magHardX    : " << cal.magHardX
       << prefix << "magHardY    : " << cal.magHardY
       << prefix << "magHardZ    : " << cal.magHardZ
       << prefix << "magSoftX    : " << cal.magSoftX
       << prefix << "magSoftY    : " << cal.magSoftY
       << prefix << "magSoftZ    : " << cal.magSoftZ
       << prefix << "magField    : " << cal.magField
       << prefix << "magError    : " << cal.magError
       << prefix << "gyroOffsetX : " << cal.gyroOffsetX
       << prefix << "gyroOffsetY : " << cal.gyroOffsetY
       << prefix << "gyroOffsetZ : " << cal.gyroOffsetZ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const narval::seatrac::SETTINGS_T& settings)
{
    using namespace narval::seatrac::print_utils;
    static const char* prefix = "\n- ";
    os << "Settings :"
       << prefix << "statusFlags    : " << settings.statusFlags
       << prefix << "status_output  : " << settings.status_output
       << prefix << "uartMainBaud   : " << settings.uartMainBaud
       << prefix << "uartAuxBaud    : " << settings.uartAuxBaud
       // << prefix << "netMacAddr     : " << settings.netMacAddr
       // << prefix << "netIpAddr      : " << settings.netIpAddr
       // << prefix << "netIpSubnet    : " << settings.netIpSubnet
       // << prefix << "netIpGateway   : " << settings.netIpGateway
       // << prefix << "netIpDns       : " << settings.netIpDns
       // << prefix << "netTcpPort     : " << settings.netTcpPort
       << prefix << "envFlags       : " << settings.envFlags
       << prefix << "envPressureOfs : " << settings.envPressureOfs
       << prefix << "envSalinity    : " << settings.envSalinity
       << prefix << "envVos         : " << settings.envVos
       << prefix << "ahrsFlags      : " << settings.ahrsFlags
       << prefix << "ahrsCal        : " << indent(settings.ahrsCal)
       << prefix << "ahrsYawOfs     : " << settings.ahrsYawOfs
       << prefix << "ahrsPitchOfs   : " << settings.ahrsPitchOfs
       << prefix << "ahrsRollOfs    : " << settings.ahrsRollOfs
       << prefix << "xcvrFlags      : " << settings.xcvrFlags
       << prefix << "xcvrBeaconId   : " << settings.xcvrBeaconId
       << prefix << "xcvrRangeTmo   : " << settings.xcvrRangeTmo
       << prefix << "xcvrRespTime   : " << settings.xcvrRespTime
       << prefix << "xcvrYaw        : " << settings.xcvrYaw
       << prefix << "xcvrPitch      : " << settings.xcvrPitch
       << prefix << "xcvrRoll       : " << settings.xcvrRoll
       << prefix << "xcvrPosfltVel  : " << (int)settings.xcvrPosfltVel
       << prefix << "xcvrPosfltAng  : " << (int)settings.xcvrPosfltAng
       << prefix << "xcvrPosfltTmo  : " << (int)settings.xcvrPosfltTmo;
    return os;
}

}; //namespace seatrac
}; //namespace narval

#endif //_DEF_SEATRAC_DRIVER_SEATRAC_TYPES_H_
