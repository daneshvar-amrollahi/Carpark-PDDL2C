import sys
inFile = sys.argv[1]
outFile = sys.argv[2]

def readLines():
    with open(inFile,'r') as i:
        lines = i.readlines()
    
    result = [line.strip() for line in lines]
    return result

def extract():
    lines = readLines()
    for line in lines:
        print(line)
    #with open(outFile,'w') as o:
    #    for line in lines:
    #        o.write("Current line is:" + line)

def compile():
    extract()
    
compile()