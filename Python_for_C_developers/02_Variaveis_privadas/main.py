#! /usr/bin/python3
# -*- coding: utf-8 -*-

class Vector:
    def __init__(self):
        self.__var = 123 # Variável privada
    
    def get(self):
        return self.__var

num = Vector()

# print(num.__var) # Erro: A variável é privada e não está acessível

# O método get é um wrapper que possibilita a leitura da variável privada
print(num.get())