def solution1(arg):
    return [i*4 for i in arg]

def solution2(arg):
    return [arg[i]*(i+1) for i in range(len(arg))]

def solution3(arg):
    return [i for i in arg if (i%3 == 0) or (i%5 ==0)]

def solution4(arg):
    return [i for j in arg for i in j]

def solution5(arg):
    return [(k,j,i) for i in range(arg+1) for j in range(i) for k in range(j) if (-i**2+j**2+k**2) == 0]

def solution6(arg):
    return [[i+j for j in arg[1]] for i in arg[0]]

def solution7(arg):
    return [[arg[j][i] for j in range(len(arg))] for i in range(len(arg[0]))]

def solution8(arg):
    return [list(map(int,i.split())) for i in arg]

def solution9(arg):
    return {k: v for k, v in zip('abcdefghijklmnopqrstuvwxyz'[:len(arg)], [i**2 for i in arg])}

def solution10(arg):
    return set([i.title() for i in arg if (len(i) > 3)])

solutions = {
    'solution1': solution1,
    'solution2': solution2,
    'solution3': solution3,
    'solution4': solution4,
    'solution5': solution5,
    'solution6': solution6,
    'solution7': solution7,
    'solution8': solution8,
    'solution9': solution9,
    'solution10': solution10,
}