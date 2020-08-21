import sys
inFile = sys.argv[1]
outFile = sys.argv[2]


class CompileError(Exception):
    def __init__(self, message):
        self.message = message
    def __str__(self):
        return self.message

class ObjectNotFound(CompileError):
    def __init__(self):
        self.message = "OBJECT NOT FOUND!"

class PredicateNotFound(CompileError):
    def __init__(self):
        self.message = "PREDICATE NOT FOUND!"


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
    #with open(outFile,'w') as o:
    #    for line in lines:
    #        o.write("Current line is:" + line)

def writeToFile():
    pass

def compile():
    extract()
    writeToFile()
    
compile()