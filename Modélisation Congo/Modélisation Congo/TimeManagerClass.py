from matplotlib.pylab import *

class TimeManager() :
    def __init__(self, temps, objetlist) : #init = constructeur 
        self.temps = temps 
        self.objetlist = objetlist
        self.x = []

    def adapthour(self):
        self.temps +=1
        self.x.append(self.temps)
        self.synchronize()

        input_energy,output_energy = self.adaptInputOutput()
        self.check_batteries(input_energy,output_energy)
        self.adapt_Y()


    def live_hours(self,nbr_iteration):
        for i in range(nbr_iteration):
            self.adapthour()
        self.displayAllGraphs()
    
    def synchronize(self):
        from powersourcesClass import TimeUser
        for object in self.objetlist:
            if isinstance(object,TimeUser): #Verifie que ce sont des TimeUsers
                object.adapthour(self.temps)
    def adaptInputOutput(self):
        input_energy = 0
        output_energy = 0
        time_step = 1 #représente un saut d'une heure
        from powersourcesClass import powersources
        from powerconsummerClass import powerconsummer

        for object in self.objetlist:
            if isinstance(object,powersources):
                input_energy+= object.getPower()*time_step
            if isinstance(object,powerconsummer):
                output_energy+= object.getPower()*time_step
        
        return input_energy,output_energy
    def check_batteries(self,input_energy,output_energy):

        from BatteryClass import Battery
        for object in self.objetlist:
            if isinstance(object,Battery):
                object.adaptSOC(input_energy,output_energy)
    def adapt_Y(self):
        from BatteryClass import Battery
        from powersourcesClass import powersources
        from powerconsummerClass import powerconsummer

        for objet in self.objetlist:
            if isinstance(objet,Battery):
                #print(f"I'm from Battery, here's my name {objet.getName()}")
                objet.adapt_my_y()
            elif isinstance(objet,powersources):
                #print(f"I'm from powersources, here's my name {objet.getName()}")
                objet.adapt_my_y()
            elif isinstance(objet,powerconsummer):
                #print(f"I'm from powerconsummer, here's my name {objet.getName()}")
                objet.adapt_my_y()
            else:
                print("ERROR!!")
                #print(f"Here's my name {objet.getName()}")
                #return 0
    def powergraphedisplay(self):

        from powerconsummerClass import powerconsummer
        from powersourcesClass import powersources
        for objet in self.objetlist:
            if isinstance(objet,powersources) or isinstance(objet,powerconsummer):
                plot(self.x, objet.getY())
        
        grid()
        title("Evolution de la Puissance en fonction du temps pour une journée")
        legend(["PV", "Grid", "GroupElec", "Lumiere", "Ordinateur", "Imprimante","Climatiseur_bureau","Climatiseur_medoc"])
        xlabel("Temps (h)")
        ylabel("Puissance (Wh)")
        show()
    def batterygraphedisplay(self):
        from BatteryClass import Battery
        for objet in self.objetlist: 
            if isinstance(objet,Battery):
                plot(self.x, objet.getY())
                #plot(self.x, objet.get_SOCmax_list(),"r")
                #plot(self.x, objet.get_SOCmin_list(),"r")
                
        
        grid()
        title("SOC")
        legend(["Battery","SOCmax","SOCmin"])
        xlabel("Temps (h)")
        ylabel("SOC (%)")
        show()
    def bilan_energy_graph(self):
        from BatteryClass import Battery
        for objet in self.objetlist: 
            if isinstance(objet,Battery):
                plot(self.x, objet.get_bilan_list())
        
        grid()
        title("Bilan d'énergie")
        legend(["bilan"])
        xlabel("Temps (h)")
        ylabel("Wh")
        show()

    def displayAllGraphs(self):
        self.powergraphedisplay()
        self.batterygraphedisplay()
        self.bilan_energy_graph()