import re

pattern_rgb = re.compile(r'^#(?:[0-9A-F]{2}){3}$')
pattern_hsl = re.compile(r'^hsl\((?:360|3[0-5][0-9]|[12][0-9][0-9]|[1-9]?[0-9]) *\, *(?:100|[1-9]?[0-9])% *\, *(?:100|[1-9]?[0-9])%\)$') #listo
pattern_directory = re.compile(r'^(?:[A-Z]:\\|∼\\|\.\\|(?:\.\.\\)+)(?:\w(?:[^\\/:*?"><|])*\\)*(?:\w(?:[\w.])*)$') #listo
pattern_mail = re.compile(r'^[a-zA-Z0-9!#$%&’*+\-/=?\^_‘{|}~](?:[a-zA-Z0-9!#$%&’*+\-/=?\^_‘{|}~]|(?<!\.)\.)*[a-zA-Z0-9!#$%&’*+\-/=?\^_‘{|}~]@(?:[a-zA-Z0-9\-])+(?:\.(?:\w|\-)+)+$')
pattern_pascal = re.compile(r'^{(?:[0-9]|[1-9](?:[0-9])+)(?:\s([0-9]|[1-9](?:[0-9])+))*}$')
pattern_time = re.compile(r'^(?:[0-9]){4}\-(?:0[1-9]|[1-9]|1[0-2])\-(?:0[1-9]|[0-9]|[1-2][0-9]|3[01])$')
pattern_xdson = re.compile(r'^(( *[a-zA-Z]+ *)=( *\"[a-zA-Z0-9]+\" *)|( *[a-zA-Z]+ *)=( *\'[a-zA-Z0-9]+\' *)|( *[a-zA-Z]+ *)=( *[0-9]+ *)|( *[a-zA-Z]+ *)=( *\[(\"[a-zA-Z0-9]+\"|\'[a-zA-Z0-9]+\'|[0-9]+)(,(\"[a-zA-Z0-9]+\"|\'[a-zA-Z0-9]+\'|[0-9]+))*\] *))(,((( *[a-zA-Z]+ *)=( *\"[a-zA-Z0-9]+\" *)|( *[a-zA-Z]+ *)=( *\'[a-zA-Z0-9]+\' *)|( *[a-zA-Z]+ *)=( *[0-9]+ *)|( *[a-zA-Z]+ *)=( *\[(\"[a-zA-Z0-9]+\"|\'[a-zA-Z0-9]+\'|[0-9]+)(,(\"[a-zA-Z0-9]+\"|\'[a-zA-Z0-9]+\'|[0-9]+))*\] *))))*$')
pattern_xdson2 = re.compile(r'^<(( *[a-zA-Z]+ *)=( *\"[a-zA-Z0-9]+\" *)|( *[a-zA-Z]+ *)=( *\'[a-zA-Z0-9]+\' *)|( *[a-zA-Z]+ *)=( *[0-9]+ *)|( *[a-zA-Z]+ *)=( *\[(\"[a-zA-Z0-9]+\"|\'[a-zA-Z0-9]+\'|[0-9]+)(,(\"[a-zA-Z0-9]+\"|\'[a-zA-Z0-9]+\'|[0-9]+))*\] *))(,((( *[a-zA-Z]+ *)=( *\"[a-zA-Z0-9]+\" *)|( *[a-zA-Z]+ *)=( *\'[a-zA-Z0-9]+\' *)|( *[a-zA-Z]+ *)=( *[0-9]+ *)|( *[a-zA-Z]+ *)=( *\[(\"[a-zA-Z0-9]+\"|\'[a-zA-Z0-9]+\'|[0-9]+)(,(\"[a-zA-Z0-9]+\"|\'[a-zA-Z0-9]+\'|[0-9]+))*\] *))))*>$')

def gen(string):
    stack = []
    contador = 0
    for i, c in enumerate(string):
        if(c == '=' and contador > 0):
            contador -= 1
        if c == '<':
            contador += 1
            stack.append(i)
        elif c == '>' and stack:
            start = stack.pop()
            print(re.match(pattern_xdson,string[start + 1: i]))
            if(re.match(pattern_xdson,string[start + 1: i]) == None):
                return False
            if(contador == 0):
                string = string[:start] + '1' + string[i+1:]
            else:
                string = string[:start] + 'hola = 1' + string[i+1:]
            return string
    return False

def xdson(string):
    contador = 0
    for i in string:
        if i == '<':
            contador += 1
    while contador > 1:
        string = gen(string)
        print(string)
        if(string == False):
            return False
        contador -= 1
    print(string)
    if(re.match(pattern_xdson2,string)):
        return True
    return False

def leap(year):
    if year == 0:
        return False
    if year % 4 == 0 and year % 100 != 0 or year % 400 == 0:
        return True
    return False

def time(t):
    t = t.split("-")
    t = list(map(int,t))
    if(t[1] == 1 or t[1] == 3 or t[1] == 5 or t[1] == 7 or t[1] == 8 or t[1] == 10 or t[1] == 12):
        if(t[2] <= 31):
            return True
    elif(t[1] == 4 or t[1] == 6 or t[1] == 9 or t[1] == 11):
        if(t[2] <= 30):
            return True
    else:
        if(leap(t[0])):
            if(t[2] <= 29):
                return True
        else:
            if(t[2] <= 28):
                return True
    return False
    

def pascal(l):

    l = l.replace("{","")
    l = l.replace("}","")
    l = l.split()
    l = list(map(int,l))

    a = [1]
    for i in range(len(l)-1):
        a.append(int(a[i]*(len(l)-i-1)/(i+1)))
    if a == l:
        return True
    return False
    

def p(string):
    if(re.match(pattern_rgb,string)):
        print("RGB")
    elif(re.match(pattern_hsl,string)):
        print("HSL")
    elif(re.match(pattern_directory,string)):
        print("Directorio")
    elif(re.match(pattern_mail,string)):
        print("Correo")
    elif(re.match(pattern_pascal,string) and pascal(string)):
        print("Pascal")
    elif(re.match(pattern_time,string) and time(string)):
        print("Fecha")
    else:
        print("No pertenece al lenguaje")



file = open("palabras.txt","r")
for i in file:
    i = i.strip()
    print(xdson(i))
file.close()
