import re

def pr(el, tam = 10):
    print(f'make {el[1]:.<{tam}}: {el[0]}')

def getMakefile():
    
    with open('Makefile', 'r') as f:
        txt = f.readlines()

    return txt

def getH():

    H = []
    txt = getMakefile()

    iscommand = False
    patt_comment = re.compile(f'^#\s.+')
    patt_command = re.compile(r'^[\w-].+(?=:)')
    h = ['', '']

    for t in txt:
        # find comment for makefile command
        if match := patt_comment.match(t):
            iscommand = True
            h[0] = re.sub(r'(#\s+)|(\n)', '', match.string)
            continue
            
        # find command
        if iscommand and (match := patt_command.match(t)):
            iscommand = False
            h[1] = re.sub(r':?\n', '', match.string)
            H.append([*h])
            
    return H

def getDefault():
    txt = getMakefile()
    
    default = ''
    for t in txt:
        if match := re.match(r'^all:.*', t):
            default = re.sub(r'(\n)|(all:\s*)', '', match.string)
            
    return default

if __name__ == "__main__":
    
    H = getH()
    default = getDefault()
    
    tam = -1
    for h in H:
        tam = max(tam, len(h[1]))
    
    tam += 1
    
    print(' ')
    print(f'default : ({default})')
    print(' ')
    for h in H:
        pr(h, tam)