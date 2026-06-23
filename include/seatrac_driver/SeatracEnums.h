#ifndef _DEF_SEATRAC_DRIVER_SEATRAC_ENUMS_H_
#define _DEF_SEATRAC_DRIVER_SEATRAC_ENUMS_H_

#include <cstdint>
#include <iostream>
#include <sstream>


namespace narval { namespace seatrac {

/**
 * AMSGTYPE_E : Acoustic Message Type.
 *
 * The AMSGTYPE_E enumeration is used to specify a type of acoustic message,
 * and determines how the message is processed and which responses are
 * generated from beacons.
 */
enum AMSGTYPE_E : uint8_t {
    MSG_OWAY = 0x0,    // Indicates an acoustic message is sent One-Way, and
                       // does not require a response. One-Way messages may
                       // also be broadcast to all beacons if required.  No
                       // USBL information is sent.
    MSG_OWAYU = 0x1,   // Indicates an acoustic message is sent One-Way, and
                       // does not require a response. One-Way messages may
                       // also be broadcast to all beacons if required.
                       // Additionally, the message is sent with USBL acoustic
                       // information allowing an incoming bearing to be
                       // determined by USBL receivers, although range cannot
                       // be provided.
    MSG_REQ = 0x2,     // Indicates an acoustic message is sent as a Request
                       // type.  This requires the receiver to generate and
                       // return a Response (MSG_RESP) message.  No USBL
                       // information is requested.
    MSG_RESP = 0x3,    // Indicate an acoustic message is sent as a Response to
                       // a previous Request message (MSG_REQ).  No USBL
                       // information is returned.
    MSG_REQU = 0x4,    // Indicates an acoustic message is sent as a Request
                       // type.  This requires the receiver to generate and
                       // return a Response (MSG_RESP) message.  Additionally,
                       // the Response message should be returned with USBL
                       // acoustic information allowing a position fix to be
                       // computed by USBL receivers through the range and
                       // incoming signal angle.
    MSG_RESPU = 0x5,   // Indicate an acoustic message is sent as a Response to
                       // a previous Request message (MSG_REQ).  Additionally,
                       // the message is sent with USBL acoustic information
                       // allowing the position of the sender to be determined
                       // through the range and incoming signal angle.
    MSG_REQX = 0x6,    // Indicates an acoustic message is sent as a Request
                       // type.  This requires the receiver to generate and
                       // return a Response (MSG_RESP) message.  Additionally,
                       // the Response message should be returned with extended
                       // Depth and USBL acoustic information allowing a more
                       // accurate position fix to be computed by USBL
                       // receivers through the range, remote depth and
                       // incoming signal angle.
    MSG_RESPX = 0x7,   // Indicate an acoustic message is sent as a Response to
                       // a previous Request message (MSG_REQ).  Additionally,
                       // the message is sent with extended depth and USBL
                       // acoustic information allowing a more accurate
                       // position of the sender to be determined through the
                       // range, remote depth and incoming signal angle.
    MSG_UNKNOWN = 0xFF // This value is NEVER used to specify a message type
                       // when sending Acoustic Messages. However, on occasions
                       // certain structures need to specify "No Message Type"
                       // (for example see ACOFIX_T), and this value is used as
                       // an OUTPUT ONLY to indicate this.
};

/**
 * APAYLOAD_E Acoustic Payload Identifier.
 *
 * The APAYLOAD_E enumeration is used to specify how the payload contents of
 * acoustic messages (see ACOMSG_T structures) are decoded and processed.
 */
enum APAYLOAD_E : uint8_t {
    PLOAD_PING = 0x0, // Specified an acoustic message payload should be
                      // interpreted by the PING protocol handler.  PING
                      // messages provide the simplest (and quickest) method of
                      // validating the presence of a beacon, and determining
                      // its position.
    PLOAD_ECHO = 0x1, // Specified an acoustic message payload should be
                      // interpreted by the ECHO protocol handler.  ECHO
                      // messages allow the function and reliability of a
                      // beacon to be tested, by requesting the payload
                      // contents of the message be returned back to the
                      // sender.
    PLOAD_NAV = 0x2,  // Specified an acoustic message payload should be
                      // interpreted by the NAV (Navigation) protocol handler.
                      // NAV messages allow tracking and navigation systems to
                      // be built that use enhanced positioning and allow
                      // remote parameters of beacons (such as heading,
                      // attitude, water temperature etc) to be queried.
    PLOAD_DAT = 0x3,  // Specified an acoustic message payload should be
                      // interpreted by the DAT (Datagram) protocol handler.
                      // DAT messages for the simplest method of data exchange
                      // between beacons, and provide a method of acknowledging
                      // data reception.
    PLOAD_DEX = 0x4,  // Specified an acoustic message payload should be
                      // interpreted by the DEX (Data Exchange) protocol
                      // handler.  DEX messages implement a protocol that
                      // allows robust bi-directional socket based data
                      // exchange with timeouts, acknowledgments and retry
                      // schemes.
    PLOAD_RES = 0x5,  // Reserved for future use.
};

/**
 * BAUDRATE_E : Serial Port Baud Rate
 *
 * The baud rate enumeration defines codes representing the speed of serial
 * communications ports. Values specified outside those defined in the table
 * below will default to BAUD_115200.
 */
enum BAUDRATE_E : uint8_t {
    BAUD_4800   = 0x07, // 4800   bits per second
    BAUD_9600   = 0x08, // 9600   bits per second
    BAUD_14400  = 0x09, // 14400  bits per second
    BAUD_19200  = 0x0A, // 19200  bits per second
    BAUD_38400  = 0x0B, // 38400  bits per second
    BAUD_57600  = 0x0C, // 57600  bits per second
    BAUD_115200 = 0x0D, // 115200 bits per second
};

/**
 * BID_E : Beacon Identification Code
 *
 * Beacon Identification (BID) Codes are used to identify a specific beacon
 * that should receive acoustic messages, or identify which beacon was the
 * source (sender) of a message. Valid values are in the range from 0 to 15 and
 * are typically send and stored as a UINT8.
 */
enum BID_E : uint8_t {
    BEACON_ALL = 0x0,   // When used as an address for sending acoustic
                        // messages to, the value of 0x00 indicates "broadcast
                        // to all".  When used as an identifier of a sender of
                        // a message, the value of 0x00 should be interpreted
                        // as unknown or invalid (reserved).
    BEACON_ID_1  = 0x1,
    BEACON_ID_2  = 0x2,
    BEACON_ID_3  = 0x3,
    BEACON_ID_4  = 0x4,
    BEACON_ID_5  = 0x5,
    BEACON_ID_6  = 0x6,
    BEACON_ID_7  = 0x7,
    BEACON_ID_8  = 0x8,
    BEACON_ID_9  = 0x9,
    BEACON_ID_10 = 0xa,
    BEACON_ID_11 = 0xb,
    BEACON_ID_12 = 0xc,
    BEACON_ID_13 = 0xd,
    BEACON_ID_14 = 0xe,
    BEACON_ID_15 = 0xf,
};

/**
 * CAL_ACTION_E : Calibration Actions
 *
 * The Calibration Action enumeration defines what operation the beacon should
 * perform when a CID_CAL_ACTION command is issued.
 */
enum CAL_ACTION_E : uint8_t {
    CAL_ACC_DEFAULTS = 0x00,      // Sets the current accelerometer calibration
                                  // coefficient values back to defaults.
    CAL_ACC_RESET = 0x01,         // Resets the accelerometer Min and Max
                                  // filtered limit values measured by the
                                  // sensor (does not modify the current
                                  // calibration).
    CAL_ACC_CALC = 0x02,          // Calculates the new accelerometer
                                  // calibration coefficients from the measured
                                  // sensor limit values.
    CAL_MAG_DEFAULTS = 0x03,      // Sets the current magnetometer calibration
                                  // values back to defaults for Hard and Sort
                                  // Iron (does not clear the magnetic buffer).
    CAL_MAG_RESET = 0x04,         // Clears the magnetic calibration buffer
                                  // (does not modify the current calibration).
    CAL_MAG_CALC = 0x05,          // Calculate and apply a new Magnetometer
                                  // calibration from current magnetic buffer
                                  // values.
    CAL_PRES_OFFSET_RESET = 0x06, // Reset the pressure offset back to zero
                                  // Bar.
    CAL_PRES_OFFSET_CALC = 0x07,  // Sets the pressure offset from the current
                                  // measured pressure, zeroing the depth
                                  // sensor reading.
};

/**
 * CID_E : Command Identification Codes
 *
 * Command Identification (CID) Codes are an enumeration (or defined set of
 * constants) stored/transmitted in a UINT8 type at the start of Command and
 * Response messages after the synchronisation character, with the purpose of
 * identifying the message function and its payload.
 */
enum CID_E : uint8_t {
    // System Messages
    CID_SYS_ALIVE = 0x01,       // Command sent to receive a simple alive
                                // message from the beacon.
    CID_SYS_INFO = 0x02,        // Command sent to receive hardware & firmware
                                // identification information.
    CID_SYS_REBOOT = 0x03,      // Command sent to soft reboot the beacon.
    CID_SYS_ENGINEERING = 0x04, // Command sent to perform engineering actions.

