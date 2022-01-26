#!/usr/bin/python3
# -*- coding: UTF-8 -*-

''' 
    ---
    Exemplo 01 - Simple Thread
    ---

import threading

def worker():
    print("Hello, world!")


for i in range(5):
    thread = threading.Thread(target=worker)
    thread.start()
'''

''' 
    ---
    Threads com passagem de parâmetros    
    ---    

import threading

def worker(text, num):
    print("%s %d" %(text, num))


for i in range(5):
    thread = threading.Thread(
        target=worker, 
        args=("Esse é o texto", i)
    )
    thread.start()
'''

''' 
    ---
    Craiar Threads por meio de Classes
    ---    


import threading

class WorkerClass(threading.Thread):
    def __init__(self):
        super(WorkerClass, self).__init__()
    
    def run(self):
        print("Hello, bro!")


for i in range(5):
    thread = WorkerClass()
    thread.start()

'''

''' 
    ---
    Craiar Threads por meio de Classes com passagem de parâmetros
    ---    


import threading

class WorkerClass(threading.Thread):
    def __init__(self, text, num):
        super(WorkerClass, self).__init__()
        self.text = text
        self.num = num
    
    def run(self):
        print("%s %d" %(self.text, self.num))


for i in range(5):
    thread = WorkerClass("Thread: ", i)
    thread.start()

'''

''' 
    ---
    Craiar Threads por meio de Classes com passagem de parâmetros e Timer
    ---    

import threading
import time

thread_list = []

class WorkerClass(threading.Thread):
    def __init__(self, text, num):
        super(WorkerClass, self).__init__()
        self.text = text
        self.num = num
    
    def run(self):
        print("%s %d" %(self.text, self.num))


for i in range(5):
    thread = WorkerClass("Thread: ", i)
    thread_list.append(thread)
    # thread.start()

for thread_ in thread_list:
    thread_.start()
    # thread_.join()

print("Início...")

'''


''' 
    ---
    Encerrar Threads
    ---    

import threading
import time

thread_list = []

class WorkerClass(threading.Thread):
    def __init__(self, text, num):
        super(WorkerClass, self).__init__()
        self.text = text
        self.num = num
        self.__stop = threading.Event()
    
    def run(self):
        while True:
            if self.__stop.isSet():
                print("%s %d FIM...\n" %(self.text, self.num))
                return
            print("%s %d" %(self.text, self.num))
            time.sleep(1)
    
    def stop(self):
        self.__stop.set()


for i in range(5):
    thread = WorkerClass("Thread: ", i)
    thread_list.append(thread)
    thread.start()

for thread_ in thread_list:
    thread_.stop()

print("Início...")

'''

''' 
    ---
    Sincronizar Threads
    ---    

import threading 
import time

event = threading.Event();

def task_1():
    print("1.");
    print("2.");
    event.wait(); 
    print("6.");
    event.clear();

def task_2():
    print("3.");
    time.sleep(3);
    print("4.");
    print("5.");
    event.set();

thread = threading.Thread(target=task_1);
thread.start();

thread = threading.Thread(target=task_2);
thread.start();

event.wait(); 
print("\nfim")

'''

''' 
    --- 
    Sincronizar Threads com Lock()
    ---    


import threading
import time


lock = threading.Lock();

# Variável Global;
counter = 0;

class WorkerClass(threading.Thread):
    def __init__(self):
        super(WorkerClass, self).__init__();

    def run(self):
        # use 'global' para ter acesso a variável global;
        global counter;

        time.sleep(1);
        lock.acquire()
        counter = counter + 1;
        print("\n%d" %(counter));
        lock.release()

for i in range(5):
    thread = WorkerClass();
    thread.start(); 
    #thread.join();

print("Inicio...");

'''

''' 
    --- 
    Cllback e Threads
    ---    
'''

import threading
import time

class Console(threading.Thread):
    def __init__( self, callback, *args ):
        threading.Thread.__init__( self, target=callback, args=args );
        self.start();

def callback( string, num ):
    print( "%s: %d" %(string, num) );
    time.sleep(1);

def main(): 
    for i in range(5):   
        thread = Console( callback, "Thread", i );
        if thread.isAlive():
            print("\nalive");

if __name__ == '__main__':
    main();