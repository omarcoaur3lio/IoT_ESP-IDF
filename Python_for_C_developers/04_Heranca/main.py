#! /usr/bin/python3
# -*- coding: utf-8 -*-

# Classe Pai
class Uart(object):
    def __init__(self, comPort, baudRate):
        self.__comPort = comPort
        self.__baudRate = baudRate

    def getComPort(self):
        return self.__comPort

    def getBaudRate(self):
        return self.__baudRate

# Classe filha
class Serial(Uart):
    def __init__(self, comPort, baudRate):
        # super(Serial, self).__init__(comPort, baudRate)
        # ou
        super().__init__(comPort, baudRate)


num = Uart(1, 9600)
print(num.getComPort())
print(num.getBaudRate())

num = Serial(5, 115200)
print(num.getComPort())
print(num.getBaudRate())