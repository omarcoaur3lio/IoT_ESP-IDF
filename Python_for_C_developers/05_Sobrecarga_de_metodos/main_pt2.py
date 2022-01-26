#!/usr/bin/python3
# -*- coding: UTF-8 -*-
# Exemplo1: Method Overrinding in Python

class Pai(object):
    def __init__(self):
        self.value = 5;

    def get_value(self):
        return self.value;

class Filha(Pai):
    pass;


f = Filha();
print( f.get_value() );

print( "--------------------------------");
p = Pai();
f = Filha();

print( "Objeto p (Pai):" );
print( dir(p) );

print( "--------------------------------");
print( "Objeto f (Filha):" );
print( dir(f) );

print( "--------------------------------");
print( "Classe Pai:" );
print( Pai.__dict__ );

print( "--------------------------------");
print( "Classe Filha:" );
print( Filha.__dict__ );
