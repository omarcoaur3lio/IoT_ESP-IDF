#!/usr/bin/python3
# -*- coding: UTF-8 -*-


# Classe Pai
class Uart( object ):

    def __init__( self, comport, baudrate ):
        self.__comport = comport;
        self.__baudrate = baudrate;
        self.buffersize = 100;

    def getComport( self ):
        return "Comport = " + str( self.__comport );

    def getBaudrate( self ):
        return "BaudRate = " + str( self.__baudrate );

    def getBufferSize( self ):
        return "BufferSize = " + str( self.buffersize );

# Classe filha		
class Serial( Uart ): 
    def __init__( self, comport, baudrate ):
        super( Serial, self ).__init__( comport, baudrate );	
        self.__baudrate = 19200;

    # A função getBaurate está sendo sobreescrita pela classe filha (Overriding)
    def getBaudrate( self ):
        return "BaudRate = " + str( self.__baudrate );

print( "-------------------------" );
# Acessando diretante a classe Uart;
t = Uart( 1, 9600 );
print( t.getComport() );
print( t.getBaudrate() );
print( t.getBufferSize() );

print( "-------------------------" );

# Acessando pela classe Interface Serial
y = Serial( 3, 115200 );
print( y.getComport() );
print( y.getBaudrate() );
print( y.getBufferSize() );
print( "-------------------------" );
