#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>
#include <fcntl.h>
#include<windows.h>

#define I 4
#define M 6
#define N 30
#define MR 250


typedef unsigned char AdressIp[I];
typedef unsigned char Nom[N];
typedef unsigned char Logiciel[250];

//Liste Chainee des logiciels clients/Serveurs
typedef struct LogicielClient LogicielClient;
struct LogicielClient{
    char nom[50];
    LogicielClient* next;
};
typedef struct LogicielServeur LogicielServeur;
struct LogicielServeur{
    char nom[50];
    LogicielClient* next;
};




typedef struct ListeClient ListeClient;
struct ListeClient{
    LogicielClient* first;
};
typedef struct ListeServeur ListeServeur;
struct ListeServeur{
    LogicielServeur* first;
};





//la machine
typedef struct Machine Machine;
struct Machine{
   // int id;
    Nom nom;
    char marque; 
    bool connected;
    AdressIp ip;
    int nombreClient;
    int nombreServeur;
    Logiciel ListeClient[20];
    Logiciel ListeServeur[20];
};




//le parc
typedef struct Parc Parc;
struct Parc{
    Machine machines[250];//Tableau de 250 elements (Machines)
    int nombre;
};
Parc p;






//Le reseau
typedef struct Reseau Reseau;
struct Reseau
{
    Machine machines[250];
    int nombre;
};
Reseau R;





int MenuGeneral();







int comparerChaine(char* chaine1,char* chaine2){
    if(strlen(chaine1)!=strlen(chaine2)){
        return 0;    
    }
    else{
        int i;
        for ( i = 0; i < strlen(chaine1); ++i)
        {
            if(chaine1[i]!=chaine2[i]){
                return 0;
            }
        }
        return 1;
    }
    
}






void chaineNew(char* nom,char* chaineNew){
    int taille = strlen(nom);
    int i=0;
    while(nom[i]!='\n'){
        chaineNew[i]=nom[i];
        i++;
    }
    chaineNew[i]='\0';
}






void verifieMachine(Nom nom){
    FILE* fichier = fopen("parc1.txt","r");
    char chaine[30];
    if(fichier != NULL){
        int verifier = 1;
        while(verifier){
            rewind(fichier);
            verifier = 0;
            //printf("Donner l'ID de la machine: ");
            //scanf("%d", id);
            printf("Donner le nom de la machine: ");
            scanf("%s", nom);
            while(fgets(chaine,15,fichier)){
                char newChaine[30];
                chaineNew(chaine,newChaine);
                if(comparerChaine(newChaine,nom) == 1){
                    printf("Une machine du meme nom existe deja.\n");
                    verifier = 1;
                    break;
                }
            }
        }
    }
    else{
        printf("Nom de la machine: ");
        scanf("%s", nom);
    }
}





Machine saisirMachine(){
    char choix='N';
    int i=0,j=0;
    Machine m;
    verifieMachine(m.nom);
    m.nombreClient=0;
    m.nombreServeur=0;
    m.connected = false;
    do{
        int c;
        while ( ((c = getchar()) != '\n') && c != EOF);
        printf("Vous voulez installer un logiciel client? O/N : ");
        scanf("%c",&choix);
    }while(choix!='N' && choix!='n' && choix!='O' && choix!='o');
    while(choix=='O' || choix=='o'){
        printf("Entrez le nom du logiciel client: ");
        scanf("%s",m.ListeClient[i]);
        m.nombreClient++;
        i++;
        do{
            int c;
            while ( ((c = getchar()) != '\n') && c != EOF);
            printf("Vous voulez installer un autre logiciel client? O/N : ");
            scanf("%c",&choix);
        }while(choix!='N' && choix!='n' && choix!='O' && choix!='o');
    }
    // On demande si on veut installer des logiciels nombreServeur
    do{
        int c;              
        while ( ((c = getchar()) != '\n') && c != EOF);
        printf("Vous voulez installer un logiciel serveur? O/N : ");
        scanf("%c",&choix);
    }while(choix!='N' && choix!='n' && choix!='O' && choix!='o');
    while(choix=='O' || choix=='o'){
        printf("Entrez le nom du logiciel serveur: ");
        scanf("%s",m.ListeServeur[j]);
        m.nombreServeur++;
        j++;
        do{
            int c;
            while ( ((c = getchar()) != '\n') && c != EOF);
            printf("Vous voulez installer un autre logiciel serveur? O/N : ");
            scanf("%c",&choix);
        }while(choix!='N' && choix!='n' && choix!='O' && choix!='o');
    }
    
    return m;
}