    // Firmware Programming Messages
    CID_PROG_INIT = 0x0D,   // Command sent to initialise a firmware
                            // programming sequence.
    CID_PROG_BLOCK = 0x0E,  // Command sent to transfer a firmware programming
                            // block.
    CID_PROG_UPDATE = 0x0F, // Command sent to update the firmware once program
                            // transfer has completed.

    // Status Messages
    CID_STATUS = 0x10,         // Command sent to request the current system
                               // status (AHRS, Depth, Temp, etc).
    CID_STATUS_CFG_GET = 0x11, // Command sent to retrieve the configuration of
                               // the status system (message content and
                               // auto-output interval).
    CID_STATUS_CFG_SET = 0x12, // Command sent to set the configuration of the
                               // status system (message content and
                               // auto-output interval).

    // Settings Messages
    CID_SETTINGS_GET = 0x15,   // Command sent to retrieve the working settings
                               // in use on the beacon.
    CID_SETTINGS_SET = 0x16,   // Command sent to set the working settings and
                               // apply them. They are NOT saved to permanent
                               // memory until CID_ SETTINGS_SAVE is issued.
                               // The device will need to be rebooted after
                               // this to apply some of the changes.
    CID_SETTINGS_LOAD = 0x17,  // Command sent to load the working settings
                               // from permanent storage and apply them. Not
                               // all settings can be loaded and applied as
                               // they only affect the device on start-up.
    CID_SETTINGS_SAVE = 0x18,  // Command sent to save the working settings
                               // into permanent storage.
    CID_SETTINGS_RESET = 0x19, // Command sent to restore the working settings
                               // to defaults, store them into permanent memory
                               // and apply them.

    // Calibration messages
    CID_CAL_ACTION   = 0x20, // Command sent to perform specific calibration
                             // actions.
    CID_AHRS_CAL_GET = 0x21, // Command sent to retrieve the current AHRS
                             // calibration.
    CID_AHRS_CAL_SET = 0x22, // Command sent to set the contents of the current
                             // AHRS calibration (and store to memory)

