# Made by Magnus Harder 2021 
# This program makes a random graph :)

import random as rm
from time import sleep
import os

def printGraph(m, n):
    arr = makeGraph(m, n)

    for i in range(m, 0, -1):
        string = ""
        for j in range(n):
            if arr[j] >= i:
                string += "#"
            else: string += " "
        print(string)



def makeGraph(m, n):
    arr = []
    for i in range(n):
        arr.append(rm.randint(0, m))
    return arr

while(True):
    os.system('clear')
    printGraph(25, 100)
    sleep(0.2)


#print("Welcome to Graph Maker!")
#printGraph(int(input("Height: ")), int(input("Width:")))