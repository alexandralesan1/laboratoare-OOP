from abc import ABC, abstractmethod
import random

class Interactiune(ABC):
    @abstractmethod
    def ataca(self, prada):
        pass

    @abstractmethod
    def reproduce(self):
        pass

class EntitateEcosistem(ABC):
    def __init__(self, nume: str, energie: int, x: int, y: int, rata: float):
        self.nume = nume
        self.energie = energie
        self.pozitieX = x
        self.pozitieY = y
        self.rataSupravietuire = rata

    @abstractmethod
    def actioneaza(self):
        pass

    def este_viu(self):
        return self.energie > 0

    def scade_energie(self, val: int):
        self.energie -= val
        if self.energie < 0:
            self.energie = 0

    def creste_energie(self, val: int):
        self.energie += val

    def set_pozitie(self, x: int, y: int):
        self.pozitieX = x
        self.pozitieY = y

    def get_energie(self):
        return self.energie

    @abstractmethod
    def reproduce(self):
        pass

class Planta(EntitateEcosistem, Interactiune):
    def __init__(self, nume: str, energie: int, x: int, y: int, rata: float, resurse: int):
        super().__init__(nume, energie, x, y, rata)
        self.resurse = resurse

    def actioneaza(self):
        if self.resurse > 10:
            self.creste_energie(5)
            self.resurse -= 10

    def ataca(self, prada):
        pass

    def reproduce(self):
        return Planta(self.nume + "_noua", 20, self.pozitieX, self.pozitieY, self.rataSupravietuire, 20)

class Animal(EntitateEcosistem, Interactiune, ABC):
    def __init__(self, nume: str, energie: int, x: int, y: int, rata: float, viteza: int, tip_hrana: str):
        super().__init__(nume, energie, x, y, rata)
        self.viteza = viteza
        self.tipHrana = tip_hrana

    def actioneaza(self):
        self.deplaseaza()
        self.scade_energie(1)

    def deplaseaza(self):
        self.pozitieX += self.viteza

    @abstractmethod
    def mananca(self, entitate):
        pass

    @abstractmethod
    def ataca(self, prada):
        pass

    @abstractmethod
    def reproduce(self):
        pass

class Erbivor(Animal):
    def __init__(self, nume: str, energie: int, x: int, y: int, rata: float, viteza: int):
        super().__init__(nume, energie, x, y, rata, viteza, "plante")

    def mananca(self, entitate):
        if isinstance(entitate, Planta):
            self.creste_energie(10)
            entitate.scade_energie(10)

    def ataca(self, prada):
        pass

    def reproduce(self):
        return Erbivor(self.nume + "_jr", 30, self.pozitieX, self.pozitieY, self.rataSupravietuire, self.viteza)

class Carnivor(Animal):
    def __init__(self, nume: str, energie: int, x: int, y: int, rata: float, viteza: int):
        super().__init__(nume, energie, x, y, rata, viteza, "carne")

    def mananca(self, entitate):
        if isinstance(entitate, Animal) and not isinstance(entitate, Carnivor):
            self.creste_energie(20)
            entitate.scade_energie(entitate.get_energie())

    def ataca(self, prada):
        if isinstance(prada, Animal):
            prada.scade_energie(20)
            self.creste_energie(10)

    def reproduce(self):
        return Carnivor(self.nume + "_junior", 40, self.pozitieX, self.pozitieY, self.rataSupravietuire, self.viteza)

class Omnivor(Animal):
    def __init__(self, nume: str, energie: int, x: int, y: int, rata: float, viteza: int):
        super().__init__(nume, energie, x, y, rata, viteza, "amestec")

    def mananca(self, entitate):
        if isinstance(entitate, Planta):
            self.creste_energie(5)
            entitate.scade_energie(5)
        elif isinstance(entitate, Animal) and entitate != self:
            self.creste_energie(15)
            entitate.scade_energie(entitate.get_energie())

    def ataca(self, prada):
        if isinstance(prada, Animal):
            prada.scade_energie(10)
            self.creste_energie(5)

    def reproduce(self):
        return Omnivor(self.nume + "_jr", 35, self.pozitieX, self.pozitieY, self.rataSupravietuire, self.viteza)

class Ecosistem:
    def __init__(self, latime: int, inaltime: int):
        self.latime = latime
        self.inaltime = inaltime
        self.entitati = []

    def adauga_entitate(self, e):
        self.entitati.append(e)

    def elimina_entitate(self, e):
        if e in self.entitati:
            self.entitati.remove(e)

    def simuleaza_pas(self):
        for e in self.entitati:
            e.actioneaza()

        noi_entitati = []
        for e in self.entitati:
            if e.get_energie() > 70:
                noua = e.reproduce()
                if noua is not None:
                    noua.set_pozitie(e.pozitieX + 1, e.pozitieY)
                    noi_entitati.append(noua)

        self.entitati.extend(noi_entitati)
        self.entitati = [e for e in self.entitati if e.este_viu()]

        if random.randint(0, 99) < 5:
            for e in self.entitati:
                if isinstance(e, Planta):
                    e.scade_energie(5)

    def afiseaza_stare(self):
        print("Entitati in ecosistem:")
        for e in self.entitati:
            print(f"{type(e).__name__} {e.nume} (Energie: {e.get_energie()}, Poz: {e.pozitieX},{e.pozitieY})")

if __name__ == "__main__":
    eco = Ecosistem(100, 100)
    p1 = Planta("Planta1", 30, 5, 5, 0.9, 50)
    i1 = Erbivor("Iepure1", 40, 10, 10, 0.8, 2)
    l1 = Carnivor("Lup1", 50, 12, 10, 0.7, 3)
    u1 = Omnivor("Urs1", 60, 15, 10, 0.85, 1)

    eco.adauga_entitate(p1)
    eco.adauga_entitate(i1)
    eco.adauga_entitate(l1)
    eco.adauga_entitate(u1)

    for t in range(10):
        print(f"Pasul {t}")
        eco.simuleaza_pas()
        eco.afiseaza_stare()
        print("-" * 30)

    print("Raport final:")
    eco.afiseaza_stare()
