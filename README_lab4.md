Descriere generală:

Proiectul simulează un ecosistem în care există entități de tip plante și animale. Plantele cresc și se reproduc, animalele (erbivore, carnivore, omnivore) se deplasează, se hrănesc (în funcție de tipul lor de dietă), interacționează, se reproduc și pot muri dacă rămân fără energie. Ecosistemul evoluează pas cu pas, iar la fiecare pas se pot produce evenimente aleatorii (ex: furtuni).

Principii OOP utilizate:

Moștenire:
-	Clasa EntitateEcosistem este clasa abstractă de bază. Planta și Animal moștenesc din ea. Animal este abstract, iar Erbivor, Carnivor, Omnivor moștenesc din Animal.

Polimorfism: 
-	Metode precum actioneaza(), mananca() și ataca() sunt definite în clasele de bază și suprascrise în cele derivate pentru comportamente specifice.

Interfață: 
-	Interactiune definește metode comune (ataca, reproduce) pe care atât plantele, cât și animalele le implementează (deși plantele nu atacă, metoda lor rămâne goală).

Clasă abstractă: 
-	EntitateEcosistem și Animal sunt clase abstracte care nu pot fi instanțiate direct.

Suprascriere și supraîncărcare: 

-	Metodele din subclase suprascriu implementările abstracte din superclase. Nu s-a evidențiat supraîncărcare (Python nu oferă direct overload), dar conceptul este înțeles.


Clasele si metodele explicate:

Clasa EntitateEcosistem;

clasă abstractă ce reprezintă o entitate generică din ecosistem.

__init__(self, nume, energie, x, y, rata)

Constructorul inițializează numele entității, energia, poziția (x, y) și rata de supraviețuire.
actioneaza(self)

Metodă abstractă care trebuie implementată de clasele derivate. Definește comportamentul specific al entității în timpul unui pas de simulare.

este_viu(self)
Verifică dacă entitatea mai are energie. Returnează True dacă energia > 0, altfel False.

scade_energie(self, val)
Reduce energia entității cu valoarea specificată (val). Energia minimă rămâne 0.

creste_energie(self, val)
Crește energia entității cu valoarea specificată (val).
set_pozitie(self, x, y)
Actualizează poziția entității pe axele X și Y.

get_energie(self)
Returnează valoarea curentă a energiei entității.

reproduce(self)
Metodă abstractă care trebuie implementată de clasele derivate. Definește modul în care entitatea creează o copie a sa.

Clasa Planta
Reprezintă o plantă din ecosistem.

__init__(self, nume, energie, x, y, rata, resurse)
Constructorul extinde clasa EntitateEcosistem și adaugă resursele disponibile plantei.

actioneaza(self)
Plantele consumă resurse pentru a-și crește energia (dacă au suficiente resurse).
Resursele scad cu 10 pentru fiecare creștere a energiei cu 5.

ataca(self, prada)
Plantele nu atacă alte entități. Metoda nu are implementare funcțională.

reproduce(self)
Creează o nouă plantă cu parametri similari, plasată în ecosistem de către clasa principală.

Clasa Animal
clasă abstractă care extinde EntitateEcosistem și definește comportamentul general al animalelor.

__init__(self, nume, energie, x, y, rata, viteza, tip_hrana)
Constructorul extinde EntitateEcosistem și adaugă viteza de deplasare și tipul de hrană.

actioneaza(self)
Animalul se deplasează pe axa X și își scade energia cu 1 pentru întreținere.

deplaseaza(self)
Animalul își schimbă poziția pe axa X în funcție de viteza sa.

mananca(self, entitate)
Metodă abstractă care trebuie implementată de clasele derivate. Definește modul în care animalul se hrănește.

ataca(self, prada)
Metodă abstractă care trebuie implementată de clasele derivate. Definește modul în care animalul atacă.

reproduce(self)
Metodă abstractă care trebuie implementată de clasele derivate. Definește modul în care animalul creează o copie a sa.

Clasa Erbivor
Reprezintă un animal erbivor care mănâncă plante.
mananca(self, entitate)
Consumă plante din ecosistem. Crește energia cu 10 și reduce energia plantei cu 10. Dacă energia plantei ajunge la 0, aceasta moare.

ataca(self, prada)
Erbivorii nu atacă alte entități. Metoda nu are implementare funcțională.

reproduce(self)
Creează un nou erbivor cu parametri similari.

Clasa Carnivor
Reprezintă un animal carnivor care mănâncă alte animale (erbivore sau omnivore).

mananca(self, entitate)
Consumă un alt animal (dacă nu este carnivor). Crește energia cu 20 și elimină toată energia prăzii.

ataca(self, prada)
Atacă alte animale, reducând energia acestora cu 20 și crescând energia proprie cu 10.

reproduce(self)
Creează un nou carnivor cu parametri similari.

Clasa Omnivor
Reprezintă un animal omnivor care poate consuma atât plante, cât și alte animale.

mananca(self, entitate)
Consumă plante (crește energia cu 5 și reduce energia plantei cu 5) sau alte animale (crește energia cu 15 și elimină toată energia prăzii).

ataca(self, prada)
Atacă alte animale, reducând energia acestora cu 10 și crescând energia proprie cu 5.

reproduce(self)
Creează un nou omnivor cu parametri similari.

Clasa Ecosistem
Reprezintă mediul în care toate entitățile coexistă.

__init__(self, latime, inaltime)
Constructorul definește dimensiunile ecosistemului și inițializează o listă de entități.

adauga_entitate(self, e)
Adaugă o entitate în ecosistem.

elimina_entitate(self, e)
Elimină o entitate din ecosistem (de exemplu, dacă moare).

simuleaza_pas(self)
Fiecare entitate acționează.
Dacă o entitate are suficientă energie (>70), aceasta se reproduce.
Elimină entitățile moarte (cu energie 0).
Poate simula evenimente aleatorii, precum o furtună (scade energia plantelor cu 5).

afiseaza_stare(self)
Afișează starea curentă a ecosistemului: tipul, numele, energia și poziția entităților.


Dificultăți întâlnite și soluții:

Stabilirea logici de reproducere și atac: În codul de mai sus am ilustrat conceptul. Într-un proiect real, ar trebui implementate reguli de proximitate (animalele trebuie să fie pe aceeași poziție cu prada/planta pentru a mânca sau ataca).
Gestionarea energiei și a morții entităților: A trebuit să avem grijă ca atunci când energia scade sub 0, entitatea să moară și să fie eliminată din ecosistem.
Evenimente aleatorii: Simplitatea a fost cheia. Am folosit un procent fix (5%) pentru a declanșa o furtună.
Separarea codului: Într-un proiect real, codul ar fi împărțit în mai multe fișiere (module), pentru o mai bună organizare. Aici s-a cerut tot codul împreună.

Prin această soluție, am început de la zero și am îndeplinit toate cerințele:
Clase abstracte, moștenire, polimorfism, interfețe.
Ierarhii complexe de clase: EntitateEcosistem → Planta și Animal → Erbivor, Carnivor, Omnivor.
Implementarea cerințelor de bază (creștere plante, hrană, reproducere, atac).
Evenimente aleatorii (furtună).
Scenarii de testare și documentație, inclusiv UML.
Codul poate fi extins și rafinat pentru a îmbunătăți logica de simulare.













