# Modélisation du Système de la Cameskin

from powersourcesClass import powersources # import la class en lui-même 
from TimeManagerClass import TimeManager
from powerconsummerClass import powerconsummer
from BatteryClass import Battery
import random

ON = 1 #Pris en compte 
OFF = 0 #Pas pris en compte 

# Sources 
PV_behavior = [0,0,0,0,0,0,0.104102729,0.35242141,0.642178054,0.763581929,0.998803315,0.865229468,1,0.873200005,0.63030394,0.334391656,0.097306797,0,0,0,0,0,0,0] #Pourcent du max de la journée 
max_pv_power = 2264.59 # Puissance maximale enregistré (PVGis) pour une journée de Juillet 
PV = powersources("PV", ON*max_pv_power, PV_behavior) 

# Modèle de comportement du réseau
# Cas 1: Réseau toujours actif (ON = 1)
Grid_behavior = [1] * 24

# Cas 2: Réseau avec des coupures aléatoires (ON=0 et ON=1)
# On utilise random.choices pour générer des 0 (coupures) et des 1 (réseau actif) aléatoirement.
# La probabilité de coupure est fixée à 30% pour cet exemple, mais vous pouvez la modifier selon vos besoins.
Grid_behavior_random = random.choices([0, 1], k=24, weights=[0.6, 0.9])

# Maintenant, nous pouvons créer des instances de la classe powersources avec les comportements du réseau correspondants.
Grid = powersources("Réseau", ON * 4000, Grid_behavior)
Grid_random = powersources("Réseau Aléatoire", ON * 10000, Grid_behavior_random)


# 10 000 W : Puissance du réseau
GroupElec_behavior =  [1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1]
GroupElec = powersources("Groupe Electrogène", OFF*5000, GroupElec_behavior)

# 1 400 W : Puissance prise au hasard pour la production électrogène (climatiseur)

# Battery
my_Battery = Battery("Battery",100, 20) # SOC initial = 50%, nombre de batterie = 20

# Consummer 
nbr_lumiere = 85
nbr_ordi = 10
nbr_impr = 10
nbr_clim_bureau = 9
nbr_clim_medoc = 45

Lumiere_behavior = [0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0]
Lumiere = powerconsummer("Lumière", ON*nbr_lumiere*85, Lumiere_behavior)
# 40W -> Puissance consommée par une lumière
Ordinateur_behavior = [0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0]
Ordinateur = powerconsummer("Ordinateur", ON*nbr_ordi*35, Ordinateur_behavior)
# 35W -> Puissance consommée par un ordinateur 
Imprimante_behavior = [0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0]
Imprimante = powerconsummer("Imprimante", ON*nbr_impr*13, Imprimante_behavior)
# 30W -> Puissance consommée par une imprimante 


Clim_bureau_behavior = [0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0]
Climatiseur_bureau = powerconsummer("Climatiseur Bureau", ON*(8*5500 + 1*7500), Clim_bureau_behavior) # 9 Climatiseurs dans le batiment administratif 
# 8*18000+1*24000 
# 1 BTU = 2,93 10^-4 

Clim_medoc_behavior = [1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1]
Climatiseur_medoc = powerconsummer("Climatiseur Medoc", ON*(14*7500 + 5500*37), Clim_medoc_behavior) # 51 Climatiseurs dans les dépôts
# 14*24000 + 37*18000 (0.293 pour convertir BTU)

# Time situation
Obj = [PV, Grid_random, GroupElec, my_Battery, Lumiere, Ordinateur, Imprimante,Climatiseur_bureau,Climatiseur_medoc]
TimeSync = TimeManager(0, Obj) # Doit prendre connaissance de tout le monde -> après les autres objets 
Objet = [PV, Grid_random, GroupElec, my_Battery, Lumiere, Ordinateur, Imprimante,Climatiseur_bureau,Climatiseur_medoc]


# Graphe
nbr_jour = 5
TimeSync.live_hours(nbr_jour*24) 


