def solution1(arg):
    import re
    return list(map(lambda x: int(str(re.sub('[^0-9]','', x))[::-1]), arg))

def solution2(arg):
    return list(map(lambda x: x[0]*x[1], arg))

def solution3(arg):
    return list(filter(lambda x: (x%6 in [0,2,5]), arg))

def solution4(arg):
    return list(filter(bool, arg))

def solution5(rooms):
    from operator import setitem
    rooms = list(map(lambda x: setitem(x,'square',x['width']*x['length']),rooms))
    return rooms

def solution6(arg):
    return list(map(lambda x: {**x,**{'square': x['width']*x['length']}},arg))

def solution7(arg):
    from functools import reduce
    return reduce(lambda a,x: set.intersection(a,x),arg)

def solution8(arg):
    from functools import reduce
    return dict(list(map(lambda num: (num,reduce(lambda x,a: x+(1 if a == num else 0), arg,0)), list(set(arg)))))

def solution9(arg):
    return list(map(lambda x: x['name'],filter(lambda x: x['gpa'] > 4.5,arg)))

def solution10(arg):
    return list(filter(lambda x: sum(map(int,(x[1::2]))) == sum(map(int,(x[0::2]))), arg))

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