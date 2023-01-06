
def count(lower):
    dct = {}
    for i in lower:
        if i not in dct.keys():
            dct[i] = 1
        else :
            dct[i] += 1
    return dct

def trans(before):
    after = ""
    for i in before:
        if i.isupper():
            after += i.lower()
        else:
            after += i.upper()
    return after

while (1):
    before = input("Input:")
    if before == "STOP":
        print("Bye")
        break
        
    lower = before.lower()
    dct = count(lower)
    
    for i in dct.keys():
        print("({} : {})   ".format(i, dct[i]), end="")
    
    print("")
    print(trans(before))
    
    
    