    // Acoustic Transceiver Messages
    CID_XCVR_ANALYSE = 0x30,      // Command sent to instruct the receiver to
                                  // perform a noise analysis and report the
                                  // results.
    CID_XCVR_TX_MSG = 0x31,       // Message sent when the transceiver
                                  // transmits a message.
    CID_XCVR_RX_ERR = 0x32,       // Message sent when the transceiver receiver
                                  // encounters an error.
    CID_XCVR_RX_MSG = 0x33,       // Message sent when the transceiver receives
                                  // a message (not requiring a response).
    CID_XCVR_RX_REQ = 0x34,       // Message sent when the transceiver receives
                                  // a request (requiring a response).
    CID_XCVR_RX_RESP = 0x35,      // Message sent when the transceiver receives
                                  // a response (to a transmitted request).
    CID_XCVR_RX_UNHANDLED = 0x37, // Message sent when a message has been
                                  // received but not handled by the protocol
                                  // stack.
    CID_XCVR_USBL = 0x38,         // Message sent when a USBL signal is decoded
                                  // into an angular bearing.
    CID_XCVR_FIX = 0x39,          // Message sent when the transceiver gets a
                                  // position/range fix on a beacon from a
                                  // request/response.
    CID_XCVR_STATUS = 0x3A,       // Message sent to query the current
                                  // transceiver state.

    // PING Protocol Messages
    CID_PING_SEND = 0x40,  // Command sent to transmit a PING message.
    CID_PING_REQ = 0x41,   // Message sent when a PING request is received.
    CID_PING_RESP = 0x42,  // Message sent when a PING response is received, or
                           // timeout occurs, with the echo response data.
    CID_PING_ERROR = 0x43, // Message sent when a PING response error/timeout
                           // occurs.

    // ECHO Protocol Messages
    CID_ECHO_SEND = 0x48,  // Command sent to transmit an ECHO message.
    CID_ECHO_REQ = 0x49,   // Message sent when an ECHO request is received.
    CID_ECHO_RESP = 0x4A,  // Message sent when an ECHO response is received,
                           // or timeout occurs, with the echo response data.
    CID_ECHO_ERROR = 0x4B, // Message sent when an ECHO response error/timeout
                           // occurs.

    // NAV Protocol Messages
    CID_NAV_QUERY_SEND = 0x50,     // Message sent to query navigation
                                   // information from a remote beacon.
    CID_NAV_QUERY_REQ = 0x51,      // Message sent from a beacon that receives
                                   // a NAV_QUERY.
    CID_NAV_QUERY_RESP = 0x52,     // Message generated when the beacon
                                   // received a response to a NAV_QUERY.
    CID_NAV_ERROR = 0x53,          // Message generated if there is a problem
                                   // with a NAV_QUERY - i.e. timeout etc.
    CID_NAV_QUEUE_SET = 0x58,      // Message sent to set the contents of the
                                   // packet data queue.
    CID_NAV_QUEUE_CLR = 0x59,      // Message sent to clear the contents of the
                                   // packet data queue.
    CID_NAV_QUEUE_STATUS = 0x5A,   // Message sent to obtain the current status
                                   // of the packet data queue.
    CID_NAV_STATUS_SEND = 0x5B,    // Message that is used to broadcast status
                                   // information from one beacon (typically
                                   // the USBL head) to others in the system.
                                   // This may include beacon positions, GPS
                                   // coordinates etc.
    CID_NAV_STATUS_RECEIVE = 0x5C, // Message generated when a beacon receives
                                   // a NAV_STATUS message.

    // DAT Protocol Messages
    CID_DAT_SEND = 0x60,         // Message sent to transmit a datagram to
                                 // another beacon
    CID_DAT_RECEIVE = 0x61,      // Message generated when a beacon receives a
                                 // datagram.
    CID_DAT_ERROR = 0x63,        // Message generated when a beacon response
                                 // error/timeout occurs for ACKs.
    CID_DAT_QUEUE_SET = 0x64,    // Message sent to set the contents of the
                                 // packet data queue.
    CID_DAT_QUEUE_CLR = 0x65,    // Message sent to clear the contents of the
                                 // packet data queue.
    CID_DAT_QUEUE_STATUS = 0x66, // Message sent to obtain the current status
                                 // of the packet data queue.
};

/**
 * CST_E : Command Status Codes
 *
 * Command Status (CST) Codes are an enumeration (or set of defined constants)
 * that are commonly used in Response  messages sent from the beacon to
 * indicate if a command executed successfully,  or if not, what type of error
 * occurred.  CST codes are always transmitted as a  UINT8 type.
 *
 * Different Response messages may only implement a subset of the constants
 * below, as appropriate for their function.
 */
enum CST_E : uint8_t {
    // General Status Codes
    CST_OK = 0x00,           // Returned if a command or operation is completed
                             // successful without error.
    CST_FAIL = 0x01,         // Returned if a command or operation cannot be
                             // completed.
    CST_EEPROM_ERROR = 0x03, // Returned if an error occurs while reading or
                             // writing EEPROM data.

    // Command Processor Status Codes
    CST_CMD_PARAM_MISSING = 0x04, // Returned if a command message is given
                                  // that does not have enough defined fields
                                  // for the specified CID code.
    CST_CMD_PARAM_INVALID = 0x05, // Returned if a data field in a message does
                                  // not contain a valid or expected value.

    // Firmware Programming Status Codes
    CST_PROG_FLASH_ERROR = 0x0A,    // Returned if an error occurs while
                                    // writing data into the processors flash
                                    // memory.
    CST_PROG_FIRMWARE_ERROR = 0x0B, // Returned if firmware cannot be
                                    // programmed due to incorrect firmware
                                    // credentials or signature.
    CST_PROG_SECTION_ERROR = 0x0C,  // Returned if the firmware cannot be
                                    // programmed into the specified memory
                                    // section.
    CST_PROG_LENGTH_ERROR = 0x0D,   // Returned if the firmware length is too
                                    // large to fit into the specified memory
                                    // section, or not what the current
                                    // operation is expecting.
    CST_PROG_DATA_ERROR = 0x0E,     // Returned if there is an error decoding
                                    // data in a firmware block.
    CST_PROG_CHECKSUM_ERROR = 0x0F, // Returned if the specified checksum for
                                    // the firmware does not match the checksum
                                    // computed prior to performing the update.

