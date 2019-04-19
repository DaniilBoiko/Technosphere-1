import functools

def counter(func):
    func.rdepth = 0
    func.ncalls = 0
    func.now = -1
    
    @functools.wraps(func)
    def wrapper(*args, **kwargs):
        if wrapper.now == -1:
            wrapper.ncalls = 0
            wrapper.now = 0
            wrapper.rdepth = 0

        wrapper.now += 1
        wrapper.rdepth = max(wrapper.rdepth,wrapper.now)
        result = func(*args, **kwargs)        
        wrapper.now -= 1

        wrapper.ncalls += 1
        if wrapper.now == 0:
            wrapper.now = -1
            
        return result
    
    return wrapper