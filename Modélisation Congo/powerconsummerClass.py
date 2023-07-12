from powersourcesClass import TimeUser
 
class powerconsummer(TimeUser) :
    def __init__(self,name,puissance_con,behavior):
        super().__init__(name)
        self.max_power = puissance_con
        self.puissance_con = 0
        self.behavior = behavior
    
    def getName(self) :
        return self.name #Protège le nom
    
    def getPower(self) :
        return self.puissance_con 
    def adapt_my_y(self):
        self.puissance_con= self.max_power*self.behavior[self.temps%24]
        self.y.append(self.puissance_con)
        print(self.y)