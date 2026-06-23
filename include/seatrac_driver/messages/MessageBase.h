#ifndef _DEF_SEATRAC_DRIVER_MESSAGES_MESSAGE_BASE_H_
#define _DEF_SEATRAC_DRIVER_MESSAGES_MESSAGE_BASE_H_

#include <iostream>
#include <type_traits>

#include <seatrac_driver/SeatracTypes.h>
#include <seatrac_driver/print_utils.h>

namespace narval { namespace seatrac { namespace messages {

// implementation involve the Curiously Recursive Template Pattern.
template <class T>
struct Message
{ 
    const CID_E msgId;

    Message() : msgId(T::Identifier) {}

    Message<T>& operator=(const std::vector<uint8_t>& other) {

        // This checks that the type T inherit from A<T>, i.e. is a Curriously
        // Recurring Template Pattern.
        static_assert(std::is_base_of<Message<T>,T>::value,
                      "T is not derived from Message<T> (search CRTP).");

        if(other.size() != sizeof(T)) {
            std::ostringstream oss;
            oss << "Wrong size to copy message from raw data (expected "
                << sizeof(T) << ", got " << other.size() << ")";
            throw std::runtime_error(oss.str());
        }

        memcpy(this, other.data(), sizeof(T));
        return *this;
    }
}__attribute__((packed));



template <typename T>
std::ostream& operator<<(std::ostream& os, const narval::seatrac::messages::Message<T>& msg)
{
    os << "Message :\n- msgId : " << msg.msgId;
    return os;
}

}; //namespace messages
}; //namespace seatrac
}; //namespace narval

#endif //_DEF_SEATRAC_DRIVER_MESSAGES_MESSAGE_BASE_H_

