#include <string>

/*
Fonction Deg2Rad
{
      Role : Convertir des degrés en radians
        Entrées: degres : 1réel
        Sortie: 1réel
}
 */
float Deg2Rad(float degres);

/*
Fonction Rad2Deg
{
      Role : Convertir des radians en degrés
        Entrées: radians : 1réel
        Sortie: 1réel
}
*/
float Rad2Deg(float degres);
/*
Fonction EstBissextile // T2
{
        Role : Verifie si une année est bissextile
        Entrées: annee :1entier
        Sortie: 1 booléen (Vrai ou Faux)
}*/
bool EstBissextile(int annee);
/*
Fonction Sexa2Deg
{
        Role : Convertir un angle sexagésimal en angle décimal
        Entrée: chainesexa : chaine de caractère
        Sortie: 1 réel
}
*/
float Sexa2Deg(std::string chainesexa);

/*
Fonction ConversionTempsHeure
{
    Role : Convertir un temps sous la forme HH MM SS vers une heure "décimale" (Comme par exemple 1:30:00 devient 1.5)
    Entrée : heure : 1entier, minute : 1entier, seconde : 1entier
    Sortie: 1 réel
}
*/
float ConversionTempsHeure(int heure,int minute,int seconde);

/*
Fonction SaisieObligatoireReel
{
    Role: Forcer l'utilisateur à saisir un reel
    Entrée : afficher : 1 chaine de caractere (Chaine de carac à afficher avant la saisie)
    Sortie: 1 réel
}

*/
float SaisieObligatoireReel(std::string chainecarac);

/*
{Calculs solaire}

Fonction CalculEnergieSolaire // Utilisée dans RayonnementSolaireDirect
{
     Role: Donne l'energie solaire (en W/m²) en fonction du jour de l'année

(Esol = 1367*(1 + 0.0334*cos(360 * (j - 2.7206)/NB_JOUR_AN)) , en W=m2)

Entrées : nbjouran : 1 entier, j : 1entier
Sortie : 1 réel
}*/
float CalculEnergieSolaire(int nbjouran,int jour);

/*

Fonction CalculDeclinaison // Utilisée dans HauteurSoleil,Azimut,DureeInsolation
{
    Role : Calcul la déclinaison de la Terre

(Dec = arcsin (0.3978*sin (vitesseangulaire*(j - 82 - 2 sin(vitesseangulaire(j - 1)))))
(vitesseangulaire = 360/NB_JOUR_AN)
Entrées: nbjouran : 1 entier,j : 1 entier
Sortie: 1 réel
}
*/
float CalculDeclinaison(int nbjouran,int jour);

/*
{ Equation du temps}


 Fonction CalculEquationTemps
 {
     R : Calcule l'équation du temps

     (E : C + O)

     Entrée : jour dans l'année j : 1 réel
     Sortie : 1 réel
 }*/
float CalculEquationTemps(int jour);

/*

 Fonction CorrectionHeureLegal2Solaire TODO : A voir si necessaire de savoir si l'année est bissextile
{
    Role: Convertir une heure(décimale) légale en heure solaire
    Entrée : estbissextile: 1 booléen , longitude : 1réel, heurehiver: 1 booléen , heurelegale : 1 réel          (Heure décimale)
    Sortie: 1 réel
    }


 */


/*

Fonction CalculAngleHoraire
{
Role : Calcul l'angle horaire
(Ah = 180 * (tSV/12 -1)            tsv est le temps solaire vrai

Entrées: TempsSolaireVrai : 1réel
Sortie: 1 réel
}
*/
float CalculAngleHoraire(float tempsolairevrai);

/*
{Position du Soleil}

Fonction CalculHauteurSoleil
{
Role : Calcul la hauteur du soleil
(h = arcsin(sin(Lat) * sin(Dec) + cos(Lat) * cos(Dec) * cos(Ah))

Entrées: Declinaison : 1réel, Latitude : 1 réel, AngleHoraire : 1 réel

Sortie:1 réel
}
*/
float CalculHauteurSoleil(float declinaison,float latitude,float anglehoraire);
/*
Fonction CalculAzimut // Utilisée dans coeffincidence
{
    Role : Calcul l'azimut, angle de même signe que l'angle horaire

    (a = arcsin( cos(Dec) * sin(Ah) / cos(h) ) )

    Entrée : declinaison   : 1 réel
                  hauteursoleil  : 1 réel
    Sortie : 1 réel
 }
*/
float CalculAzimut(float declinaison,float hauteursoleil);

/*
Fonction CalculDureeInsolation // TODO : Pourquoi aucune utilisation ?
{
      Role : Calcul la durée d'insolation(Durée maximale d'une jour
      Di = 2/15 * arccos(-tan(Lat) * tan(Dec))

Entrées:Latitude : 1réel, Declinaison:1réel
Sortie: 1 réel
}

*/


/*


 {Réception du rayonnement}

Fonction CalculCoefficientIncidence
{
    R : Calcul le coefficient d'incidence

    (Ci = sin(i) * cos(h) * cos(o - a) + cos(i) * sin(h) )

    Entrée : inclination : 1 réel
                  hauteursoleil : 1 réel
                  orientation : 1 réel
                  azimut: 1 réel
    Sortie : 1 réel
 }
*/
float CalculCoefficientIncidence(float inclinaison,float hauteursoleil,float orientation,float azimut);
/*
{Energie solaire disponible}

 Fonction CalculRayonnementSolaireDirect
  {

      R : Calcul le rayonnement solaire direct arrivant sur un plan récepteur normal à ce rayonnement

     ( I* = Esol * e^(-Er*m*TL)

      Entrée :  Enersol : 1 réel
                                hauteursoleil: 1 réel
                                tauxmoyenhumiditerelative: 1réel
                                typezone: 1 entier
                                température T en °C : 1 réel
                                altitude z : 1 réel

      Sortie : 1 réel
  }
  */

float CalculRayonnementSolaireDirect(float Enersol,float hauteursoleil,float tauxmoyenhumiditerelative,int typezone,float temperaturecelcius,float altitude);

/*

  Fonction CalculRayonnementSolaireDiffus
  {
      R : Calcul le rayonnement solaire diffus arrivant sur un plan récepteur normal à ce rayonnement

      (D* = 124 * sin(h)^0.4 * ((1 + cos(i)) / 2 ) + 211.86 * sin(h)^1.22 * ((1 - cos(i)) / 2)

      Entrée : hauteur du soleil h : 1 réel
                    inclinaison i : 1 réel
      Sortie : 1 réel
  }*/
float CalculRayonnementSolaireDiffus(float hauteursoleil,float inclinaison);
  /*

 Fonction CalculRayonnementSolaireGlobal
 {
     R : Calcul le rayonnement solaire global (maximal) qui peut arriver sur un plan récepteur

     (G* = I* x Ci + D*)

     Entrée : rayonnement solaire direct I* : 1 réel
                   rayonnement solaire diffus D* : 1 réel
                   coefficient d'incidence Ci : 1 réel
     Sortie : 1 réels
 }
 */
float CalculRayonnementSolaireGlobal(float coefficientincidence,float rayosoldirect,float rayosoldiffus);



