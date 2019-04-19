def brackets(n, n_open = 0, n_close = 0, ans = ''):
    if n > 0:
        if n_open == n_close:
            yield from brackets(n-0.5, n_open + 1 , n_close, ans + '(')
        
        if n_open > n_close:
            yield from brackets(n-0.5, n_open + 1 , n_close, ans + '(')
            yield from brackets(n-0.5, n_open, n_close + 1, ans + ')')
    else:
        if n_open == n_close:
            yield (ans)
            
if __name__ == "__main__":
    a = input()
    for i in brackets(int(a)):
        print(i)
