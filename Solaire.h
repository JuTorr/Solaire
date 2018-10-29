#include <string>

/*
      Role : Convertir des degrés en radians
        Entrées: degres : 1réel
        Sortie: 1réel
 */
float Deg2Rad(float degres);
//T4


/*
      Role : Convertir des radians en degrés
        Entrées: radians : 1réel
        Sortie: 1réel
*/
float Rad2Deg(float degres);
//T4


/*
        Role : Verifie si une année est bissextile
        Entrées: annee :1entier
        Sortie: 1 booléen (Vrai ou Faux)
*/
bool EstBissextile(int annee);
//T2


/*
        Role : Convertir un angle sexagésimal en angle décimal (en radians)
        Entrée: chainesexa : chaine de caractère //
        Sortie: 1 réel
*/
float Sexa2Deg(std::string chainesexa);
//T1


/*
    Role : Convertir un temps sous la forme HH MM SS vers une heure "décimale" (Comme par exemple 1:30:00 devient 1.5)
    Entrée : heure : 1entier, minute : 1entier, seconde : 1entier
    Sortie: 1 réel
*/
float ConversionTempsHeure(int heure,int minute,int seconde);
//T2


/*
    Role: Forcer l'utilisateur à saisir un reel quelconque
    Entrée : afficher : 1 chaine de caractere (Chaine de carac à afficher avant la saisie)
    Sortie: 1 réel
*/
float SaisieObligatoireReel(const char chainecarac[]);
//T3

/*
    Role: Forcer l'utilisateur à saisir un reel dans l'intervalle [bornebasse;bornehaute]
    Entrée : afficher : 1 chaine de caractere (Chaine de carac à afficher avant la saisie)
    Sortie: 1 réel
*/
float SaisieObligatoireReelBorne(const char chainecarac[],int bornebasse,int bornehaute);

/*
    Role: Forcer l'utilisateur à saisir un ENTIER dans l'intervalle [bornebasse;bornehaute]
    Entrée : afficher : 1 chaine de caractere (Chaine de carac à afficher avant la saisie)
    Sortie: 1 réel
*/
int SaisieObligatoireEntierBorne(const char chainecarac[],int bornebasse,int bornehaute);



//{Calculs solaire}

/*
     Role: Donne l'energie solaire (en W/m²) en fonction du jour de l'année (plan perpen hors atmos)
     Entrées : nbjouran : 1 entier, j : 1 entier
     Sortie : 1 réel
*/
float CalculEnergieSolaire(int nbjouran,int jour);
//T3


/*
    Role : Calcul la déclinaison de la Terre
    Entrées: nbjouran : 1 entier,j : 1 entier
    Sortie: 1 réel
*/
float CalculDeclinaison(int nbjouran,int jour);
//T5


//{ Equation du temps}

/*
     R : Calcule l'équation du temps
     Entrée : jour dans l'année j : 1 réel
     Sortie : 1 réel
 */
float CalculEquationTemps(int jour);
//T6


/*
    Role: Convertir une heure(décimale) légale en heure solaire
    Entrée : estbissextile: 1 booléen , longitude(en radians) : 1réel, heurehiver: 1 booléen , heurelegale : 1 réel          (Heure décimale)
    Sortie: 1 réel
 */
float CorrectionHeureLegale2solaire(bool estbissextile, float longitude, bool heurehiver, float heurelegale);            // ajouter une fonction heure hiver ete



/*
    Role : Calcul l'angle horaire en radians
    Entrées: TempsSolaireVrai en heure décimale : 1réel
    Sortie: 1 réel
}
*/
float CalculAngleHoraire(float tempsolairevrai);
//T6


//Position du Soleil

/*
    Role : Calcul la hauteur du soleil (en degres)
    Entrées: Declinaison(en radians) : 1réel, Latitude(en radians) : 1 réel, AngleHoraire(en radians) : 1 réel
    Sortie:1 réel
*/
float CalculHauteurSoleil(float declinaison,float latitude,float anglehoraire);
//T7


