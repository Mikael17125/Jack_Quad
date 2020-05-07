#ifndef JACK_CONTROLLER_H_
#define JACK_CONTROLLER_H_

#include "ros/ros.h"
#include "boost/thread.hpp"
#include "std_msgs/String.h"

#include "jack_framework_common/motion_module.h"

class JackController : public Singleton<JackController>
{
private:
    boost::thread queue_thread_;
    boost::thread gazebo_thread_;
    boost::mutex queue_mutex_;
    

    std::list<MotionModule*> motion_modules_;
    
    void gazeboTimerThread();
    void msgQueueThread();

    bool is_timer_running_;

public:
    std::string gazebo_robot_name_;
    ros::Publisher test_pub;
    JackController();
    bool initialize();
    void process();
    void addMotionModule(MotionModule *module);
    void startTimer();
    void gazeboJointStatesCallback(const std_msgs::String::ConstPtr &msg);

};

#endif