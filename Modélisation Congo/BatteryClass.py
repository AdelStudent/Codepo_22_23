from powersourcesClass import TimeUser
class Battery(TimeUser):
    def __init__(self,name, SOC, nbr_batt) :
       super().__init__(name)
       self.SOC = SOC #Ce sont des % (ref 200 Ah)
       self.SOCmin = 50
       self.SOCmax = 100.1
       self.SOCmin_list = []
       self.SOCmax_list = []
       self.bilan_list = []
       self.max_energy = 2880*nbr_batt #Wh 
    
    def get_bilan_list(self):
        return self.bilan_list
    
    def get_SOCmax_list(self):
        return self.SOCmax_list
    
    def get_SOCmin_list(self):
        return self.SOCmin_list
    
    def adaptSOC(self, input_energy, output_energy):
        bilan_energy = input_energy - output_energy
        new_SOC = self.SOC + self.convert_energy_to_SOC(bilan_energy)

        # Check if the new SOC exceeds 100%
        if new_SOC > 100:
            bilan_energy -= self.convert_SOC_to_energy(new_SOC - 100)
            new_SOC = 100

        # Check if the new SOC goes below 50%
        if new_SOC < 50:
            raise ValueError("SOC is below 50*%* - Error: Insufficient battery capacity!")

        # Update the SOC and bilan list
        self.SOC = new_SOC
        self.bilan_list.append(bilan_energy)

    def convert_SOC_to_energy(self, SOC_percentage):
        return SOC_percentage * self.max_energy / 100
        

    
    def convert_energy_to_SOC(self,bilan_energy):
        converted_value = bilan_energy/self.max_energy
        return converted_value
    
    def adapt_my_y(self):
        self.y.append(self.SOC)
        self.SOCmax_list.append(self.SOCmax)
        self.SOCmin_list.append(self.SOCmin)
        
        print(self.y)
        
        
        