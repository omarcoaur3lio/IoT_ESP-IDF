#! /usr/bin/python3
# -*- coding: utf-8 -*-

class Vector:
    __name = "Result: "
    var_public = "I'm public var"

    def __init__(self):
        self.__var = 1234
    
    def get(self):
        return self.__name + str(self.__var)

num = Vector()
print(num.var_public)

# Mesmo sendo privada, ainda assim é possível acessar o seu conteúdo. Esta forma de acesso deve ser evitada.
print(num._Vector__var)

print(num.get())