/*
    Role : Calcul l'azimut, angle de même signe que l'angle horaire
    Entrée : declinaison (en radians)   : 1 réel
            hauteursoleil (! en degres) : 1 réel
    Sortie : 1 réel
*/
float CalculAzimut(float declinaison,float hauteursoleil);             //radians degres
//T5


/*
    Role : Calcul la durée d'insolation(Durée maximale d'une jour)
    Entrées:Latitude(en radians) : 1réel, Declinaison(en degres):1réel
    Sortie: 1 réel
*/
float CalculDureeInsolation(float latitude, float declinaison);          //faire commencer a tsv lever...     ?     tsv  coucher  -  tsv levee   ou     di + ts lever
//à voir


//Réception du rayonnement

/*
    R : Calcul le coefficient d'incidence
    Entrée : inclination (en radians) : 1 réel
                  hauteursoleil (en degres) : 1 réel
                  orientation (en radians) : 1 réel
                  azimut (en radians): 1 réel
    Sortie : 1 réel
*/
float CalculCoefficientIncidence(float inclinaison,float hauteursoleil,float orientation,float azimut);
//T7


//Energie solaire disponible

/*
      R : Calcul le rayonnement solaire direct arrivant sur un plan récepteur normal à ce rayonnement (Après avoir traverser l'atmosphère)
      Entrée :  Enersol : 1 réel
                                hauteursoleil (en degres): 1 réel
                                tauxmoyenhumiditerelative: 1réel
                                typezone : 1 entier  (Environnement industriel(1), rural(2), urbain(3), industriel(4))
                                température en °C : 1 réel
                                altitude (en m) : 1 réel

      Sortie : 1 réel
  */
float CalculRayonnementSolaireDirect(float Enersol,float hauteursoleil,float tauxmoyenhumiditerelative,int typezone,float temperaturecelcius,float altitude);
//T1


/*
      R : Calcul le rayonnement solaire diffus arrivant sur un plan récepteur d'inclinaison i (après avoir été réflechi par nuages, les aerosols, les poussieres et le sol.)
      Entrée : hauteursoleil  (en degres) : 1 réel
                   inclinaison (en radians) : 1 réel
      Sortie : 1 réel
*/
float CalculRayonnementSolaireDiffus(float hauteursoleil,float inclinaison);
//T4


/*
     R : Calcul le rayonnement solaire global (maximal) qui peut arriver sur un plan récepteur
     Entrée : rayonnementsolairedirect : 1 réel
              rayonnementsolairediffus : 1 réel
              coefficientincidence : 1 réel
     Sortie : 1 réels
 */
float CalculRayonnementSolaireGlobal(float coefficientincidence,float rayosoldirect,float rayosoldiffus);
//T2


/*
Role : Verifier si pour le jour entré, à l'heure entrée et à l'année entrée, l'heure est une heure d'hiver (renvoie true) ou d'été (renvoie false)
Entrées: heure : 1 entier, jour : 1entier, annee : 1entier
Sortie : 1 booléen

*/
bool VerifHeureHiver(int heure,int jour,int annee);
// T1
/*
Triômes :
  T1 Arnaud Arthur Maxime
  T2 Yassine Charles Gwendal
  T3 Teddy Jérémy Lucas
  T4 Jonah Yvan Melvine
  T5 Catharina Wassim Inès
  T6 Guilhem Jade Alexis
  T7 Benjamin Alexandre Fahel
*/




















/*
Entrées :

i. Un lieu : longitude/latitude/altitude. Pour la latitude et la longitude, il aura
le choix des unites (degres decimaux ou degres sexagesimaux).

longitude comprise entre -90 et 90
longitude comprise entre -180 et 180
altitude sur Terre comprise entre -418 et 8848m (Source:https://fr.wikipedia.org/wiki/Terre)


ii. Une date : annee, mois, jour, heure, minute, seconde.
annee : pas de borne(on bornera entre 1990(car on prendre 1990 en repere pour le calcul heure hiver été)





iii. Un environnement : industriel, rural, urbain, industriel
iv. Des donnees meteo : Temperature, Humidite relative
v. La position du capteur : orientation, inclinaison (attention a ^etre precis sur
les demandes).
*/