    // Acoustic Transceiver Status Codes
    CST_XCVR_BUSY = 0x30,          // Returned if the transceiver cannot
                                   // perform a requested action as it is
                                   // currently busy (i.e. transmitting a
                                   // message).
    CST_XCVR_ID_REJECTED = 0x31,   // Returned if the received message did not
                                   // match the specified transceiver ID (and
                                   // wasn t a Sent-To-All), and the message
                                   // has been rejected.
    CST_XCVR_CSUM_ERROR = 0x32,    // Returned if received acoustic message's
                                   // checksum was invalid, and the message has
                                   // been rejected.
    CST_XCVR_LENGTH_ERROR = 0x33,  // Returned if an error occurred with
                                   // message framing, meaning the end of the
                                   // message has not been received within the
                                   // expected time.
    CST_XCVR_RESP_TIMEOUT = 0x34,  // Returned if the transceiver has sent a
                                   // request message to a beacon, but no
                                   // response has been returned within the
                                   // allotted waiting period.
    CST_XCVR_RESP_ERROR = 0x35,    // Returned if the transceiver has send a
                                   // request message to a beacon, but an error
                                   // occurred while receiving the response.
    CST_XCVR_RESP_WRONG = 0x36,    // Returned if the transceiver has sent a
                                   // request message to a beacon, but received
                                   // an unexpected response from another
                                   // beacon while waiting.
    CST_XCVR_PLOAD_ERROR = 0x37,   // Returned by protocol payload decoders, if
                                   // the payload can t be parsed correctly.
    CST_XCVR_STATE_STOPPED = 0x3A, // Indicates the transceiver is in a stopped state.
    CST_XCVR_STATE_IDLE = 0x3B,    // Indicates the transceiver is in an idle
                                   // state waiting for reception or
                                   // transmission to start.
    CST_XCVR_STATE_TX = 0x3C,      // Indicates the transceiver is in a
                                   // transmitting states.
    CST_XCVR_STATE_REQ = 0x3D,     // Indicates the transceiver is in a
                                   // requesting state, having transmitted a
                                   // message and is waiting for a response to
                                   // be received.
    CST_XCVR_STATE_RX = 0x3E,      // Indicates the transceiver is in a
                                   // receiving state.
    CST_XCVR_STATE_RESP = 0x3F,    // Indicates the transceiver is in a
                                   // responding state, where a message is
                                   // being composed and the "response time"
                                   // period is being observed.

