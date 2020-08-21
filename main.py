from errlib import *
import sys
inFile = sys.argv[1]
outFile = sys.argv[2]


def readLines():
    with open(inFile,'r') as i:
        lines = i.readlines()
    
    result = [line.strip() for line in lines]
    return result

def extractObjectLines(lines):
    result = []
    flag = 0
    for line in lines:
        if (line == "(:objects"):
            flag = 1
        
        if (line == ")"):
            flag = 0

        if (flag):
            result.append(line)

    return result[1:]

def extractInitLines(lines):
    result = []
    flag = 0
    for line in lines:
        if (line == "(:init"):
            flag = 1
            
        if (line == ")"):
            flag = 0

        if (flag):
            result.append(line[1:-1])
    
    return result[2:]

def extractGoalLines(lines):
    result = []
    flag = 0
    for line in lines:
        if (line == "(:goal"):
            flag = 1
        
        if (line == ")"):
            flag = 0

        if (flag):
            result.append(line[1:-1])

    return result[2:]


def extract():
    lines = readLines()
    print("All lines: ")
    for line in lines:
        print(line)

    print("--------------")

    objects = extractObjectLines(lines)
    print("Object lines: ")
    for line in objects:
        print(line)

    print("---------------")

    inits = extractInitLines(lines)
    print("Init lines: ")
    for line in inits:
        print(line)
    
    print("---------------")

    goals = extractGoalLines(lines)
    print("Goal lines: ")
    for line in goals:
        print(line)

    return (objects, inits, goals)
    

def writeToFile():
    with open(outFile,'w') as o:
        o.write("#include <math.h>\n#include <klee/klee.h>")
        


def compile():
    objects, inits, goals = extract()
    writeToFile()
    
compile()