void Ajout(){
        p.machines[p.nombre] = saisirMachine();

        p.nombre++;
}



void SaisirAdress(AdressIp ip){

    ip[0] = 10;
    ip[1] = 20;
    ip[2] = 30;
    ip[3] = R.nombre+1;
}




int IsOctet(int i){
    return i>=0 && i<256;
}



void affecterAdress(AdressIp ip){
    int i;
    for(i=0;i<I;i++){
        printf("%d", ip[i]);
        if(i<I-1)
            printf(".");
    }
}




void listeMachine(){
    int i;
    puts("\n");
    printf("^^^^^^^^^^^^^^Nombre de Machine^^^^^^^^^^^^^^^^^\n");
    puts("\n");
    printf("Il y a %d machine(s) dans le parc\n", p.nombre);
    puts("\n");
    printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
        for(i=0;i<p.nombre;i++)
        printf("%s\n", p.machines[i].nom);
}





void afficherMachine(Machine m){
    system("cls");

    //printf("ID : %d",m.id);
    //puts("");
    printf("Nom : %s",m.nom);
    puts("");
    if(!m.connected){
        printf("Indication Connection: %d(non connectee)",m.connected);
        puts("");
    }
    else{
        printf("Indication Connection: %d(connectee)",m.connected);
        puts("");
        printf("Adresse IP : "); affecterAdress(m.ip);
        puts("");
    }
    printf("Liste logiciel client: %d",m.nombreClient);
    puts("");
    int i;
    for(i=0;i<m.nombreClient;i++){
        printf("\t* %s\n",m.ListeClient[i]);
    }
    printf("Liste logiciel serveur: %d",m.nombreServeur);
    puts("");
    int j;
    for( j=0;j<m.nombreServeur;j++){
        printf("\t* %s\n",m.ListeServeur[j]);
    }
    
}






int strcmpIp(AdressIp ip1,AdressIp ip2){
    int i;
    for(i=0;i<I;i++){
        if(ip1[i] != ip2[i])
            return 0;
    }
    return 1;
}



void Rechercher(){
    int i=0;
    char nomChoisi[20];
    printf("Quelle machine souhaitez-vous afficher?\n");
    printf("Entrez son nom :");
    scanf("%s", nomChoisi);
    while (i<250 && strcmp(nomChoisi, p.machines[i].nom)) i++;
    if(i == 250) puts("Machine inexistante");
    else afficherMachine(p.machines[i]);
}






void supprimerMachine(){
    int i,j;
    char nomChoisi[30];
    printf("Quelle machine souhaitez-vous supprimer?\n");
    printf("Nom de la machine:");
    scanf("%s", nomChoisi);
    bool trouve = false;
    for(i=0;i<MR;i++)
        if((strcmp(nomChoisi, p.machines[i].nom)) == 0){
            trouve=true;
            for(j=i;j<MR-1;j++)
                p.machines[j]=p.machines[j+1];
            MR-1;
        }
    if (trouve)
    { 
        p.nombre--;
        printf("------------------------------------\n");
        printf("%s est supprimee avec succes\n", nomChoisi);
    }
    else{
        printf("------------------------------------\n");
        printf("%s n'existe pas dans le parc\n",nomChoisi );
    }
}







void sauvegarder(){
    printf("%d\n",p.nombre );
    FILE* fichier = fopen("parc1.txt","w");
    if(fichier!=NULL){
        int i;
        for ( i = 0; i < p.nombre; i++)
        { 
            fputs(p.machines[i].nom,fichier);
            fputs("\n",fichier);
        }
        fclose(fichier);
    }
    int i;
    for ( i = 0; i < p.nombre; i++)
    {
        int fic;
        fic = open(p.machines[i].nom, O_CREAT | O_TRUNC | O_RDWR, 777);
        write(fic, &p.machines[i],sizeof(Machine));
        close(fic);
    }
}







void import(){
    FILE* fichier = fopen("parc1.txt","r");
    char chaine[30];
    if (fichier!=NULL)
    {
        
        while(fgets(chaine,15,fichier)){
            char newChaine[30];
            chaineNew(chaine,newChaine);

            int i,fic;
            fic = open(newChaine, O_RDONLY);
            read(fic, &p.machines[p.nombre],sizeof(Machine));
            p.nombre++;
            close(fic);
        }
        fclose(fichier);
    }
}






