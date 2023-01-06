
class Student():
    def __init__(self, num, name, kor, eng, math):
        self._num = num
        self._name = name
        self._kor = kor
        self._eng = eng
        self._math = math
        self._total = kor + eng + math
        self._avg = (kor + eng + math) / 3
        self._order = 0
    
    @property
    def num(self):
        return self._num
    
    @property
    def name(self):
        return self._name
    
    @property
    def kor(self):
        return self._kor
    
    @property
    def eng(self):
        return self._eng
    
    @property
    def math(self):
        return self._math
    
    @property
    def math(self):
        return self._total
    
    @property
    def avg(self):
        return self._avg
    
    @property
    def order(self):
        return self._order
