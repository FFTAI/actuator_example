#include "Fsa.h"
#include <vector>
#include <thread>
#include <chrono>
#include <iostream>
#include "broccoli/core/Time.hpp"
#include <fstream>
#include <sstream>
#include <cstring>
#include <atomic>
#include <list>
#include <unistd.h>

#include "../include/udpJsonData.h"
#include "../include/udp_s.hpp"

using namespace std;
using namespace FSA_CONNECT;
using namespace udpServer::Server;
std::ofstream log_file("../log/test_kt_2_23_200.txt");

bool flag_actuator_ip = false;
bool flag_first_cur = false;
bool flag_second_cur = false;
bool flag_vertify_cur = false;

void cycle_loop_recv_udp(void (*fun_pt)(), double cycle_time_s){
    broccoli::core::Time timer;
    broccoli::core::Time start_time;
    broccoli::core::Time end_time;
    broccoli::core::Time last_time;
    broccoli::core::Time time_to_sleep;
    broccoli::core::Time cycle_time{0, cycle_time_s*1e9};
    timespec time_to_sleep_std;
    while (1)
    {
        start_time = timer.currentTime();
        fun_pt();
        time_to_sleep = start_time + cycle_time;
        time_to_sleep_std = time_to_sleep.toTimeSpec();
        last_time = start_time;
        clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &time_to_sleep_std, NULL);
    }
};

void udpserver(){
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(PORT);
    bind(server_sock, (sockaddr*)&server_address, sizeof(server_address));

    memset(&client_address, 0, sizeof(client_address));
    client_address.sin_family = AF_INET;
    client_address.sin_addr.s_addr = htonl(INADDR_ANY);
    client_address.sin_port = htons(0);
}
void recv_cur_mode()
{
    std::cout << "已进入： " << std::endl;
    ssize_t recv_len = recvfrom(server_sock, client_buffer, sizeof(client_buffer), 0, (sockaddr*)&client_address, &client_address_len);
    std::cout << "长度为： " << recv_len << std::endl;
    client_buffer[recv_len] = '\0';
    std::string recv_mess_str;
    json recv_mess_json;
    recv_mess_str = std::string(client_buffer);
    std::cout << "消息内容： " << recv_mess_str << std::endl;
    recv_mess_json = json::parse(recv_mess_str);
    if (recv_mess_json.contains("actuator_ip"))
    {
        std::string ip = recv_mess_json.at("actuator_ip");
        std::cout << "当前获得的ip为  " << ip << std::endl;
        flag_actuator_ip = true;
        // send to actuator
        const std::string json_j = "abcde";
        int nbytes = sendto(server_sock, json_j.c_str(), json_j.size(), 0, (struct sockaddr*)&client_address, sizeof(client_address));
    }
    if (recv_mess_json.contains("first_current") and flag_actuator_ip)
    {
        double first_current = recv_mess_json.at("first_current");
        std::cout << "the first current is : " << first_current << std::endl;
        flag_first_cur = true;
    }
    if (recv_mess_json.contains("second_current") and flag_first_cur)
    {
        double second_current = recv_mess_json.at("second_current");
        std::cout << "the second current is : " << second_current << std::endl;
        flag_second_cur = true;
    }
    if (recv_mess_json.contains("vertify_current") and flag_second_cur)
    {
        double vertify_current = recv_mess_json.at("vertify_current");
        std::cout << "the vertify current is : " << vertify_current << std::endl;
        vertify_current = true;
    }
}