    // DEX Protocol Status Codes
    CST_DEX_SOCKET_ERROR = 0x70,      // Returned by the DEX protocol handler
                                      // if an error occurred trying to open,
                                      // close or access a specified socket ID.
    CST_DEX_RX_SYNC = 0x71,           // Returned by the DEX protocol handler
                                      // when receiver synchronisation has
                                      // occurred with the socket master and
                                      // data transfer is ready to commence.
    CST_DEX_RX_DATA = 0x72,           // Returned by the DEX protocol handler
                                      // when data has been received through a
                                      // socket.
    CST_DEX_RX_SEQ_ERROR = 0x73,      // Returned by the DEX protocol handler
                                      // when data transfer synchronisation has
                                      // been lost with the socket master.
    CST_DEX_RX_MSG_ERROR = 0x74,      // Returned by the DEX protocol handler
                                      // to indicate an unexpected acoustic
                                      // message type with the DEX protocol has
                                      // been received and cannot be processed.
    CST_DEX_REQ_ERROR = 0x75,         // Returned by the DEX protocol handler
                                      // to indicate a error has occurred while
                                      // responding to a request (i.e. lack of
                                      // data).
    CST_DEX_RESP_TMO_ERROR = 0x76,    // Returned by the DEX protocol handler
                                      // to indicate a timeout has occurred
                                      // while waiting for a response back from
                                      // a remote beacon with requested data.
    CST_DEX_RESP_MSG_ERROR = 0x77,    // Returned by the DEX protocol handler
                                      // to indicate an error has occurred
                                      // while receiving response back from a
                                      // remote beacon.
    CST_DEX_RESP_REMOTE_ERROR = 0x78, // Returned by the DEX protocol handler
                                      // to indicate the remote beacon has
                                      // encountered an error and cannot return
                                      // the requested data or perform the
                                      // required operation.
};

/** 
 * STATUSMODE_E : Status Output Mode
 *
 * The Status Mode enumeration is used to specify how often periodic status
 * output messages are automatically generated...
 */
enum STATUSMODE_E : uint8_t {
    STATUS_MODE_MANUAL = 0x0, // Status output message are not generated
                              // automatically, only upon manual request by
                              // sending the CID_STATUS command.
    STATUS_MODE_1HZ = 0x1,    // Status output message are generated at 1
                              // second (1Hz) intervals.
    STATUS_MODE_2HZ5 = 0x2,   // Status output message are generated at 0.4
                              // second (2.5Hz) intervals.
    STATUS_MODE_5HZ = 0x3,    // Status output message are generated at 0.2
                              // second (5Hz) intervals.
    STATUS_MODE_10HZ = 0x4,   // Status output message are generated at 0.1
                              // second (10Hz) intervals.
    STATUS_MODE_25HZ = 0x5,   // Status output message are generated at
                              // 0.04 second (25Hz) intervals. Be wary using
                              // this setting, as on slow communication baud
                              // rates, this setting may lead to a situation
                              // where more data is required to be sent down
                              // the link in a set period of time than the link
                              // is physically capable of sending and the
                              // beacon processor may stall.
};

/**
 * NAV_QUERY_E : NAV Protocol Query Bit Mask
 *
 * The NAV Protocol Query Flags type is defined as a bit-field stored in a
 * uint8_t value, where one or more bits (flags) may be set to specify an overall
 * numerical value.
 *
 */
enum NAV_QUERY_E : uint8_t {
    QRY_DEPTH = 0x01,    // When set, a NAV_QUERY_SEND command will request
                         // that depth information is sent back, and a
                         // NAV_QUERY_RESP will contain depth data fields.
    QRY_SUPPLY = 0x02,   // When set, a NAV_QUERY_SEND command will request
                         // that supply voltage information is sent back, and a
                         // NAV_QUERY_RESP will contain supply voltage data
                         // fields.
    QRY_TEMP = 0x04,     // When set, a NAV_QUERY_SEND command will request
                         // that temperature information is sent back, and a
                         // NAV_QUERY_RESP will contain temperature data
                         // fields.
    QRY_ATTITUDE = 0x08, // When set, a NAV_QUERY_SEND command will request
                         // that attitude information is sent back, and a
                         // NAV_QUERY_RESP will contain attitude data fields.
    QRY_DATA = 0x80,     // When set, a NAV_QUERY_SEND command will request
                         // that any queued pending NAV data should be sent
                         // back, and a NAV_QUERY_RESP will contain data
                         // payload fields.
};

/**
 * STATUS_BITS_E : Status Fields Bit-Mask
 *
 * The Status Flags type is defined as a bit-field stored in a uint8_t value,
 * where one or more bits (flags) may be set to specify an overall numerical
 * value.
 */
enum STATUS_BITS_E : uint8_t {
    ENVIRONMENT = 0x01,    // When set, appends environmental sensor data
                           // fields (temperature, depth, VOS, supply voltage
                           // etc) to the end of the status output message.
    ATTITUDE = 0x02,       // When set, appends the AHRS attitude (yaw, pitch,
                           // roll) fields to the end of the status output
                           // message.
    MAG_CAL = 0x04,        // When set, appends magnetometer calibration and
                           // buffer fields to the end of the status output
                           // message.
    ACC_CAL = 0x08,        // When set, appends accelerometer calibration and
                           // limits fields to the end of the status output
                           // message.
    AHRS_RAW_DATA = 0x10,  // When set, appends raw sensor data fields to the
                           // end of the status output message.
    AHRS_COMP_DATA = 0x20, // When set, appends compensated sensor data fields
                           // to the end of the status output message.
};

/**
 * ENV_FLAGS_E : Used in SETTINGS_T type.
 */
enum ENV_FLAGS_E : uint8_t {
    AUTO_VOS = 0x01,          // When this flag is true, the velocity-of-sound
                              // used in range timing equations is
                              // automatically computed form the current water
                              // pressure, temperature and manually specified
                              // salinity.  VOS is calculated using the Coppens
                              // 1981 equation where temperature is valid over
                              // 0°C to 45°C, salinity over 0ppt to 35ppt and
                              // depth over 0m to 4000m.
    AUTO_PRESSURE_OFS = 0x02, // When this flag is true, the pressure offset is
                              // automatically chosen using the minimum
                              // observed pressure reading when the beacon is
                              // in less than 3m of water (0.3 bar). The
                              // assumption is than when fitted to an ROV this
                              // value will be seen on deck after the ROV is
                              // powered up, but if power is cycled when the
                              // beacon is below 3m, the pressure offset will
                              // not be updated.
};

/**
 * AHRS_FLAGS_E : Used in SETTINGS_T type.
 */
enum AHRS_FLAGS_E : uint8_t {
    AUTO_CAL_MAG = 0x01, // When this bit is true, automatic (dynamic)
                         // calibration of the magnetometer is enabled. In this
                         // mode, the magnetic field surrounding the beacon is
                         // continuously samples as the beacon is rotated
                         // through space, and every 30s a new calibration is
                         // attempted. If the results are better than the
                         // current calibration, then the new coefficientsi are
                         // accepted.
};

/**
 * XCVR_FLAGS_E : Used in SETTINGS_T type.
 */
enum XCVR_FLAGS_E : uint8_t {
    USBL_USE_AHRS = 0x01,      // When this flag is true the acoustic
                               // transceiver will use the current AHRS
                               // attitude (updated internally at a 50Hz rate)
                               // when resolving relative positions of remote
                               // beacons to the local beacon. When the flag is
                               // false, the fixed attitude specified in the
                               // XCVR_YAW, XCVR_PITCH and XCVR_ROLL fields
                               // will be used.
    XCVR_POSFLT_ENABLE = 0x02, // When this flag is true, the position filter
                               // is enabled to mark potentially erroneous
                               // acoustic USBL fixes based on velocity and
                               // angular movement limits.
    XCVR_USBL_MSGS = 0x20,     // When this flag is true, a CID_XCVR_USBL
                               // status message is generated on successfully
                               // reception of an acoustic message containing
                               // USBL signal information.
    XCVR_FIX_MSGS = 0x40,      // When this flag is true, a CID_XCVR_FIX status
                               // message will be generated on successful
                               // reception of an acoustic response message.
                               // The fix message contains details relating to
                               // distance, position and depth of the remote
                               // beacon.
    XCVR_DIAG_MSGS = 0x80,     // When this flag is true a series of diagnostic
                               // status messages will be generated by
                               // triggering events processed by the acoustic
                               // transceiver for further details see the
                               // following commands (CID_XCVR_TX_MSG,
                               // CID_XCVR_RX_ERR, CID_XCVR_RX_MSG,
                               // CID_XCVR_RX_REQ, CID_XCVR_RX_RESP,
                               // CID_XCVR_RX_RESP_ERROR,
                               // CID_XCVR_RX_UNHANDLED)
};

enum XCVR_TXMSGCTRL_E : uint8_t {
    XCVR_TXMSG_ALLOW_ALL = 0x0,  // Allow transmission of all messages
    XCVR_TXMSG_BLOCK_RESP = 0x1, // Block transmission of response messages. Automatic
                                 // transmission of Response Messages after a Request
                                 // message is received are blocked.
    XCVR_TXMSG_BLOCK_ALL = 0x3,  // Block transmission of all messages. Transmit
                                 // commands function as normal except no physical
                                 // transmission is started.
};

enum ACOFIX_FLAGS : uint8_t {
    POSITION_FLT_ERROR = 0x10,  // If this bit is true, it indicates the position filter has identified
                                // that the position specified in the fix may be invalid based on
                                // the beacons previous position, the define beacons motion
                                // limits and the time since last communication. However, the
                                // position fields still contain the USBL computed position and it
                                // is up to the user if they wish to reject this fix, or use it in some
                                // direct or weighted fashion.
    POSITION_ENHANCED = 0x08,   // If this bit is set, it indicates the Position fix has been computed
                                // from an Enhanced USBL return – this means the Depth will be
                                // the value from the remote beacons depth sensor rather than
                                // computed form the incoming signal angle.
    POSITION_VALID = 0x04,      // If this bit is set, it indicates the record contains the Position fields
    USBL_VALID = 0x02,          // If this bit is set, it indicates the record contains the USBL fields
    RANGE_VALID = 0x01,         // If this bit is set, it indicates the record contains the Range fields
};



inline std::ostream& operator<<(std::ostream& os, narval::seatrac::BAUDRATE_E rate)
{
    using namespace narval::seatrac;
    switch(rate) {
        case BAUD_4800   : os << "BAUD_4800";   break;
        case BAUD_9600   : os << "BAUD_9600";   break;
        case BAUD_14400  : os << "BAUD_14400";  break;
        case BAUD_19200  : os << "BAUD_19200";  break;
        case BAUD_38400  : os << "BAUD_38400";  break;
        case BAUD_57600  : os << "BAUD_57600";  break;
        case BAUD_115200 : os << "BAUD_115200"; break;
        default: os << "Unknown Baudrate";
    }
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const narval::seatrac::BID_E& beaconId)
{
    if(beaconId == narval::seatrac::BEACON_ALL)
        os << "BEACON_ALL";
    else if(beaconId <= 15)
        os << "BEACON_" << (int)beaconId;
    else
        os << "BEACON_UNKNOWN";
    return os;
}

inline std::ostream& operator<<(std::ostream& os, narval::seatrac::ENV_FLAGS_E flags)
{
    std::ostringstream oss;
    if(flags & narval::seatrac::AUTO_VOS)          oss << " | AUTO_VOS";
    if(flags & narval::seatrac::AUTO_PRESSURE_OFS) oss << " | AUTO_PRESSURE_OFS";
    if(oss.str().size() > 2)
        os << oss.str().substr(3);
    else
        os << "None";
    return os;
}

inline std::ostream& operator<<(std::ostream& os, narval::seatrac::AHRS_FLAGS_E flags)
{
    if(flags & narval::seatrac::AUTO_CAL_MAG)
        os << "AUTO_CAL_MAG enabled";
    else
        os << "AUTO_CAL_MAG disabled";
    return os;
}

inline std::ostream& operator<<(std::ostream& os, narval::seatrac::XCVR_FLAGS_E flags)
{
    std::ostringstream oss;

    if(flags & narval::seatrac::USBL_USE_AHRS)      oss << " | USBL_USE_AHRS";
    if(flags & narval::seatrac::XCVR_POSFLT_ENABLE) oss << " | XCVR_POSFLT_ENABLE";
    if(flags & narval::seatrac::XCVR_USBL_MSGS)     oss << " | XCVR_USBL_MSGS";
    if(flags & narval::seatrac::XCVR_FIX_MSGS)      oss << " | XCVR_FIX_MSGS";
    if(flags & narval::seatrac::XCVR_DIAG_MSGS)     oss << " | XCVR_DIAG_MSGS";

    if(oss.str().size() > 2)
        os << oss.str().substr(3);
    else
        os << "None";
    return os;
}

inline std::ostream& operator<<(std::ostream& os, narval::seatrac::CID_E cid)
{
    using namespace narval::seatrac;
    switch(cid) {
         default: os << "Unknown CID : " << (uint8_t)cid;             break;
         case CID_SYS_ALIVE:          os << "CID_SYS_ALIVE";          break;
         case CID_SYS_INFO:           os << "CID_SYS_INFO";           break;
         case CID_SYS_REBOOT:         os << "CID_SYS_REBOOT";         break;
         case CID_SYS_ENGINEERING:    os << "CID_SYS_ENGINEERING";    break;
         case CID_PROG_INIT:          os << "CID_PROG_INIT";          break;
         case CID_PROG_BLOCK:         os << "CID_PROG_BLOCK";         break;
         case CID_PROG_UPDATE:        os << "CID_PROG_UPDATE";        break;
         case CID_STATUS:             os << "CID_STATUS";             break;
         case CID_STATUS_CFG_GET:     os << "CID_STATUS_CFG_GET";     break;
         case CID_STATUS_CFG_SET:     os << "CID_STATUS_CFG_SET";     break;
         case CID_SETTINGS_GET:       os << "CID_SETTINGS_GET";       break;
         case CID_SETTINGS_SET:       os << "CID_SETTINGS_SET";       break;
         case CID_SETTINGS_LOAD:      os << "CID_SETTINGS_LOAD";      break;
         case CID_SETTINGS_SAVE:      os << "CID_SETTINGS_SAVE";      break;
         case CID_SETTINGS_RESET:     os << "CID_SETTINGS_RESET";     break;
         case CID_CAL_ACTION:         os << "CID_CAL_ACTION";         break;
         case CID_AHRS_CAL_GET:       os << "CID_AHRS_CAL_GET";       break;
         case CID_AHRS_CAL_SET:       os << "CID_AHRS_CAL_SET";       break;
         case CID_XCVR_ANALYSE:       os << "CID_XCVR_ANALYSE";       break;
         case CID_XCVR_TX_MSG:        os << "CID_XCVR_TX_MSG";        break;
         case CID_XCVR_RX_ERR:        os << "CID_XCVR_RX_ERR";        break;
         case CID_XCVR_RX_MSG:        os << "CID_XCVR_RX_MSG";        break;
         case CID_XCVR_RX_REQ:        os << "CID_XCVR_RX_REQ";        break;
         case CID_XCVR_RX_RESP:       os << "CID_XCVR_RX_RESP";       break;
         case CID_XCVR_RX_UNHANDLED:  os << "CID_XCVR_RX_UNHANDLED";  break;
         case CID_XCVR_USBL:          os << "CID_XCVR_USBL";          break;
         case CID_XCVR_FIX:           os << "CID_XCVR_FIX";           break;
         case CID_XCVR_STATUS:        os << "CID_XCVR_STATUS";        break;
         case CID_PING_SEND:          os << "CID_PING_SEND";          break;
         case CID_PING_REQ:           os << "CID_PING_REQ";           break;
         case CID_PING_RESP:          os << "CID_PING_RESP";          break;
         case CID_PING_ERROR:         os << "CID_PING_ERROR";         break;
         case CID_ECHO_SEND:          os << "CID_ECHO_SEND";          break;
         case CID_ECHO_REQ:           os << "CID_ECHO_REQ";           break;
         case CID_ECHO_RESP:          os << "CID_ECHO_RESP";          break;
         case CID_ECHO_ERROR:         os << "CID_ECHO_ERROR";         break;
         case CID_NAV_QUERY_SEND:     os << "CID_NAV_QUERY_SEND";     break;
         case CID_NAV_QUERY_REQ:      os << "CID_NAV_QUERY_REQ";      break;
         case CID_NAV_QUERY_RESP:     os << "CID_NAV_QUERY_RESP";     break;
         case CID_NAV_ERROR:          os << "CID_NAV_ERROR";          break;
         case CID_NAV_QUEUE_SET:      os << "CID_NAV_QUEUE_SET";      break;
         case CID_NAV_QUEUE_CLR:      os << "CID_NAV_QUEUE_CLR";      break;
         case CID_NAV_QUEUE_STATUS:   os << "CID_NAV_QUEUE_STATUS";   break;
         case CID_NAV_STATUS_SEND:    os << "CID_NAV_STATUS_SEND";    break;
         case CID_NAV_STATUS_RECEIVE: os << "CID_NAV_STATUS_RECEIVE"; break;
         case CID_DAT_SEND:           os << "CID_DAT_SEND";           break;
         case CID_DAT_RECEIVE:        os << "CID_DAT_RECEIVE";        break;
         case CID_DAT_ERROR:          os << "CID_DAT_ERROR";          break;
         case CID_DAT_QUEUE_SET:      os << "CID_DAT_QUEUE_SET";      break;
         case CID_DAT_QUEUE_CLR:      os << "CID_DAT_QUEUE_CLR";      break;
         case CID_DAT_QUEUE_STATUS:   os << "CID_DAT_QUEUE_STATUS";   break;
    }
    return os;
}

inline std::ostream& operator<<(std::ostream& os, narval::seatrac::CST_E statusCode)
{
    using namespace narval::seatrac;
    switch(statusCode) {
        case CST_OK:                    os << "CST_OK";                    break;
        case CST_FAIL:                  os << "CST_FAIL";                  break;
        case CST_EEPROM_ERROR:          os << "CST_EEPROM_ERROR";          break;
        case CST_CMD_PARAM_MISSING:     os << "CST_CMD_PARAM_MISSING";     break;
        case CST_CMD_PARAM_INVALID:     os << "CST_CMD_PARAM_INVALID";     break;
        case CST_PROG_FLASH_ERROR:      os << "CST_PROG_FLASH_ERROR";      break;
        case CST_PROG_FIRMWARE_ERROR:   os << "CST_PROG_FIRMWARE_ERROR";   break;
        case CST_PROG_SECTION_ERROR:    os << "CST_PROG_SECTION_ERROR";    break;
        case CST_PROG_LENGTH_ERROR:     os << "CST_PROG_LENGTH_ERROR";     break;
        case CST_PROG_DATA_ERROR:       os << "CST_PROG_DATA_ERROR";       break;
        case CST_PROG_CHECKSUM_ERROR:   os << "CST_PROG_CHECKSUM_ERROR";   break;
        case CST_XCVR_BUSY:             os << "CST_XCVR_BUSY";             break;
        case CST_XCVR_ID_REJECTED:      os << "CST_XCVR_ID_REJECTED";      break;
        case CST_XCVR_CSUM_ERROR:       os << "CST_XCVR_CSUM_ERROR";       break;
        case CST_XCVR_LENGTH_ERROR:     os << "CST_XCVR_LENGTH_ERROR";     break;
        case CST_XCVR_RESP_TIMEOUT:     os << "CST_XCVR_RESP_TIMEOUT";     break;
        case CST_XCVR_RESP_ERROR:       os << "CST_XCVR_RESP_ERROR";       break;
        case CST_XCVR_RESP_WRONG:       os << "CST_XCVR_RESP_WRONG";       break;
        case CST_XCVR_PLOAD_ERROR:      os << "CST_XCVR_PLOAD_ERROR";      break;
        case CST_XCVR_STATE_STOPPED:    os << "CST_XCVR_STATE_STOPPED";    break;
        case CST_XCVR_STATE_IDLE:       os << "CST_XCVR_STATE_IDLE";       break;
        case CST_XCVR_STATE_TX:         os << "CST_XCVR_STATE_TX";         break;
        case CST_XCVR_STATE_REQ:        os << "CST_XCVR_STATE_REQ";        break;
        case CST_XCVR_STATE_RX:         os << "CST_XCVR_STATE_RX";         break;
        case CST_XCVR_STATE_RESP:       os << "CST_XCVR_STATE_RESP";       break;
        case CST_DEX_SOCKET_ERROR:      os << "CST_DEX_SOCKET_ERROR";      break;
        case CST_DEX_RX_SYNC:           os << "CST_DEX_RX_SYNC";           break;
        case CST_DEX_RX_DATA:           os << "CST_DEX_RX_DATA";           break;
        case CST_DEX_RX_SEQ_ERROR:      os << "CST_DEX_RX_SEQ_ERROR";      break;
        case CST_DEX_RX_MSG_ERROR:      os << "CST_DEX_RX_MSG_ERROR";      break;
        case CST_DEX_REQ_ERROR:         os << "CST_DEX_REQ_ERROR";         break;
        case CST_DEX_RESP_TMO_ERROR:    os << "CST_DEX_RESP_TMO_ERROR";    break;
        case CST_DEX_RESP_MSG_ERROR:    os << "CST_DEX_RESP_MSG_ERROR";    break;
        case CST_DEX_RESP_REMOTE_ERROR: os << "CST_DEX_RESP_REMOTE_ERROR"; break;
        default:                        os << "Unknown status code";       break;
    }
    return os;
}

inline std::ostream& operator<<(std::ostream& os, narval::seatrac::AMSGTYPE_E msgType)
{
    using namespace narval::seatrac;
    switch(msgType) {
         default: os << "Unknown CID : " << (uint8_t)msgType;             break;
         case MSG_OWAY:             os << "MSG_OWAY";           break;
         case MSG_OWAYU:            os << "MSG_OWAYU";          break;
         case MSG_REQ:              os << "MSG_REQ";            break;
         case MSG_RESP:             os << "MSG_RESP";           break;
         case MSG_REQU:             os << "MSG_REQU";           break;
         case MSG_RESPU:            os << "MSG_RESPU";          break;
         case MSG_REQX:             os << "MSG_REQX";           break;
         case MSG_RESPX:            os << "MSG_RESPX";          break;
         case MSG_UNKNOWN:          os << "MSG_UNKNOWN";        break;
    }
    return os;
}

inline std::ostream& operator<<(std::ostream& os, narval::seatrac::STATUS_BITS_E flags)
{
    using namespace narval::seatrac;
    os << "\n-   ENVIRONMENT    : " << ((ENVIRONMENT     & flags) ? '1' : '0')
       << "\n-   ATTITUDE       : " << ((ATTITUDE        & flags) ? '1' : '0')
       << "\n-   MAG_CAL        : " << ((MAG_CAL         & flags) ? '1' : '0')
       << "\n-   ACC_CAL        : " << ((ACC_CAL         & flags) ? '1' : '0')
       << "\n-   AHRS_RAW_DATA  : " << ((AHRS_RAW_DATA   & flags) ? '1' : '0')
       << "\n-   AHRS_COMP_DATA : " << ((AHRS_COMP_DATA  & flags) ? '1' : '0');
    return os;
}

inline narval::seatrac::STATUS_BITS_E operator|(narval::seatrac::STATUS_BITS_E lhs,
                                                narval::seatrac::STATUS_BITS_E rhs)
{
    return static_cast<narval::seatrac::STATUS_BITS_E>(
        static_cast<uint8_t>(lhs) | static_cast<uint8_t>(rhs));
}

inline std::ostream& operator<<(std::ostream& os, narval::seatrac::STATUSMODE_E mode)
{
    using namespace narval::seatrac;
    switch(mode) {
        case STATUS_MODE_MANUAL: os << "STATUS_MODE_MANUAL"; break;
        case STATUS_MODE_1HZ:    os << "STATUS_MODE_1HZ";    break;
        case STATUS_MODE_2HZ5:   os << "STATUS_MODE_2HZ5";   break;
        case STATUS_MODE_5HZ:    os << "STATUS_MODE_5HZ";    break;
        case STATUS_MODE_10HZ:   os << "STATUS_MODE_10HZ";   break;
        case STATUS_MODE_25HZ:   os << "STATUS_MODE_25HZ";   break;
        default:                 os << "Unknown mode";       break;
    };
    return os;
}

inline std::ostream& operator<<(std::ostream& os, narval::seatrac::NAV_QUERY_E flags)
{
    std::ostringstream oss;

    if(flags & narval::seatrac::QRY_DATA)       oss << " | QRY_DATA";
    if(flags & narval::seatrac::QRY_ATTITUDE)   oss << " | QRY_ATTITUDE";
    if(flags & narval::seatrac::QRY_TEMP)       oss << " | QRY_TEMP";
    if(flags & narval::seatrac::QRY_SUPPLY)     oss << " | QRY_SUPPLY";
    if(flags & narval::seatrac::QRY_DEPTH)      oss << " | QRY_DEPTH";

    if(oss.str().size() > 2)
        os << oss.str().substr(3);
    else
        os << "None";
    return os;
}

}; //namespace seatrac
}; //namespace narval

#endif //_DEF_SEATRAC_DRIVER_SEATRAC_ENUMS_H_
