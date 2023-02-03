

states = ["waiting", "get_floor_to_go", "move_to_start", "load_passengers", "close_door", "compute_floor",
          "leave_to_destination", "open_door", "close_door"]

go_up = 0
go_down = 0
curent_floor = 0
current_state = states[0]
next_state = None
door_open = 0

##################################
start_floor = 0
destination_floor = 0

Event e


while(True):

    while(True):

        if(current_state == "waiting"):
            #todo close the door!
            #if gets floor number to go:
            next_state = "get_floor_to_go"
            #update start floor
        elif(current_state == "get_floor_to_go"):
            #get start floor
            a=1
        elif(current_state == "move_to_start"):
            if(curent_floor > start_floor):
                go_down = 1
                curent_floor -=1
                next_state = "move_to_start"

            elif(curent_floor < start_floor):
                go_up = 1
                curent_floor +=1
                next_state = "move_to_start"

            elif(curent_floor == start_floor):
                go_up = 0
                go_down = 0
                next_state = "load_passengers"

        elif (current_state == "load_passengers"):
            door_open = 1
            #wait seconds
            next_state = "close_door"

        elif (current_state == "close_door"):
            door_open = 0
            next_state = "compute_floor"

        elif (current_state == "compute_floor"):
            #update destination floor
            next_state = "leave_to_destination"
        elif (current_state == "leave_to_destination"):

            if (curent_floor > destination_floor):
                go_down = 1
                curent_floor -= 1
                next_state = "leave_to_destination"

            elif (curent_floor < destination_floor):
                go_up = 1
                curent_floor += 1
                next_state = "leave_to_destination"

            elif (curent_floor == destination_floor):
                go_up = 0
                go_down = 0
                next_state = "open_door"

        elif (current_state == "open_door"):
            door_open = 1
            #wait seconds!!!
            next_state = "close_door"

        elif (current_state == "close_door"):
            door_open = 0
            next_state = "waiting"

        current_state = next_state

    if(go_up == 1):
        a = 1
    if(go_down == 1):
        a = 1

    door_open = 1
    #wait few seconds
    door_open = 0






















