#include "Fonctions.h"
#include <iostream>
#include <fstream>
#include <limits>


using namespace std;

int main(){
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


        /*annee = SaisieObligatoireReel("Veuillez saisir une annee");
        mois = SaisieObligatoireReel("Veuillez saisir un mois");
        heure = SaisieObligatoireReel("Veuillez saisir une heure");
        minute = SaisieObligatoireReel("Veuillez saisir une minute");
        seconde = SaisieObligatoireReel("Veuillez saisir une seconde");
        altitude = SaisieObligatoireReel("Veuillez saisir l'altitude de votre lieu");
         tauxmoyenhumiditerelative = SaisieObligatoireReel("Veuillez saisir le taux d'humidité relative de votre lieu");
         */


        if(EstBissextile(annee)){
            NB_JOUR_AN = 366;
        }
        else{
            NB_JOUR_AN = 365;
        }

        cout << "Voulez vous entrer vos valeur en degrès séxagesimaux ? (0 pour non, 1 pour oui)\n";
        do{
            while(!(cin>>sexagesimaux)){ // On force sexagesimaux à prendre une valeur =0 ou 1
              cin.clear(); // Permet de clear l'entrée
              cin.ignore( numeric_limits<streamsize>::max(), '\n' ); // Ignore l'entrée erronée
              cerr<<"Saisie erronée, veuillez verifier votre saisie (0 ou 1)\n";
            }
            if(sexagesimaux != 0 && sexagesimaux != 1){
                cerr<<"Saisie erronée, veuillez verifier votre saisie (0 ou 1)\n";}
        }while(sexagesimaux != 0 && sexagesimaux != 1);



        if(sexagesimaux){
            string latisexa,longisexa;
            cin >> latisexa;
            cin >> longisexa; // Possibilité de verif plus tard si la saisie est valide
            /*latitude = Sexa2Deg(latisexa);
            longitude = Sexa2Deg(longisexa);*/
        }
        else{
            /*latitude = SaisieObligatoireFloat("Veuillez saisir la latitude de votre lieu");
            longitude = SaisieObligatoireFloat("Veuillez saisir la longitude de votre lieu");*/
        }


        cout << "Veuillez saisir un environnement ( Environnement industriel(1), rural(2), urbain(3), industriel(4))\n";
        while((environnement != 1 && environnement != 2 && environnement != 3 && environnement != 4)){// On force sexagesimaux à prendre une valeur =1 , 2,3ou 4
            while (!(cin >> environnement)) { // On force environnement à prendre une valeur numérique
                cin.clear(); // Permet de clear l'entrée
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore l'entrée erronée
                cerr<<"Saisie erronée, veuillez verifier votre saisie (0 ou 1)\n";
            }

            if(environnement != 1 && environnement != 2 && environnement != 3 && environnement != 4){
                cerr<<"Saisie erronée, veuillez verifier votre saisie\n";
            }
        }

        while(!fin){
            cout << "Menu ? \n"
                 << "1.rayonnement global reu en un point du globe en fonction du jour de l'annee"<< annee<< endl
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
                    while(j < NB_JOUR_AN){
                        declinaison = CalculDeclinaison(NB_JOUR_AN,j);
                        // heuresolaire = CorrectionHeureLegal2Solaire(     );
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

