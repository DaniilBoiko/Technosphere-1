import functools
import time
from datetime import datetime, timedelta

def timeout(rps):
    def _timeout(func):
        @functools.wraps(func)
        def wrapper(*args):
            #print("Entered")
            current = time.time()
            output = func(*args)
            diff = 1/rps-(time.time()-current)
            if diff > 0:
                time.sleep(diff)
            return output
        return wrapper
    return _timeout