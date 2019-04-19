def product(A, history = [], max_iter = -1, now = 0):
    if max_iter == -1:
        max_iter = len(A)
    
    if now != max_iter:
        for a in A[now]:
            yield from product(A, history = history + [a], max_iter = max_iter, now = now + 1)
    else:
        yield tuple([item for item in history])