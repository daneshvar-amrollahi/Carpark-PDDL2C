import sys
inFile = sys.argv[1]
outFile = sys.argv[2]

def readLines():
    with open(inFile,'r') as i:
        lines = i.readlines()
    
    result = [line.strip() for line in lines]
    return result

def extractObjects(lines):
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

def extract():
    lines = readLines()
    print("All lines: ")
    for line in lines:
        print(line)

    print("--------------")

    objects = extractObjects(lines)
    print("Object lines: ")
    for line in objects:
        print(line)
    
    #with open(outFile,'w') as o:
    #    for line in lines:
    #        o.write("Current line is:" + line)

def compile():
    extract()
    
compile()