import pybullet as p
import time
import math
import numpy as np
from math import *
import keyboard

DEG2RAD = math.pi/180.0
RAD2DEG = 180.0/math.pi


flag_axe = 0



physics_client = p.connect(p.GUI)

p.resetDebugVisualizerCamera(1.0, 90, -40, (0, 0, 0))

p.setGravity(0,0,-9.81)
p.setRealTimeSimulation(0)

p.loadURDF("plane.urdf",[0,0,0],[0,0,0,1])
urdf_file = p.loadURDF("test_visual3d.urdf",[0,0,0],[0,0,0,1],useFixedBase = True)
robot_id = urdf_file

# les 6 axes
base_joint1_index = 0
joint1_joint2_index = 1
joint3_joint4_index = 2
joint4_joint5_index = 3
joint5_joint6_index = 4

# anciennne valeur

last_base_joint_angle = 0
last_shoulder_joint_angle = 0
last_elbow_joint_angle = 0
last_rot_joint_angle = 0
last_tilt_joint_angle = 0

# Sliders des joints
base_slider = p.addUserDebugParameter("Base Joint", -180, 180, 0.0)
shoulder_slider = p.addUserDebugParameter("Shoulder Joint", 0, 95, 0)
elbow_slider = p.addUserDebugParameter("Elbow Joint", 0, 135, 0.0)
rot_slider = p.addUserDebugParameter("Rot Joint", -180, 180, 0.0)
tilt_slider = p.addUserDebugParameter("Tilt Joint", 0, 90, 0.0)



def draw_axes(index) :
    joint_info= p.getJointInfo(robot_id,index)
    joint_pose = p.getLinkState(robot_id, joint_info[0])[:2]
    joint_pose = p.getLinkState(robot_id, joint_info[0])[:2]

    # Dessiner les axes du joint
    length = 0.1  # Longueur des axes
    x_axis = np.array([length, 0, 0])
    y_axis = np.array([0, length, 0])
    z_axis = np.array([0, 0, length])

    p.addUserDebugLine(joint_pose[0], joint_pose[0] + x_axis, [1, 0, 0], 2, 1)
    p.addUserDebugLine(joint_pose[0], joint_pose[0] + y_axis, [0, 1, 0], 2, 1)
    p.addUserDebugLine(joint_pose[0], joint_pose[0] + z_axis, [0, 0, 1], 2, 1)


def draw_axes_all(flag):
    if keyboard.is_pressed('r') and flag == 1:
        return 0
    if keyboard.is_pressed('s') or flag == 1 :
        draw_axes(base_joint1_index)
        draw_axes(joint1_joint2_index)
        draw_axes(joint3_joint4_index)
        draw_axes(joint4_joint5_index)
        draw_axes(joint5_joint6_index)
        return 1



while True:

    # Lecture sliders
    base_joint_angle = p.readUserDebugParameter(base_slider)*DEG2RAD
    shoulder_joint_angle = -p.readUserDebugParameter(shoulder_slider)*DEG2RAD+1.3
    elbow_joint_angle = - p.readUserDebugParameter(elbow_slider)*DEG2RAD + 1.57
    rot_joint_angle = p.readUserDebugParameter(rot_slider)*DEG2RAD 

    max_tilt = abs( elbow_joint_angle*2.7- 1.57*2.7 ) + ( exp(abs(rot_joint_angle))*0.3 -0.3)
    tilt_joint_angle = p.readUserDebugParameter(tilt_slider)*DEG2RAD

    if tilt_joint_angle > max_tilt : 
        tilt_joint_angle = max_tilt

    # print(base_joint_angle)
    # print((shoulder_joint_angle-1.3)*(-1))
    # print((elbow_joint_angle-last_elbow_joint_angle - 1.57)*(-1))
    # print(rot_joint_angle-last_rot_joint_angle)
    # print((tilt_joint_angle-last_tilt_joint_angle)*(-1))
    # print(abs(max_tilt))

    if keyboard.is_pressed('a'):
        print((base_joint_angle-last_base_joint_angle)*(-1))
        print((shoulder_joint_angle-last_shoulder_joint_angle-1.3)*(-1))
        print((elbow_joint_angle-last_elbow_joint_angle- 1.57)*(-1))
        print((rot_joint_angle-last_rot_joint_angle)*(-1))
        print((tilt_joint_angle-last_tilt_joint_angle)*(-1))
        last_base_joint_angle = base_joint_angle
        last_shoulder_joint_angle = shoulder_joint_angle-1.3
        last_elbow_joint_angle = elbow_joint_angle-1.57
        last_rot_joint_angle = rot_joint_angle
        last_tilt_joint_angle = tilt_joint_angle
        sleep(0.2)
        
    flag_axe=draw_axes_all(flag_axe)


   


    p.resetJointState(robot_id, base_joint1_index, targetValue=base_joint_angle, targetVelocity = 0)
    p.resetJointState(robot_id, joint1_joint2_index, targetValue=shoulder_joint_angle, targetVelocity = 0)
    p.resetJointState(robot_id, joint3_joint4_index, targetValue=elbow_joint_angle, targetVelocity = 0)
    p.resetJointState(robot_id, joint4_joint5_index, targetValue=rot_joint_angle, targetVelocity = 0)
    p.resetJointState(robot_id, joint5_joint6_index, targetValue=tilt_joint_angle, targetVelocity = 0)
   
    p.stepSimulation()
    

    time.sleep(1.0 / 500.0)
    if keyboard.is_pressed('esc'):
        win.close()
        p.disconnect()