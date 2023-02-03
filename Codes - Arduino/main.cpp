#include <iostream>
#include<dos.h>
using namespace std;

int main() {


    //states = ["waiting", "get_floor_to_go", "move_to_start", "load_passengers", "close_door", "compute_floor",
    //        "leave_to_destination", "open_door", "close_door"]

    int go_up = 0;
    int go_down = 0;
    int curent_floor = 0;
    std::string current_state = "waiting";
    std::string next_state = "";
    int door_open = 0;

    int emergency_alert = 0;


    int start_floor = 0;
    int destination_floor = 0;

    //Event e


    while (true) {

        while (true) {

            if (current_state == "waiting") {
                if(emergency_alert == 1){
                    break;
                }
                door_open = 0;
                //if gets floor number to go:
                next_state = "get_floor_to_go";
            } else if (current_state == "get_floor_to_go") {
                if(emergency_alert == 1){
                    break;
                }
                //get start floor
                start_floor = 123;
                next_state = "move_to_start";

            } else if (current_state == "move_to_start") {
                if(emergency_alert == 1){
                    break;
                }
                if (curent_floor > start_floor) {
                    go_up = 0;
                    go_down = 1;
                    curent_floor -= 1;
                    next_state = "move_to_start";
                } else if (curent_floor < start_floor) {
                    if(emergency_alert == 1){
                        break;
                    }
                    go_down = 0;
                    go_up = 1;
                    curent_floor += 1;
                    next_state = "move_to_start";
                } else if (curent_floor == start_floor) {
                    if(emergency_alert == 1){
                        break;
                    }
                    go_down = 0;
                    go_up = 0;
                    go_down = 0;
                    next_state = "load_passengers";
                }
            } else if (current_state == "load_passengers") {
                if(emergency_alert == 1){
                    break;
                }
                door_open = 1;
                //wait seconds
                delay(5000);
                next_state = "close_door";
            } else if (current_state == "close_door") {
                if(emergency_alert == 1){
                    break;
                }
                door_open = 0;
                next_state = "compute_floor";
            } else if (current_state == "compute_floor") {
                if(emergency_alert == 1){
                    break;
                }
                //todo update destination floor
                destination_floor = 123;
                next_state = "leave_to_destination";
            } else if (current_state == "leave_to_destination") {
                if(emergency_alert == 1){
                    break;
                }

                if (curent_floor > destination_floor) {
                    go_up = 0;
                    go_down = 1;
                    curent_floor -= 1;
                    delay(1000);
                    next_state = "leave_to_destination";
                } else if (curent_floor < destination_floor) {
                    go_down = 0;
                    go_up = 1;
                    curent_floor += 1;
                    delay(1000);
                    next_state = "leave_to_destination";
                } else if (curent_floor == destination_floor) {
                    go_up = 0;
                    go_down = 0;
                    next_state = "open_door";
                }
            } else if (current_state == "open_door") {
                if(emergency_alert == 1){
                    break;
                }
                door_open = 1;
                //wait seconds!!!
                delay(5000);
                next_state = "close_door";
            } else if (current_state == "close_door") {
                if(emergency_alert == 1){
                    break;
                }
                door_open = 0;
                next_state = "waiting";
            }
            current_state = next_state;
        }

        if (go_up == 1) {
            curent_floor += 1;
            delay(1000);
            go_up = 0;
        }
        if (go_down == 1) {
            curent_floor -= 1;
            delay(1000);
            go_down = 0;
        }

        door_open = 1;
        //wait few seconds
        delay(5000);
        door_open = 0;

        next_state = "waiting";
    }

}
