int main()
{
    udpserver();
    std::thread recv_mode_thread(cycle_loop_recv_udp, recv_cur_mode, 0.0025);
    recv_mode_thread.join();
    // double cycle_time_s = 0.0025;
    // broccoli::core::Time timer;
    // broccoli::core::Time start_time;
    // broccoli::core::Time end_time;
    // broccoli::core::Time last_time;
    // broccoli::core::Time time_to_sleep;
    // broccoli::core::Time cycle_time{0, cycle_time_s*1e9};
    // timespec time_to_sleep_std;

    // FSAConfig::FSAPIDParams pidparam;
    // FSA single_act;
    // std::string ip_str;
    // std::cout <<"请输入电机ip: " << std::endl;
    // std::cin >> ip_str;
    // single_act.init(ip_str);
    // single_act.Enable();
    // std::this_thread::sleep_for(std::chrono::seconds(1));
    // double start_t = 0;
    // double cur_pos, cur_vel, cur_cur;
    // double des_pos = 0, des_vel = 0, des_cur_1 = 0, des_cur_2 = 0;
    // single_act.EnablePosControl();
    // std::this_thread::sleep_for(std::chrono::seconds(1));

    // std::cout << "请输入第一次下发的小电流： " << std::endl;
    // std::string cur_1_str;
    // std::cin >> cur_1_str;
    // std::istringstream iss_cur_1(cur_1_str);
    // double num_cur_1;
    // iss_cur_1 >> num_cur_1;
    
    // // double kt = 0.257;
    // // des_cur = (20.0/7)/kt;
    // // des_cur = 20;
    // broccoli::core::Time start_time_1;
    // start_time_1 = timer.currentTime();
    // while (timer.currentTime() - start_time_1 < 15)
    // {
    //     start_time = timer.currentTime();
    //     time_to_sleep = start_time + cycle_time;
    //     time_to_sleep_std = time_to_sleep.toTimeSpec();

    //     single_act.SetPosition(des_pos, des_vel, num_cur_1);
    //     single_act.GetPVC(cur_pos, cur_vel, cur_cur);
    //     log_file << start_t << " " << des_pos << " " << des_vel << " " << num_cur_1 << " " << cur_pos << " " << cur_vel << " " << cur_cur << std::endl;
    //     start_t += cycle_time_s;
    //     clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &time_to_sleep_std, NULL);
    // }
    // std::cout << "第一次下发的小电流结束....." << std::endl;

    // std::cout << "请输入第二次下发的大电流： " << std::endl;
    // std::string cur_2_str;
    // std::cin >> cur_2_str;
    // std::istringstream iss_cur_2(cur_2_str);
    // double num_cur_2;
    // iss_cur_2 >> num_cur_2;

    // broccoli::core::Time start_time_2;
    // start_time_2 = timer.currentTime();
    // while (timer.currentTime() - start_time_2 < 15)
    // {
    //     start_time = timer.currentTime();
    //     time_to_sleep = start_time + cycle_time;
    //     time_to_sleep_std = time_to_sleep.toTimeSpec();

    //     single_act.SetPosition(des_pos, des_vel, num_cur_2);
    //     single_act.GetPVC(cur_pos, cur_vel, cur_cur);
    //     log_file << start_t << " " << des_pos << " " << des_vel << " " << num_cur_2 << " " << cur_pos << " " << cur_vel << " " << cur_cur << std::endl;
    //     start_t += cycle_time_s;
    //     clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &time_to_sleep_std, NULL);
    // }
    // std::cout << "第二次下发的大电流结束....." << std::endl;
    // single_act.SetPosition(des_pos, des_vel, 0);
    // std::string first_cur;
    // std::cout << "请输入读到的第一次电流值： " << std::endl;
    // std::cin >> first_cur;
    // std::istringstream iss_read_cur_1(first_cur);
    // double read_cur_1;
    // iss_read_cur_1 >> read_cur_1;

    // std::string second_cur;
    // std::cout << "请输入读到的第二次电流值： " << std::endl;
    // std::cin >> second_cur;
    // std::istringstream iss_read_cur_2(second_cur);
    // double read_cur_2;
    // iss_read_cur_2 >> read_cur_2;

    // double delta_cur;
    // delta_cur = read_cur_2 - read_cur_1;

    // std::string delta_torque;
    // std::cout << "请输入两次的扭矩差： " << std::endl;
    // std::cin >> delta_torque;
    // std::istringstream iss_delta_torque(delta_torque);
    // double num_delta_torque;
    // iss_delta_torque >> num_delta_torque;

    // std::string ratio_str;
    // std::cout << "请输入执行器的减速比： " << std::endl;
    // std::cin >> ratio_str;
    // std::istringstream iss_ratio_str(ratio_str);
    // double num_ratio;
    // iss_ratio_str >> num_ratio;

    // double kt = ((num_delta_torque)/(delta_cur)) / num_ratio;
    // std::cout << "执行器的电流扭矩系数为：   "  <<  kt << std::endl;

    // std::string verify_torque;
    // std::cout << "请输入验证环节的扭矩： " << std::endl;
    // std::cin >> verify_torque;
    // std::istringstream iss_verify_torque(verify_torque);
    // double num_verify_torque;
    // iss_verify_torque >> num_verify_torque;

    // double torque_cur = (num_verify_torque/num_ratio)/kt;
    // broccoli::core::Time start_time_3;
    // start_time_3 = timer.currentTime();
    // while (timer.currentTime() - start_time_3 < 15)
    // {
    //     start_time = timer.currentTime();
    //     time_to_sleep = start_time + cycle_time;
    //     time_to_sleep_std = time_to_sleep.toTimeSpec();

    //     single_act.SetPosition(des_pos, des_vel, torque_cur);
    //     single_act.GetPVC(cur_pos, cur_vel, cur_cur);
    //     log_file << start_t << " " << des_pos << " " << des_vel << " " << torque_cur << " " << cur_pos << " " << cur_vel << " " << cur_cur << std::endl;
    //     start_t += cycle_time_s;
    //     clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &time_to_sleep_std, NULL);
    // }
    // std::this_thread::sleep_for(std::chrono::seconds(1));
    // single_act.SetPosition(0, 0, 0);
}