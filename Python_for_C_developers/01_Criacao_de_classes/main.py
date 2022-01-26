#! /usr/bin/python3
# -*- coding: utf-8 -*-

class Vector:
    def __init__(self, x = 0, y = 0):
        self.x = x
        self.y = y

    def get( self ):
        return self.x + self.y


num = Vector(15, 60)
print(num.get())