void AjoutReseau(){
    int i=0;
    char nomChoisi[30];
    printf("Quelle machine souhaitez-vous ajouter?\n");
    printf("Entrez son nom :");
    scanf("%s", nomChoisi);
    while (i<250 && strcmp(nomChoisi, p.machines[i].nom)) i++;
    if(i == 250) puts("Cette machine n'existe pas dans le parc");
    else{
        p.machines[i].connected = true;
        SaisirAdress(p.machines[i].ip);
        R.machines[R.nombre]=p.machines[i];
        R.nombre++;
        printf("------ La machine est bien connecte au reseau --------\n");
    }
}






void listeReseau(){
    int i;
    puts("\n");
    printf("Il y a %d machine(s) dans le reseau\n", R.nombre);
    printf("--------------------------------\n");
        for(i=0;i<R.nombre;i++){

            printf("%s  : ", R.machines[i].nom);
            affecterAdress(R.machines[i].ip);
            printf("\n---\n");
        }
}







void RetirerReseau(){
    int i,j;
    char nomChoisi[30];
    printf("Quelle machine souhaitez-vous retirer du reseau?\n");
    printf("Entrez son nom:");
    scanf("%s", nomChoisi);
    bool trouve = false;
    for(i=0;i<MR;i++)
        if((strcmp(nomChoisi, R.machines[i].nom)) == 0){
            trouve=true;
            for(j=i;j<MR-1;j++)
                R.machines[j]=R.machines[j+1];
            MR-1;
        }
    if (trouve)
    { 
        R.nombre--;
        printf("------------------------------------\n");
        printf("%s est retiree avec succes\n", nomChoisi);

        int i=0;
        while (i<250 && strcmp(nomChoisi, p.machines[i].nom)) i++;
        if(i == 250) puts("Cette machine n'existe pas dans le parc");
        else{
            p.machines[i].connected = false;
        }
    }
    else{
        printf("------------------------------------\n");
        printf("%s n'existe pas dans le reseau\n",nomChoisi );
    }
}






void Ping(){
    puts("");
    printf("-----------Vous voulez faire un ping-----------");
    printf("Saisissez l'adresse ip: ");
    int a,b,c,d,i;
    AdressIp ip;
    do{
        i = scanf("%d.%d.%d.%d",&a,&b,&c,&d);
        if(i<4){
            puts("Adresse incorrecte");
            while (getchar()!='\n');
            continue;
        }
        if ((!(IsOctet(a) && IsOctet(b) && IsOctet(c) && IsOctet(d))))
            puts("Adresse incorrecte");
        else break;
    }while(1);
    ip[0] = (unsigned char)a;
    ip[1] = (unsigned char)b;
    ip[2] = (unsigned char)c;
    ip[3] = (unsigned char)d;

    //affecterAdress(ip);
    int j=0;
    while (j<250 && strcmpIp(ip, R.machines[j].ip)==0) j++;
    if(j == 250) puts("Cette machine n'existe pas dans le reseau");
    else{
        puts("Cette machine est dans le reseau");
        puts("--------");

        printf("PING ");
        puts("\n");
        printf(" : 56 data bytes\n");
        Sleep(2500);
       
        printf("64 bytes from %d.%d.%d.%d \n",a,b,c,d); Sleep(500); 
        puts("\n");
        printf(" : icmp_seq=0 ttl=64 time=3.186 ms\n");Sleep(500);
        Sleep(500);
        puts("\n");
        printf(" ping statistics ---\n");
        Sleep(2500);
        printf("2 packets transmitted, 2 packets received, 0.0%% packet loss\n");
        puts("\n");
        printf("round-trip min/avg/max/stddev = 2.183/2.684/3.186/0.501 ms\n");
        puts("\n");
        printf("Ping Reussie.\n");
        puts("\n");
        printf("%s : ",R.machines[j].nom);
        affecterAdress(R.machines[j].ip);
    }
}





int ta;
int extract(int x, int y, char *chaine, char *sChaine)
{
  int i=0, j=0;
  int taille = strlen(chaine);
  
  if( x > taille || x < 0 ){
    printf("Erreur\n");
    return 1;
  }
  if( y > taille ){
    printf("Erreur\n");
    return  0;
  } 
   i = x, j = 0; 
  while( i <= y){
    sChaine[j] = chaine[i];
    i++, j++;
  }  
  return 0;  
}

int Long(char* ch)
{
    int lg=0;
    while(*(ch+lg)!='\0')
    {
        lg++;
    }
    return lg;
}

