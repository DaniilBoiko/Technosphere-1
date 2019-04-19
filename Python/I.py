from copy import deepcopy

class FragileDict():
    def __init__(self, _data = {}):
        self._data = deepcopy(_data)
        self._lock = True
        
    def __getitem__(self, key):
        if self._lock:
            return deepcopy(self._data[key])
        else:
            return self._cache[key]
        
    def __setitem__(self, key, value):
        if not self._lock:
            self._cache[key] = value
        else:
            raise RuntimeError("Protected state")
            
    def __contains__ (self, key):
        if self._lock:
            if key in self._data:
                return key
            else:
                return False
        else:
            if key in self._cache:
                return key
            else:
                return False
            
    def __enter__(self, data = None):
        self._lock = False
        
        if data:
            self._data = data
        if not self._data:
            self._data = {}
            
        self._cache = deepcopy(self._data)
        return self
        
    def __exit__(self, exc_type, exc_value, traceback):
        self._lock = True
        if exc_type is not None:
            print("Exception has been suppressed.")
        else:
            self._data = deepcopy(self._cache)
            
        delattr(self, '_cache')
        return True