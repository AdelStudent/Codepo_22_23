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
        from BatteryClass import Battery
        for obj in self.objetlist:
            obj.adapthour(self.temps)


    def adaptInputOutput(self):
        input_energy = 0
        output_energy = 0
        time_step = 1 #représente un saut d'une heure
        
        from powersourcesClass import powersources
        from powerconsummerClass import powerconsummer

        for obj in self.objetlist:
            if isinstance(obj, powersources):
                input_energy += obj.getPower() * time_step
            if isinstance(obj, powerconsummer):
                output_energy += obj.getPower() * time_step

        return input_energy, output_energy
    
    def check_batteries(self,input_energy,output_energy):

        from BatteryClass import Battery
        for obj in self.objetlist:
            if isinstance(obj, Battery):
                obj.adaptSOC(input_energy, output_energy)
    def adapt_Y(self):
        from BatteryClass import Battery
        from powersourcesClass import powersources
        from powerconsummerClass import powerconsummer
        
        for obj in self.objetlist:
            obj.adapt_my_y()
            
            
    def powergraphedisplay(self):

        from powerconsummerClass import powerconsummer
        from powersourcesClass import powersources
        for obj in self.objetlist:
            if isinstance(obj, powersources) or isinstance(obj, powerconsummer):
                plt.plot(self.x, obj.getY())

        plt.grid()
        plt.title("Evolution de la Puissance en fonction du temps pour une journée")
        plt.legend([obj.getName() for obj in self.objetlist if isinstance(obj, powersources) or isinstance(obj, powerconsummer)])
        plt.xlabel("Temps (h)")
        plt.ylabel("Puissance (W)")
        plt.show()

        
    def batterygraphedisplay(self):
        from BatteryClass import Battery
        for obj in self.objetlist:
            if isinstance(obj, Battery):
                plt.plot(self.x, obj.getY())
                plt.plot(self.x, obj.get_SOCmax_list(), "r")
                plt.plot(self.x, obj.get_SOCmin_list(), "r")
        plt.grid()
        plt.title("SOC de la Batterie")
        plt.legend([obj.getName() for obj in self.objetlist if isinstance(obj, Battery)] + ["SOCmax", "SOCmin"])
        plt.xlabel("Temps (h)")
        plt.ylabel("SOC (%)")
        plt.show()
        
        
        
    def bilan_energy_graph(self):
        from BatteryClass import Battery
        for obj in self.objetlist:
            if isinstance(obj, Battery):
                plt.plot(self.x, obj.get_bilan_list())

        plt.grid()
        plt.title("Bilan d'énergie")
        plt.legend([obj.getName() for obj in self.objetlist if isinstance(obj, Battery)])
        plt.xlabel("Temps (h)")
        plt.ylabel("Wh")
        plt.show()
        

    def displayAllGraphs(self):
        self.powergraphedisplay()
        self.batterygraphedisplay()
        self.bilan_energy_graph()

    
    
    