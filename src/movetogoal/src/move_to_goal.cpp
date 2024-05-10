#include "ros/ros.h"
#include <move_base_msgs/MoveBaseAction.h>
#include "actionlib/client/simple_action_client.h"

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;


int main(int argc,char** argv)
{

    ros::init(argc,argv,"Simple_move_Nav");
    MoveBaseClient movetogoal("move_base",true);
    while(!movetogoal.waitForServer(ros::Duration(5.0))){
        ROS_INFO("Wait for server");

    }
    move_base_msgs::MoveBaseGoal goal;

    goal.target_pose.header.frame_id="map";
    goal.target_pose.header.stamp=ros::Time::now();


    float goals [4][4]={{-1.5600,-1.5899,0.72,0.6938},{-1.539,1.6800,0.99,0.2-628},{1.5300,1.599,-0.7071,0.7071},{1.6999,-1.6,-0.9997,0.02323}};


    for(int i=0;i<4;i++){
        goal.target_pose.pose.position.x=goals[i][0];
        goal.target_pose.pose.position.y=goals[i][1];
        goal.target_pose.pose.orientation.z=goals[i][2];
        goal.target_pose.pose.orientation.w=goals[i][3];

        movetogoal.sendGoal(goal);
        ROS_INFO("Goal Has been Sent");
        movetogoal.waitForResult();
        ros::Duration(0.5).sleep();
    }

  if(movetogoal.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
    ROS_INFO("Robot is moved to all the node");
  else
    ROS_INFO("Robot Failed");

  return 0;



  



    
}