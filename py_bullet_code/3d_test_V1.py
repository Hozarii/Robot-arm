import pybullet as p
import time
import math
from math import *
from pickle import TRUE
from time import time, sleep

from win32api import EnumDisplayDevices, EnumDisplaySettings, GetKeyState

# Non-standard imports (pip install might be needed)
from graphics import *

from pyautogui import position as mousePos
import keyboard



physics_client = p.connect(p.GUI)

p.resetDebugVisualizerCamera(1.0, 90, -40, (0, 0, 0))

p.setGravity(0,0,-9.81)
p.setRealTimeSimulation(0)

p.loadURDF("plane.urdf",[0,0,0],[0,0,0,1])
urdf_file = p.loadURDF("test_visual3d.urdf",[0,0,0],[0,0,0,1],useFixedBase = True)
robot_id = urdf_file
# p.setJointMotorControlArray(robot_id, range(0), p.POSITION_CONTROL,targetPositions=[0.1] * 6)

# les 6 axes
base_joint1_index = 0
joint1_joint2_index = 1
joint3_joint4_index = 2
joint4_joint5_index = 3
joint5_joint6_index = 4

# Sliders des joints
base_slider = p.addUserDebugParameter("Base Joint", -3.14, 3.14, 0.0)
shoulder_slider = p.addUserDebugParameter("Shoulder Joint", -0.09, 1.3, 0.0)
elbow_slider = p.addUserDebugParameter("Elbow Joint", -3.14, 3.14, 0.0)

# rot_slider = p.addUserDebugParameter("Rot Joint", -3.14, 3.14, 0.0)
# tilt_slider = p.addUserDebugParameter("Tilt Joint", -1.57, 0, 0.0)

      



while True:
    # Lecture sliders
    base_joint_angle = p.readUserDebugParameter(base_slider)
    shoulder_joint_angle = p.readUserDebugParameter(shoulder_slider)
    elbow_joint_angle = p.readUserDebugParameter(elbow_slider)
    # rot_joint_angle = p.readUserDebugParameter(rot_slider)
    # tilt_joint_angle = p.readUserDebugParameter(tilt_slider)


    p.resetJointState(robot_id, base_joint1_index, targetValue=base_joint_angle, targetVelocity = 0)
    p.resetJointState(robot_id, joint1_joint2_index, targetValue=shoulder_joint_angle, targetVelocity = 0)
    p.resetJointState(robot_id, joint3_joint4_index, targetValue=elbow_joint_angle, targetVelocity = 0)
    # p.resetJointState(robot_id, joint4_joint5_index, targetValue=rot_joint_angle, targetVelocity = 0)
    # p.resetJointState(robot_id, joint5_joint6_index, targetValue=tilt_joint_angle, targetVelocity = 0)
   
    p.stepSimulation()
    

    time.sleep(1.0 / 500.0)
    if keyboard.is_pressed('esc'):
        win.close()

p.disconnect()