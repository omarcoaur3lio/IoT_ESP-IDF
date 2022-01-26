#!/usr/bin/python3
# -*- coding: UTF-8 -*-

class Uart( object ):
	def __init__( self, comport, baudrate ):
		self.comport = comport;
		self.baudrate = baudrate;

print("---------------------------------------");
t = Uart( 10, 10 );

if id( t.comport ) == id( t.baudrate ):
	print( "Os IDs das Variáveis são Iguais:" );
else:
	print( "Os IDs das Variáveis são diferentes!" );

print( type( t.comport ) );
print( type( t.baudrate ) );
print( "t.comport:  " + str( id( t.comport ) ) );
print( "t.baudrate: " + str( id( t.baudrate ) ) );

print("---------------------------------------");

t = Uart( 46, 10 );

if id( t.comport ) == id( t.baudrate ):
	print( "Os IDs das Variáveis são Iguais:" );
else:
	print( "Os IDs das Variáveis são diferentes!" );

print(type(t.comport));
print(type(t.baudrate));
print("t.comport:  " + str(id(t.comport)) );
print("t.baudrate: " + str(id(t.baudrate)) );