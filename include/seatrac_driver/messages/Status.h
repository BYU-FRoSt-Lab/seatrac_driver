#ifndef _DEF_SEATRAC_DRIVER_MESSAGES_STATUS_H_
#define _DEF_SEATRAC_DRIVER_MESSAGES_STATUS_H_

#include <seatrac_driver/SeatracTypes.h>
#include <seatrac_driver/messages/MessageBase.h>

namespace narval { namespace seatrac { namespace messages {

/**
 * Environmental Fields.
 *
 * If the Status.contentType field contains the ENVIRONMENT bit (see
 * STATUS_BITS_T), then the following fields are sequentially appended to the
 * message.
 */
struct StatusEnvironment {
    uint16_t envSupply;  // The beacons supply voltage. Values are encoded in
                         // milli-volts, so divide by 1000 for a value in
                         // Volts.
    int16_t envTemp;     // The temperature of air/water in contact with the
                         // diaphragm of the pressure sensor. Values are
                         // encoded in deci-Celsius, so divide by 10 to obtain
                         // a value in Celsius.
    int32_t envPressure; // The external pressure measured on the diaphragm of
                         // the pressure sensor. Values are encoded in
                         // milli-bars, so divide by 1000 to obtain a value in
                         // Bar. Please note, the specification of pressure
                         // reading is 0.5% of the sensors full-scale value, so
                         // for a 200 Bar sensor the tolerance applicable to
                         // this value is ±1 Bar (~10m).
    int32_t envDepth;    // The computed depth based on the measured
                         // environmental pressure. Values are encoded in
                         // deci-metres, so divide by 10 for a value in metres.
    uint16_t envVos;     // The value of Velocity-of-Sound currently being used
                         // for computing ranges. This may be either the
                         // manually specified VOS from settings, or the
                         // auto-computed value based on pressure, temperature
                         // and salinity. Values are encoded in
                         // deci-metres-per-second, so divide by 10 to obtain a
                         // value in metres-per-second.
}__attribute__((packed));

/**
 * Attitude Fields
 *
 * If Status.contentType contains the ATTITUDE bit (see STATUS_BITS_T), then
 * the following fields are sequentially appended to the message.
 */
struct StatusAttitude {
    int16_t attYaw;   // The current Yaw angle of the beacon, relative to
                      // magnetic north, measured by the beacons AHRS system.
                      // Values are encoded as deci-degrees, so divide the
                      // value by 10 to obtain a value in degrees.
    int16_t attPitch; // The current Pitch angle of the beacon, relative to
                      // magnetic north, measured by the beacons AHRS system.
                      // Values are encoded as deci-degrees, so divide the
                      // value by 10 to obtain a value in degrees.
    int16_t attRoll;  // The current Roll angle of the beacon, relative to
                      // magnetic north, measured by the beacons AHRS system.
                      // Values are encoded as deci-degrees, so divide the
                      // value by 10 to obtain a value in degrees.
}__attribute__((packed));

/**
 * Magnetometer Calibration and Status Fields
 *
 * If Status.contentType contains the MAG_CAL bit (see STATUS_BITS_T), then the
 * following fields are sequentially appended to the message record.  These
 * fields are commonly  used to monitor the current magnetic calibration state
 * and to assist with the  magnetometer calibration procedure.
 */
struct StatusMagCalibration {
    uint8_t magCalBuf;  // Value that indicates how full the data buffer is
                        // that holds magnetometer values describing the
                        // surrounding magnetic environment. Values are encoded
                        // as a percentage from 0 to 100 representing empty
                        // (where no magnetic calibration is possible) to full
                        // (where the best magnetic calibration can be
                        // computed).
    bool magCalValid;   // The flag is True if a magnetic calibration has been
                        // computed and is currently in use, compensating
                        // magnetometer readings.
    uint32_t magCalAge; // The number of seconds that have elapsed since the
                        // magnetometer calibration was last computed. When
                        // dynamic calibration is enabled, and there is
                        // sufficient data in the magnetic calibration buffer,
                        // then calibrations should be computed every 30
                        // seconds.
    uint8_t magCalFit;  // Value indicating how well the current magnetometer
                        // calibration can fit the measured data to an ideal
                        // "sphere" (or perfect calibration). Values are
                        // encoded as a percentage from 0 to 100.
}__attribute__((packed));

/**
 * Accelerometer Calibration Fields
 *
 * If Status.contentType contains the ACC_CAL bit (see STATUS_BITS_T), then the
 * following fields  are sequentially appended to the message record.  The
 * fields are commonly used to assist in calibrating the accelerometer
 * hardware.
 */
struct StatusAccCalibration {
    int16_t accLimMinX; // Value that holds the raw accelerometer sensor value
                        // that will be used to represent -1G on the X sensor
                        // axis.
    int16_t accLimMinY; // Value that holds the raw accelerometer sensor value 
                        // that will be used to represent +1G on the X sensor
                        // axis.
    int16_t accLimMinZ; // Value that holds the raw accelerometer sensor value
                        // that will be used to represent -1G on the Y sensor
                        // axis.
    int16_t accLimMaxX; // Value that holds the raw accelerometer sensor value
                        // that will be used to represent +1G on the Y sensor
                        // axis.
    int16_t accLimMaxY; // Value that holds the raw accelerometer sensor value
                        // that will be used to represent -1G on the Z sensor
                        // axis.
    int16_t accLimMaxZ; // Value that holds the raw accelerometer sensor value
                        // that will be used to represent +1G on the Z sensor
                        // axis.
}__attribute__((packed));

/**
 * Raw AHRS Sensor Data Fields
 *
 * If Status.contentType contains the AHRS_RAW_DATA bit (see STATUS_BITS_T),
 * then the following fields are sequentially appended to the message record.
 *
 * Values are sampled internally by the AHRS at a rate of 50Hz.
 */
struct StatusRawAHRS {
    int16_t ahrsRawAccX;  // The last raw accelerometer sensor value measured
                          // on the X-axis. This field is used during
                          // functional testing and can be used to assist with
                          // the accelerometer calibration procedure. Computing
                          // a ratio between this value and the -1G to +1G
                          // interval (specified by the ACC_LIM_MIN_X and
                          // ACC_LIM_MAX_X values), gives the current
                          // gravitation acceleration seen on the sensor axis.
    int16_t ahrsRawAccY;  // The last raw accelerometer sensor value measured
                          // on the Y-axis. This field is used during
                          // functional testing and can be used to assist with
                          // the accelerometer calibration procedure. Computing
                          // a ratio between this value and the -1G to +1G
                          // interval (specified by the ACC_LIM_MIN_Y and
                          // ACC_LIM_MAX_Y values), gives the current
                          // gravitation acceleration seen on the sensor axis.
    int16_t ahrsRawAccZ;  // The last raw accelerometer sensor value measured
                          // on the Z-axis. This field is used during
                          // functional testing and can be used to assist with
                          // the accelerometer calibration procedure. Computing
                          // a ratio between this value and the -1G to +1G
                          // interval (specified by the ACC_LIM_MIN_Z and
                          // ACC_LIM_MAX_Z values), gives the current
                          // gravitation acceleration seen on the sensor axis.
    int16_t ahrsRawMagX;  // The last ;raw magnetometer sensor value measure on
                          // the X-axis. This field is used during functional
                          // testing and can be used to assist with the
                          // magnetometer calibration procedure (in conjunction
                          // with the accelerometer orientation value).
    int16_t ahrsRawMagY;  // The last raw magnetometer sensor value measure on
                          // the Y-axis. This field is used during functional
                          // testing and can be used to assist with the
                          // magnetometer calibration procedure (in conjunction
                          // with the accelerometer orientation value).
    int16_t ahrsRawMagZ;  // The last raw magnetometer sensor value measure on
                          // the Z-axis. This field is used during functional
                          // testing and can be used to assist with the
                          // magnetometer calibration procedure (in conjunction
                          // with the accelerometer orientation value).
    int16_t ahrsRawGyroX; // The last raw rate of rotation measured around the
                          // X-axis of the gyroscope sensor. Values are encoded
                          // in degrees-per-second.
    int16_t ahrsRawGyroY; // The last raw rate of rotation measured around the
                          // Y-axis of the gyroscope sensor. Values are encoded
                          // in degrees-per-second.
    int16_t ahrsRawGyroZ; // The last raw rate of rotation measured around the
                          // Z-axis of the gyroscope sensor. Values are encoded
                          // in degrees-per-second.
}__attribute__((packed));

/**
 * Compensated AHRS Sensor Data Fields
 *
 * If Status.contentType contains the AHRS_COMP_DATA bit (see STATUS_BITS_T),
 * then the following fields are sequentially appended to the message record.
 *
 * Values are sampled internally by the AHRS at a rate of 50Hz.
 */
struct StatusCompensatedAHRS {
    float ahrsCompAccX;  // The AHRS_RAW_ACC_X sensor reading after the
                         //calibration coefficients have been applied.
    float ahrsCompAccY;  // The AHRS_RAW_ACC_Y sensor reading after the
                         // calibration coefficients have been applied.
    float ahrsCompAccZ;  // The AHRS_RAW_ACC_Z sensor reading after the
                         // calibration coefficients have been applied.
    float ahrsCompMagX;  // The AHRS_RAW_MAG_X sensor reading after the
                         // calibration coefficients have been applied.
    float ahrsCompMagY;  // The AHRS_RAW_MAG_Y sensor reading after the
                         // calibration coefficients have been applied.
    float ahrsCompMagZ;  // The AHRS_RAW_MAG_Z sensor reading after the
                         // calibration coefficients have been applied.
    float ahrsCompGyroX; // The AHRS_RAW_GYRO_X sensor reading after the
                         // calibration coefficients have been applied.
    float ahrsCompGyroY; // The AHRS_RAW_ GYRO _Y sensor reading after the
                         // calibration coefficients have been applied.
    float ahrsCompGyroZ; // The AHRS_RAW_ GYRO _Z sensor reading after the
                         // calibration coefficients have been applied.
}__attribute__((packed));

struct Status : public Message<Status>
{
    static const CID_E Identifier = CID_STATUS;

