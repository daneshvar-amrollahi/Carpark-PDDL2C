import sys
inFile = sys.argv[1]
outFile = sys.argv[2]

def extract():
    with open(inFile,'r') as i:
        lines = i.readlines()
        for line in lines:
            print("Current line is ", line)

def compile():
    extract()
    
compile()