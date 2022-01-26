#!/usr/bin/python3
# -*- coding: UTF-8 -*-

class Uart(object):
	def __init__(self, comport, baudrate):
		self.comport = comport;
		self.baudrate = baudrate;

print( "---------------------------------------" );
t = Uart( 10, 10 );
y = t;

if id(y) == id(t):
	print("Os IDs das Objetos são Iguais:");
else:
	print("Os IDs das Objetos são diferentes!");

print(type(y));
print(type(t));
print("y:  " + str(id(y)));
print("t:  " + str(id(t)));

print("---------------------------------------");

t = Uart(10,10);
y = Uart(10,10);

if id( y ) == id( t ):
	print( "Os IDs das Objetos são Iguais:" );
else:
	print( "Os IDs das Objetos são diferentes!" );

print( type( y ) );
print( type( t ) );
print( "y: " + str( id( y ) ) );
print( "t: " + str( id( t ) ) );

print( "---------------------------------------" );
