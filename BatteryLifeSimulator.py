class BatteryLifeEstimator:
    def __init__(self, capacity, max_cycles, max_temperature):
        self.capacity = capacity  # Capacité nominale de la batterie en Ah (ampères-heures)
        self.max_cycles = max_cycles  # Nombre maximum de cycles de charge/décharge
        self.max_temperature = max_temperature  # Température maximale admissible en degrés Celsius
        self.current_cycles = 800  # Nombre de cycles de charge/décharge actuels
        self.current_temperature = 27.3  # Température actuelle en degrés Celsius (valeur par défaut de 25°C)

    def charge_discharge(self, charge_fraction):
        # Simule un cycle de charge/décharge partiel de la batterie
        if self.current_cycles < self.max_cycles:
            self.current_cycles += charge_fraction

    def update_temperature(self, temperature):
        # Met à jour la température actuelle de la batterie
        self.current_temperature = temperature

    def usage_while_charging(self, charge_fraction):
        # Simule l'utilisation de la batterie tout en étant en charge
        self.charge_discharge(charge_fraction)

    def predict_remaining_life(self):
        # Calcule la durée de vie restante estimée de la batterie en jours
        remaining_cycles = max(self.max_cycles - self.current_cycles, 0)
        temperature_factor = max(1.0, self.current_temperature / self.max_temperature)

        # Estimation de la durée de vie restante en jours
        remaining_life_days = remaining_cycles * (1 / temperature_factor)

        return remaining_life_days

# Exemple d'utilisation :
if __name__ == "__main__":
    capacity = 200  # Capacité nominale de la batterie en Ah
    max_cycles = 2400  # Nombre maximum de cycles de charge/décharge
    max_temperature = 50  # Température maximale admissible en degrés Celsius

    battery = BatteryLifeEstimator(capacity, max_cycles, max_temperature)

    # Simulons quelques cycles de charge/décharge partiels et mettons à jour la température
    for _ in range(365): #100
        battery.charge_discharge(1)  # 10% d'un cycle complet

    battery.update_temperature(27.3)  # Température de la batterie de 30°C

    # Simulons l'utilisation de la batterie tout en étant en charge
    battery.usage_while_charging(0.50)  # 70% d'un cycle complet

    # Estimons la durée de vie restante de la batterie
    remaining_life = battery.predict_remaining_life()
    remaining_years = remaining_life/365.0
    print(f"Durée de vie restante estimée de la batterie : {remaining_life:.2f} jours")
    print(f"Nombre d'années restantes : {remaining_years:.2f} années")
