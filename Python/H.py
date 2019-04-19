class BinarySearchTree:

    def __init__(self, root = None, main = True):
        self.root = root
        self.left = None
        self.right = None
        self.main = main
        
    def append(self, value):
        if self.root is None:
            self.root = value
        else:
            if value <= self.root:
                if self.left is None:
                    self.left = BinarySearchTree(value, main = False)
                else:
                    self.left.append(value)
            else:
                if self.right is None:
                    self.right = BinarySearchTree(value, main = False)
                else:
                    self.right.append(value)
                                    
    def child_items(self,level):
        if level == 0:
            return [self.root]
        else:
            left = []
            right = []
            
            if self.left is not None:
                left = self.left.child_items(level-1)
            
            if self.right is not None:
                right = self.right.child_items(level-1)
                
            return left+right 
            
    def __contains__(self, item):
        if self.left is not None:
            if item in self.left:
                return True
        if self.right is not None:
            if item in self.right:
                return True
            
        if self.root == item:
            return True
        else:
            return False
                
    def __iter__(self):
        result = []
        i = 0
        flag = True
        
        if self.root == None:
            return iter(result)
        
        while flag:
            if (self.child_items(i) == []):
                flag = False
            else:
                for item in self.child_items(i):
                    yield item
                
                i += 1