    STATUS_BITS_E         contentType;
    uint64_t              timestamp;
    StatusEnvironment     environment;
    StatusAttitude        attitude;
    StatusMagCalibration  magCalibration;
    StatusAccCalibration  accCalibration;
    StatusRawAHRS         rawAHRS;
    StatusCompensatedAHRS compensatedAHRS;

    Status& operator=(const std::vector<uint8_t>& data) {
        
        const uint8_t* p = data.data();

        // Validating CID_E
        if(p[0] != CID_STATUS) {
            std::ostringstream oss;
            oss << "Invalid CID_E for Status message (expected "
                << CID_STATUS << ", got " << p[0] << ").";
            throw std::runtime_error(oss.str());
        }
        p++;

        // Copying fixed status content
        contentType = *reinterpret_cast<const STATUS_BITS_E*>(p);
        p += sizeof(STATUS_BITS_E);
        timestamp = *reinterpret_cast<const uint64_t*>(p);
        p += sizeof(uint64_t);
        
        // Now checking contentType to copy data chunks if present.
        if(this->expected_size() != data.size()) {
            std::ostringstream oss;
            oss << "Got Status message but wrong number of bytes (expected " <<
                    this->expected_size() << ", got " << data.size() << ")\n";
            throw std::runtime_error(oss.str());
        }

        if(contentType & ENVIRONMENT) {
            environment = *reinterpret_cast<const messages::StatusEnvironment*>(p);
            p += sizeof(messages::StatusEnvironment);
        }
        if(contentType & ATTITUDE) {
            attitude = *reinterpret_cast<const messages::StatusAttitude*>(p);
            p += sizeof(messages::StatusAttitude);
        }
        if(contentType & MAG_CAL) {
            magCalibration = *reinterpret_cast<const messages::StatusMagCalibration*>(p);
            p += sizeof(messages::StatusMagCalibration);
        }
        if(contentType & ACC_CAL) {
            accCalibration = *reinterpret_cast<const messages::StatusAccCalibration*>(p);
            p += sizeof(messages::StatusAccCalibration);
        }
        if(contentType & AHRS_RAW_DATA) {
            rawAHRS = *reinterpret_cast<const messages::StatusRawAHRS*>(p);
            p += sizeof(messages::StatusRawAHRS);
        }
        if(contentType & AHRS_COMP_DATA) {
            compensatedAHRS = *reinterpret_cast<const messages::StatusCompensatedAHRS*>(p);
            p += sizeof(messages::StatusCompensatedAHRS);
        }

        return *this;
    }
    
