#include "Solaire.h"
#include <iostream>
#include <fstream>
#include <limits>


using namespace std;

int main(){




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
        float latitude,longitude,altitude; // Lieu
        float annee,mois,jour,heure,minute,seconde; // Date, float car plus facile à traiter plus tard

        int sexagesimaux; // Choix degrès séxagesimaux ou décimaux
        float environnement; // Environnement industriel(1), rural(2), urbain(3), industriel(4)
        float temperature,humiditerelative; // Données meteo
        float orientationcapteur,inclinaisoncapteur; // Données capteur
        int NB_JOUR_AN;
        bool fin= false;
        int choix;
        float tauxmoyenhumiditerelative; // Sera rentrée par l'utilisateur
        float declinaison;
        float anglehoraire,azimut,hauteursoleil;
        float heuresolaire,heuredecimale;
        bool estbissextile,heurehiver;
        altitude = SaisieObligatoireReel("Veuillez saisir l'altitude de votre lieu");
        tauxmoyenhumiditerelative = SaisieObligatoireReelBorne("Veuillez saisir le taux d'humidité relative de votre lieu",0,100);
        environnement = SaisieObligatoireEntierBorne("Veuillez saisir un environnement ( Environnement industriel(1), rural(2), urbain(3), industriel(4))",1,4);
        sexagesimaux = SaisieObligatoireEntierBorne("Voulez vous entrer vos valeur en degrès séxagesimaux ? (0 pour non, 1 pour oui)\n",0,1)

        if(sexagesimaux){
            string latisexa,longisexa;//TODO: Sexa2Deg devra recevoir un tableau de carac car interdit d'utiliser objet string
            cin >> latisexa;
            cin >> longisexa; // Possibilité de verif plus tard si la saisie est valide
            latitude = Sexa2Deg(latisexa);
            longitude = Sexa2Deg(longisexa);
        }
        else{
            latitude = SaisieObligatoireReelBorne("Veuillez saisir la latitude de votre lieu",-90,90);
            longitude = SaisieObligatoireReelBorne("Veuillez saisir la longitude de votre lieu",-180,180);
        }





        while(!fin){
            cout << "Menu \n"
                 << "1.rayonnement global reu en un point du globe en fonction du jour de l'annee saisie a une heure précise"<< endl
                 << "2.rayonnement global recu en un point du globe en fonction de l'heure pour le jour "<< jour << " de l'annee "<<annee <<endl
                 << "0 : Fin\n"
                 ;
            while (!(cin >> choix)) { // On force choix à prendre une valeur numérique
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore l'entrée erronée
                cerr<<"Saisie erronée, veuillez verifier votre saisie\n";
            }
            switch(choix){
                case 1:{
                    int j =0;
                    string final;
                    final = "Jour Rayonnement(W/m2) \n";
                    float rayoglob,rayodiff,rayodirect,coeffinci,enersol;
                    heuredecimale = ConversionTempsHeure(heure,minute,seconde);// Hors boucle car ne depend pas du jour, on considere l'heure légale constante
                    estbissextile = EstBissextile(annee);
                    annee = SaisieObligatoireReel("Veuillez saisir une annee");
                    heure = SaisieObligatoireReelBorne("Veuillez saisir une heure",0,24);
                    minute = SaisieObligatoireReelBorne("Veuillez saisir une minute",0,60);
                    seconde = SaisieObligatoireReelBorne("Veuillez saisir une seconde",0,60);
                    if(estbissextile){
                        NB_JOUR_AN = 366;
                    }
                    else{
                        NB_JOUR_AN = 365;
                    }
                    while(j < NB_JOUR_AN){
                        declinaison = CalculDeclinaison(NB_JOUR_AN,j);
                        heurehiver = VerifHeureHiver(heure,j,annee);
                        heuresolaire = CorrectionHeureLegale2solaire(estbissextile,longitude,heurehiver,heuredecimale); // CorrectionHeureLegale2solaire(bool estbissextile, float longitude, bool heurehiver, float heurelegale);
                        anglehoraire = CalculAngleHoraire(heuresolaire);
                        hauteursoleil = CalculHauteurSoleil(declinaison,latitude,anglehoraire);
                        azimut = CalculAzimut(declinaison,hauteursoleil);
                        coeffinci = CalculCoefficientIncidence(inclinaisoncapteur,hauteursoleil,orientationcapteur,azimut);;
                        enersol = CalculEnergieSolaire(NB_JOUR_AN,j);
                        rayodirect = CalculRayonnementSolaireDirect(enersol,hauteursoleil,tauxmoyenhumiditerelative,environnement,temperature,altitude);
                        rayodiff = CalculRayonnementSolaireDiffus(hauteursoleil,inclinaisoncapteur);
                        rayoglob = CalculRayonnementSolaireGlobal(coeffinci,rayodirect,rayodiff);
                        final.append(to_string(j));
                        final.append(" "); // Séparateur
                        final.append(to_string(rayoglob));
                        final.append("\n");
                        j++;
                    }
                    // Ici saisie dans csv
                    string nomfichier = "Rayonnement en fonction des jours de l'annee "+to_string(annee)+".csv";
                    ofstream fichier(nomfichier, ios::out | ios::trunc);  //déclaration du flux et ouverture du fichier
                    if(fichier) // Si le fichier s'est ouvert
                    {
                        fichier << final;
                        cout << "Le fichier a bien ete cree";
                        fichier.close();  //  referme le fichier
                    }
                    else
                        cerr << "Erreur à l'ouverture !" << endl;
                    break;}
                case 2:{
                    break;}
                default:{
                    fin = true;
                    break;
                }
            }
        }















    /*ofstream fichier("test.csv", ios::out | ios::trunc);  //déclaration du flux et ouverture du fichier

    if(fichier) // Si le fichier s'est ouvert
    {
        fichier << "1" <<" "<<"2" <<" "<<"34";
        fichier.close();  //  referme le fichier
    }
    else
        cerr << "Erreur à l'ouverture !" << endl;*/

    return 0;
}