void Ajouter_domaine()
{
    char dns[500]= "";

    printf("Veuillez Saisir l'Adresse IP du domaine, Nom du domaine \n");

    printf("\n");
    scanf("%s",dns);

    int autre=0;
    int longg = Long(dns);
    for (ta= 0;ta < longg; ++ta)
    {
        if (dns[ta] ==',')
        {
          autre = ta ;
        }
    }

    char nom[40];
    char ip[40];
    extract(0,autre-1,dns,ip);
    extract(autre+1,Long(dns)-1,dns,nom);

    printf("%s,%s\n",nom,ip);

    FILE *che = fopen("dns.txt","r");

    if (che == NULL)
    {
        FILE *file = fopen("dns.txt","w");

        fclose(file);
    }

    char domain_re[2500]= "";

    while( (fscanf(che,"%s\n",domain_re))!= EOF )
    {
        int longg = Long(domain_re);
        
        int autre=0;
        int ta ;
        for ( ta= 0;ta < longg; ++ta)
        {
            if (domain_re[ta] ==',')
            {
              autre= ta ;
            } 
        }

        char ipp[50];char nomm[150];
        extract(0,autre-1,domain_re,ipp);
        extract(autre+1,Long(domain_re),domain_re,nomm);
        int retour;
        
        if (!strncmp(nomm,nom,250))
        {
            printf("Nom de domaine configure\n");
            //menu();
        }
       
        if (!strncmp(ipp,ip,250))
        {
            printf("IP configuree\n");
            //menu();
        }
    }
    
    fclose(che);

    FILE *fcp = fopen("dns.txt","a+");

    if (fcp == NULL)
    {
        exit(1);
        printf("Erreur d'ecriture +\n");
    }


    fprintf(fcp,"%s\n",dns);

    printf("Configuration valide\n");

    fclose(fcp);
    
}

/*void Resoudre_domaine()
{
    FILE *fcp = fopen("dns.txt","r");

    if (fcp == NULL)
    {
        exit(1);
    }

    char dns[1024]   = "";
    char domain_re[1024]= "";

    printf("Entrer le nom du domaine : ");

    scanf("%s",domain_re);

    char* tab_nom[400]={};
    char* tab_ip[400]={} ;

    int index = 300;

    int i = 0;
    int j = 0;
    while( (fscanf(fcp,"%s\n",dns)) )
    {
        int longg = Long(dns);
        
        int autre=0;
        

        for ( ta = 0;ta< longg; ++ta)
        {
            if (dns[ta] ==',')
            {
              autre = ta;
            } 
        }
        
        char nomm[400]="";char ipp[400]="";

        extract(0,autre-1,dns,ipp);
            
        extract(autre+1,Long(dns),dns,nomm);

        tab_nom[i++] = nomm ;
        tab_ip[j++]  = ipp  ;

        printf("%s,%s\n",tab_nom[i-1],tab_ip[j-1]);
    }
    int z;
    for ( z= 0;z< i; ++z)
    {
        if (strcmp(tab_nom[z],domain_re))
        {
            index = z;
        }
        else
        {
            index = 300;
        }
    }

    printf("%s\n",domain_re);
    printf("%d\n",index);
    if (index == 300)
    {
        
    }
    else
    {
    
    }

    fclose(fcp);
}*/

void  voir_fichier()
{
    FILE *fcp = fopen("dns.txt","r");

    if (fcp == NULL)
    {
        exit(1);
    }

    char* tab_nom[500];
    char* tab_ip[500] ;
    char dns[2500]= "";

    while( (fscanf(fcp,"%s\n",dns))!= EOF)
    {
        int longg = Long(dns);
        int i = 0;
        
        int autre=0;

        for (ta= 0; ta< longg; ++ta)
        {
            if (dns[ta] ==',')
            {
              autre = ta;
            } 
        }
        
        char nomm[500]="";char ipp[500]="";

                extract(0,autre-1,dns,ipp);
            
                extract(autre+1,Long(dns),dns,nomm);

            *(tab_nom+i) = nomm ;
            *(tab_ip+i)  = ipp ;

            printf("\n");
            printf("%s,%s\n",tab_ip[i],tab_nom[i]); 
        i++;
    }   
}

