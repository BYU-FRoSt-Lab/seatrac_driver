cmake_minimum_required(VERSION 3.10)
project(seatrac_driver VERSION 1.1)

# find_package(rtac_asio REQUIRED)
find_package(rtac_asio QUIET)
if(NOT TARGET rtac_asio)
    include(FetchContent)
    FetchContent_Declare(rtac_asio
        GIT_REPOSITORY https://github.com/pnarvor/rtac_asio.git
        GIT_TAG        master
    )
    FetchContent_MakeAvailable(rtac_asio)
endif()

list(APPEND seatrac_driver_headers
    include/seatrac_driver/SeatracEnums.h
    include/seatrac_driver/SeatracTypes.h
    include/seatrac_driver/print_utils.h

    include/seatrac_driver/SeatracClient.h
    include/seatrac_driver/SeatracDriver.h
    include/seatrac_driver/DataWaiter.h

    include/seatrac_driver/commands.h
    include/seatrac_driver/Calibration.h
    include/seatrac_driver/messages/MessageBase.h
    include/seatrac_driver/messages/Messages.h

    include/seatrac_driver/messages/SysAlive.h
    include/seatrac_driver/messages/SysInfo.h
    include/seatrac_driver/messages/SysReboot.h

    include/seatrac_driver/messages/Status.h
    include/seatrac_driver/messages/StatusConfigGet.h
    include/seatrac_driver/messages/StatusConfigSet.h

    include/seatrac_driver/messages/SettingsGet.h
    include/seatrac_driver/messages/SettingsSet.h
    include/seatrac_driver/messages/SettingsLoad.h
    include/seatrac_driver/messages/SettingsSave.h
    include/seatrac_driver/messages/SettingsReset.h

    include/seatrac_driver/messages/PingSend.h
    include/seatrac_driver/messages/PingReq.h
    include/seatrac_driver/messages/PingResp.h
    include/seatrac_driver/messages/PingError.h

    include/seatrac_driver/messages/DataSend.h
    include/seatrac_driver/messages/DataReceive.h
    include/seatrac_driver/messages/DataError.h
    include/seatrac_driver/messages/DataQueueSet.h

    include/seatrac_driver/messages/EchoSend.h
    include/seatrac_driver/messages/EchoReq.h
    include/seatrac_driver/messages/EchoResp.h
    include/seatrac_driver/messages/EchoError.h

    include/seatrac_driver/messages/NavQuerySend.h
    include/seatrac_driver/messages/NavQueryReq.h
    include/seatrac_driver/messages/NavQueryResp.h
    include/seatrac_driver/messages/NavError.h

    include/seatrac_driver/messages/XcvrAnalyse.h
    include/seatrac_driver/messages/XcvrStatus.h
    include/seatrac_driver/messages/XcvrReceptionError.h
)

add_library(seatrac_driver SHARED
    src/SeatracClient.cpp
    src/SeatracDriver.cpp
    src/DataWaiter.cpp
)
target_include_directories(seatrac_driver PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)
target_link_libraries(seatrac_driver PUBLIC
    rtac_asio
)

rtac_install_target(seatrac_driver
    HEADER_FILES ${seatrac_driver_headers}
)

add_subdirectory(tests)



