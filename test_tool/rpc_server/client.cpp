#include <cstdint>
#include <iostream>
#include <string>
#include <thread>
#include <utility>
#include <vector>
#include <iomanip>


#include <iostream>


#include "3rdparty/rpclib/include/rpc/client.h"
#include "3rdparty/rpclib/include/rpc/rpc_error.h"

static constexpr size_t BUFFER_SIZE = 2048;
uint8_t _buffer[BUFFER_SIZE] = {0};

// pose
struct Vector3f {
    float x_val = 0.0f;
    float y_val = 0.0f;
    float z_val = 0.0f;

    MSGPACK_DEFINE_MAP(x_val, y_val, z_val);
};

struct Vector3d {
    double x_val = 0.0f;
    double y_val = 0.0f;
    double z_val = 0.0f;

    MSGPACK_DEFINE_MAP(x_val, y_val, z_val);
};

struct Pose {
    Vector3d position;
    Vector3f rotation;
    MSGPACK_DEFINE_MAP(position, rotation);
};

struct VehicleState {
    int32_t id;
    int64_t time_stamp;
    Pose pose;
    int32_t gps_level;
    float steering_angle = 0.0f;
    float forward_speed = 0.0f;
    int32_t current_gear;

    MSGPACK_DEFINE_MAP(id, time_stamp, pose, gps_level, steering_angle,
                       forward_speed, current_gear);
};

rpc::client client_("10.0.169.228", 17771);


int32_t GetConnectionState()  {
    switch (client_.get_connection_state()) {
        case rpc::client::connection_state::connected:
            return 0;
        case rpc::client::connection_state::disconnected:
            return 1;
        case rpc::client::connection_state::initial:
            return 2;
        case rpc::client::connection_state::reset:
            return 3;
        default:
            return 4;
    }
}

int main() {


    client_.set_timeout(1000);
    VehicleState state_;
    std::string err_msg;
    int64_t ret;
    std::cout <<std::setiosflags(std::ios::fixed);


    std::cout << "Waiting for connection - " << std::flush;
    int32_t timeout = 20;
    while (GetConnectionState() != 0) {
        std::cout << "X" << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        if (--timeout <= 0) {
            std::cout << std::endl << "Connect timeout!" << std::endl;
            return 0;
        }
    }
    std::cout << std::endl << "Connected!" << std::endl;

    ret = 0;
    try {
        ret = client_.call("StartSim").as<int32_t>();
    }
    catch (rpc::rpc_error& e) {
        std::cout << "rpc_error" << std::endl;
        if (&err_msg != nullptr) *(&err_msg) = e.get_error().as<std::string>();
        ret = 0;
    }

    std::cout << "The StartSim result1 is: " << ret << std::endl;


    try{
        state_ = client_.call("GetVehicleState").as<VehicleState>();
    }
    catch (rpc::rpc_error& e) {
        std::cout << "rpc_error" << std::endl;
        if (&err_msg != nullptr) *(&err_msg) = e.get_error().as<std::string>();
        ret = 0;
    }

    //std::cout <<  client_.get_connection_state();
    ret = state_.time_stamp;

    memcpy(&_buffer,&state_, sizeof(VehicleState));

    VehicleState *st_cpy;
    st_cpy = reinterpret_cast< VehicleState* > (&_buffer);
    std::cout << "st_cpy " <<st_cpy->time_stamp << '\n';
    std::cout << "x_val is: " <<std::setprecision(8)<< st_cpy->pose.position.x_val << std::endl;

    if(state_.time_stamp > 0) {


        std::cout << "time_stamp is: " <<std::setprecision(8)<< state_.time_stamp << std::endl;
        std::cout << "The result1 is: " <<std::setprecision(8)<< state_.pose.position.x_val << std::endl;
        std::cout << "The result1 is: " <<std::setprecision(8)<< state_.pose.position.y_val << std::endl;
    }

    try{
        ret = client_.call("StopSim").as<int32_t>();
    }
    catch (rpc::rpc_error& e) {
        std::cout << "rpc_error" << std::endl;
        if (&err_msg != nullptr) *(&err_msg) = e.get_error().as<std::string>();
        ret = 0;
    }
    std::cout << "The StopSim result1 is: " << ret << std::endl;



    return 0;
}