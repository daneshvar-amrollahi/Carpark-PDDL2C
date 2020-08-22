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


def extractLines():
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
    

def writeIncludes():
    with open(outFile,'w') as o:
        o.write("#include <math.h>\n#include <klee/klee.h>\n\n")

def writeDefines(objects):
    with open(outFile,'a+') as o:
        o.write("#define numOfActions 4\n")
        
        for obj in objects:
            o.write("#define numOf{}s {}\n".format(obj[-1], len(obj) - 1))

        for obj in objects:
            for i in range(len(obj) - 1):
                o.write("#define {} {}\n".format(obj[i], i))
            o.write("\n")

def writeToFile(objects):
    writeIncludes()
    writeDefines(objects)
        
        

def extractObjectsFromLines(lines):
    result = []
    for line in lines:
        cur = list(line.split())
        result.append(cur[:-2] + cur[-1:])
    return result

def compile():
    objectLines, initLines, goalLines = extractLines()
    objects = extractObjectsFromLines(objectLines)
    print(objects)
    writeToFile(objects)
    
compile()