void GestionParc(){
    int choix,test;
    system("cls");
    do{
        puts("\n");
        puts("^^^^^^^^^^^^^^^ MENU: Gestion Parc ^^^^^^^^^^^^^^^^");
        puts("\n");
        puts(" 1) Ajouter une machine dans le parc");
        puts(" 2) Retirer une machine du parc");
        puts(" 3) Afficher les informations d'une machine");
        puts(" 4) Lister les machines du parc");
        puts(" 5) Effacer ecran");
        puts(" 6) Accueil");
        puts("\n");
        puts("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^");
        printf("Quel est votre choix: ");
        test = scanf("%d",&choix);

        while(test==0 || choix<1 || choix > 10 ){
            int c;
            while ( ((c = getchar()) != '\n') && c != EOF);
            printf("\a!!!Choix incorrect!!! Retapez: ");
            test = scanf("%d",&choix);
        }
        switch(choix){
            case 1 : Ajout(); break;
            case 2 : supprimerMachine(); break;
            case 3 : Rechercher(); break;
            case 4 : listeMachine(); break;
            case 5: system("cls"); break;
            case 6: MenuGeneral(); break;
        }
    }while(choix!=6 );
}

void GestionReseau(){
    int choix,test;
    system("cls");
    do{
        puts("\n");
        puts("^^^^^^^^^^^^^^^^^^^^^^Gestion Reseau ^^^^^^^^^^^^^^^^^^^^^^^^");
        puts(" 1- Ajouter une machine dans le reseau");
        puts(" 2- Retirer une machine du reseau");
        puts(" 3- Faire un ping");
        puts(" 4- Afficher les machines en reseau");
        puts(" 5- Effacer l'ecran");
        puts(" 6- Accueil");
        puts("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^");
        printf("Quel est votre choix: ");
        test = scanf("%d",&choix);

        while(test==0 || choix<1 || choix > 6){
            int c;
            while ( ((c = getchar()) != '\n') && c != EOF);
            printf("!!!Choix incorrect!! Retapez: ");
            test = scanf("%d",&choix);
        }
        switch(choix){
            case 1 : AjoutReseau(); break;
            case 2 : RetirerReseau(); break;
            case 3 : Ping(); break;
            case 4 : listeReseau(); break;
            case 5: system("cls"); break;
            case 6: MenuGeneral(); break;
        }
    }while(choix!=6);
}

void GestionDNS(){
    int choix,test;
    system("cls");
    do{
        puts("\n");
        puts("^^^^^^^^^^^^^^^^^^^^^^ MENU: Gestion DNS ^^^^^^^^^^^^^^^^^^^^^^^^");
        puts(" 1- Ajouter un nom de domaine");
        puts(" 2- Afficher le fichier");
        puts(" 3- Effacer l'ecran");
        puts(" 4- Accueil");
        puts("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^");
        printf("Quel est votre choix: ");
        test = scanf("%d",&choix);

        while(test==0 || choix<1 || choix > 4){
            int c;
            while ( ((c = getchar()) != '\n') && c != EOF);
            printf("!!!Choix incorrect!! Retapez: ");
            test = scanf("%d",&choix);
        }
        switch(choix){
            case 1 : Ajouter_domaine(); break;
            case 2 : voir_fichier(); break;
            case 3: system("cls"); break;
            case 4: MenuGeneral(); break;
        }
    }while(choix!=4);
}

int MenuGeneral(){
    int choix,test;
    system("cls");
    puts("\n");
    puts("^^^^^^^^^^^^^^^^^^^^^^^ MENU ^^^^^^^^^^^^^^^^^^^^^^^");
    puts(" 1- GERER PARC");
    puts(" 2- GERER RESEAU");
    puts(" 3- CONFIGURATION DNS");
    puts(" 4- EFFACER ECRAN");
    puts(" 5- QUITTER");
    puts("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^");
    printf("Quel est votre choix: ");
    test = scanf("%d",&choix);

    while(test==0 || choix<1 || choix > 5){
        int c;
        while ( ((c = getchar()) != '\n') && c != EOF);
        printf("\a!!!Choix incorrect!!! Retapez: ");
        test = scanf("%d",&choix);
    }
    switch(choix){
        case 1 : GestionParc(); break;
        case 2 : GestionReseau(); break;
        case 3 : GestionDNS(); break;
        case 4 : system("cls"); break;
        case 5: puts("^^^^^^^^^^^");
            puts("Sauvegarde des donnee du parc");
            sauvegarder();
            printf("Ciao Ciaooo!!!!!\n");
    }
}


int main()
{
    p.nombre=0;
    R.nombre=0;
    import();
    MenuGeneral();
    return 0;
}

