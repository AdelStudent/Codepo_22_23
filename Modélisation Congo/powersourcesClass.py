class TimeUser():
    def __init__(self,name):
        self.temps = 0
        self.y = []
        self.name = name
    def adapthour(self, current_time):
        self.temps = current_time
    
    def getY(self):
        return self.y
    def getName(self) :
        return self.name #Protège le nom
    

class powersources (TimeUser): #powersources class fille de TimeUser 
    
    def __init__(self, name, Watt_gen, behavior) :
       super().__init__(name)
       self.max_power = Watt_gen
       self.puissance_gen = 0
       self.behavior = behavior
       # . attribut = paramètre de la fonction

    def getName(self) :
        return self.name #Protège le nom
    
    def getPower(self) :
        return self.puissance_gen
    
    def adapt_my_y(self):
        self.puissance_gen= self.max_power*self.behavior[self.temps%24]
        self.y.append(self.puissance_gen)
        print(self.y)

    