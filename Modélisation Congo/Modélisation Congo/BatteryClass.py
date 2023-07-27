from powersourcesClass import TimeUser
class Battery(TimeUser):
    def __init__(self,name, SOC, nbr_batt) :
       super().__init__(name)
       self.SOC = SOC #Ce sont des % (ref 200 Ah)
       self.SOCmin = 30
       self.SOCmax = 70
       self.SOCmin_list = []
       self.SOCmax_list = []
       
       self.bilan_list = []


       self.max_energy = 2400*nbr_batt #Wh 
    
    def get_bilan_list(self):
        return self.bilan_list
    def get_SOCmax_list(self):
        return self.SOCmax_list
    def get_SOCmin_list(self):
        return self.SOCmin_list
    
    def adaptSOC(self, input_energy, output_energy):
        #print(f"Here's my old SOC : {self.SOC}")
        bilan_energy = input_energy - output_energy
        self.bilan_list.append(bilan_energy)

        self.SOC += self.convert_energy_to_SOC(bilan_energy)
        #print(f"Here's my new SOC : {self.SOC}")
        
    def getSOCminmax(self): # Pour le graphe 
        return [self.SOCmin,self.SOCmax]
    def convert_energy_to_SOC(self,bilan_energy):
        converted_value = bilan_energy/self.max_energy
        return converted_value
    def adapt_my_y(self):
        self.y.append(self.SOC)
        self.SOCmax_list.append(self.SOCmax)
        self.SOCmin_list.append(self.SOCmin)
        
        print(self.y)