    unsigned int expected_size() const {
        unsigned int expectedSize = sizeof(CID_E) + sizeof(contentType) + sizeof(timestamp);
        if(contentType & ENVIRONMENT) {
            expectedSize += sizeof(messages::StatusEnvironment);
        }
        if(contentType & ATTITUDE) {
            expectedSize += sizeof(messages::StatusAttitude);
        }
        if(contentType & MAG_CAL) {
            expectedSize += sizeof(messages::StatusMagCalibration);
        }
        if(contentType & ACC_CAL) {
            expectedSize += sizeof(messages::StatusAccCalibration);
        }
        if(contentType & AHRS_RAW_DATA) {
            expectedSize += sizeof(messages::StatusRawAHRS);
        }
        if(contentType & AHRS_COMP_DATA) {
            expectedSize += sizeof(messages::StatusCompensatedAHRS);
        }
        return expectedSize;
    }
}__attribute__((packed));



inline std::ostream& operator<<(std::ostream& os,
                                const narval::seatrac::messages::StatusEnvironment& msg)
{
    const char* prefix = "\n- ";
    os << "Environment : " << sizeof(msg)
        << prefix << "envSupply   : " << msg.envSupply
        << prefix << "envTemp     : " << msg.envTemp
        << prefix << "envPressure : " << msg.envPressure
        << prefix << "envDepth    : " << msg.envDepth
        << prefix << "envVos      : " << msg.envVos;
    return os;
}

inline std::ostream& operator<<(std::ostream& os,
                                const narval::seatrac::messages::StatusAttitude& msg)
{
    const char* prefix = "\n- ";
    os << "Attitude :"
       << prefix << "attYaw    : " << msg.attYaw
       << prefix << "attPitch  : " << msg.attPitch
       << prefix << "attRoll   : " << msg.attRoll;
    return os;
}

inline std::ostream& operator<<(std::ostream& os,
                                const narval::seatrac::messages::StatusMagCalibration& msg)
{
    const char* prefix = "\n- ";
    os << "MagCalibration :"
       << prefix << "magCalBuf   : " << msg.magCalBuf
       << prefix << "magCalValid : " << msg.magCalValid
       << prefix << "magCalAge   : " << msg.magCalAge
       << prefix << "magCalFit   : " << msg.magCalFit;
    return os;
}

inline std::ostream& operator<<(std::ostream& os,
                                const narval::seatrac::messages::StatusAccCalibration& msg)
{
    const char* prefix = "\n- ";
    os << "AccCalibration :"
       << prefix << "accLimMinX : " << msg.accLimMinX
       << prefix << "accLimMinY : " << msg.accLimMinY
       << prefix << "accLimMinZ : " << msg.accLimMinZ
       << prefix << "accLimMaxX : " << msg.accLimMaxX
       << prefix << "accLimMaxY : " << msg.accLimMaxY
       << prefix << "accLimMaxZ : " << msg.accLimMaxZ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os,
                                const narval::seatrac::messages::StatusRawAHRS& msg)
{
    const char* prefix = "\n- ";
    os << "RawAHRS :"
       << prefix << "ahrsRawAccX  : " << msg.ahrsRawAccX
       << prefix << "ahrsRawAccY  : " << msg.ahrsRawAccY
       << prefix << "ahrsRawAccZ  : " << msg.ahrsRawAccZ
       << prefix << "ahrsRawMagX  : " << msg.ahrsRawMagX
       << prefix << "ahrsRawMagY  : " << msg.ahrsRawMagY
       << prefix << "ahrsRawMagZ  : " << msg.ahrsRawMagZ
       << prefix << "ahrsRawGyroX : " << msg.ahrsRawGyroX
       << prefix << "ahrsRawGyroY : " << msg.ahrsRawGyroY
       << prefix << "ahrsRawGyroZ : " << msg.ahrsRawGyroZ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os,
                                const narval::seatrac::messages::StatusCompensatedAHRS& msg)
{
    const char* prefix = "\n- ";
    os << "CompensatedAHRS :"
       << prefix << "ahrsCompAccX  : " << msg.ahrsCompAccX
       << prefix << "ahrsCompAccY  : " << msg.ahrsCompAccY
       << prefix << "ahrsCompAccZ  : " << msg.ahrsCompAccZ
       << prefix << "ahrsCompMagX  : " << msg.ahrsCompMagX
       << prefix << "ahrsCompMagY  : " << msg.ahrsCompMagY
       << prefix << "ahrsCompMagZ  : " << msg.ahrsCompMagZ
       << prefix << "ahrsCompGyroX : " << msg.ahrsCompGyroX
       << prefix << "ahrsCompGyroY : " << msg.ahrsCompGyroY
       << prefix << "ahrsCompGyroZ : " << msg.ahrsCompGyroZ;
    return os;
};

inline std::ostream& operator<<(std::ostream& os, const narval::seatrac::messages::Status& msg)
{
    using namespace narval::seatrac;
    using namespace narval::seatrac::print_utils;
    const char* prefix = "\n- ";
    os << "Status : " << sizeof(msg)
       << prefix << "msgId       : " << msg.msgId
       << prefix << "contentType : " << msg.contentType
       << prefix << "timestamp   : " << msg.timestamp;
       //<< prefix << "timestamp   : " << msg.timestamp2;

    if(msg.contentType & ENVIRONMENT) {
        os << prefix << indent(msg.environment);
    }
    else {
        os << prefix << "Environment : Empty";
    }
    if(msg.contentType & ATTITUDE) {
        os << prefix << indent(msg.attitude);
    }
    else {
        os << prefix << "Attitude : Empty";
    }
    if(msg.contentType & MAG_CAL) {
        os << prefix << indent(msg.magCalibration);
    }
    else {
        os << prefix << "MagCalibration : Empty";
    }
    if(msg.contentType & ACC_CAL) {
        os << prefix << indent(msg.accCalibration);
    }
    else {
        os << prefix << "AccCalibration : Empty";
    }
    if(msg.contentType & AHRS_RAW_DATA) {
        os << prefix << indent(msg.rawAHRS);
    }
    else {
        os << prefix << "RawAHRS : Empty";
    }
    if(msg.contentType & AHRS_COMP_DATA) {
        os << prefix << indent(msg.compensatedAHRS);
    }
    else {
        os << prefix << "CompensatedAHRS : Empty";
    }

    return os;
}

}; //namespace messages
}; //namespace seatrac
}; //namespace narval

#endif //_DEF_SEATRAC_DRIVER_MESSAGES_STATUS_H_
