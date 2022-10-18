name = "hyperlpr_python_pkg"
import sys
from .hyperlpr import LPR
import os
import time


# PR = LPR(os.path.join(os.path.split(os.path.realpath(__file__))[0],"models"))
# print(os.path.join(os.path.split(os.path.realpath(__file__))[0]))
#
#
# def HyperLPR_plate_recognition(Input_BGR,opt = None):
#     return PR.plate_recognition(Input_BGR,opt)
