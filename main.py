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
            continue
        if (line == ")"):
            flag = 0

        if (flag):
            result.append(line)
    return result

def extractInitLines(lines):
    result = []
    flag = 0
    for line in lines:
        if (len(line) > 13 and line[:15] == "(= (total-cost)"):
            flag = 1
            continue
        if (line == ")"):
            flag = 0

        if (flag):
            result.append(line[1:-1])
    
    return result

            


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
    
    #with open(outFile,'w') as o:
    #    for line in lines:
    #        o.write("Current line is:" + line)

def compile():
    extract()
    
compile()