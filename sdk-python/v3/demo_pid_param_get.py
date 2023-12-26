import fi_fsa
import time

server_ip_list = ["192.168.137.10", 
                  "192.168.137.11", 
                  "192.168.137.12", 
                  "192.168.137.13", 
                  "192.168.137.14", 
                  "192.168.137.30", 
                  "192.168.137.31", 
                  "192.168.137.32", 
                  "192.168.137.33", 
                  "192.168.137.34", ]


def main():
    # server_ip_list = fi_fsa.broadcast_func_with_filter(filter_type="Actuator")

    if server_ip_list:

        # get the communication configuration of all FAS
        for i in range(len(server_ip_list)):
            fi_fsa.get_pid_param(server_ip_list[i])

        print('\n')
        time.sleep(1)


if __name__ == '__main__':
    main()
