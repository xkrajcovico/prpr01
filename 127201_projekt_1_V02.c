#include <stdio.h>  
#include <stdlib.h>
#include <string.h>
//funcions: 
// v - print
// n - napln
// c - ciachovanie
// s - output in text
// h - histogram
// z - zmaz
// k - ukonci
// x - vytvor osoby
// y - print osoby

//my functions
char **alokuj(int x, int y) {                                          //alokacia
    char **p = (char **)malloc(x * sizeof(char *));
    for(int i = 0; i < x; i++)  
        p[i] = (char *)malloc(y * sizeof(char));
    return p;
}

void dealokuj(char **matrix, int x) {                                  //dealokacia
    for(int i = 0; i < x; i++) {
        free(matrix[i]);
        matrix[i] = NULL;  
    }
    free(matrix);
    matrix = NULL;
}

char strip(char *str) {                                                //odstranenie /n na konci inputu
    char *strip_str = str + strlen(str) - 1;
    while (strip_str > str && *strip_str == '\n') {
        strip_str--;
    }
    *(strip_str + 1) = '\0';
    return *strip_str;
}

int compare(const void *str_vstup_1, const void *str_vstup_2) {       //compare pre qsort v s
    const char *str_1 = *(const char **)str_vstup_1;
    const char *str_2 = *(const char **)str_vstup_2;
    return strcmp(str_1, str_2);
}

void v_function(int *n,FILE **dataloger, char ***id, char ***pozicia, char ***typ_veliciny, double **hodnota, char ***cas, char ***datum)
{
    char ch_txt[50];
    //  zistí, či dataloger.txt je otvoreny. Ak nie, skúsi ho otvoriť. ak  sa  súbor  nepodarí  otvoriť: print: Neotvoreny  subor
    if(*dataloger == NULL) {
        *dataloger = fopen("dataloger.txt","r");

        if(*dataloger == NULL)
        {
            printf("Neotvoreny subor\n");
        }
    }

    //  zistí či sú polia alokované, ak nie: print: obsah: dataloger.txt. Ak ano: naplni polia
    if (*id == NULL || *pozicia == NULL || *typ_veliciny == NULL || *hodnota == NULL || *cas == NULL || *datum == NULL)
    {
        // print: obsah dataloger.txt
        int i = 0;
        while (fgets(ch_txt,50,*dataloger) != NULL)
        {       
            switch (i)
            {
                case 0:
                    printf("ID  mer. modulu: %s", ch_txt);
                    i++;
                    break;
                case 1:
                    printf("Pozicia modulu: %s", ch_txt);
                    i++;
                    break;
                case 2:
                    printf("Typ mer. veliciny: %s", ch_txt);
                    i++;
                    break;
                case 3:
                    printf("Hodnota: %s", ch_txt);
                    i++;
                    break;
                case 4:
                    printf("Cas merania: %s", ch_txt);
                    i++;
                    break;
                case 5:
                    printf("Datum merania: %s", ch_txt);
                    i++;
                    break;
                case 6:
                    printf("\n");
                    i = 0;
                    break;
            }
            // printf("i = %d\n",i);
            
        }
    rewind(*dataloger);
    }
    
    else
    {
    for (int i = 0; i < (*n); i++)
    {
         for (int j = 0; j < 7; j++)
        {      
            switch (j)
            {
                case 0:
                    printf("ID  mer. modulu: %s\n", (*id)[i]);
                    // i++;
                    break;
                case 1:
                    printf("Pozicia modulu: %s\n", (*pozicia)[i]);
                    // i++;
                    break;
                case 2:
                    printf("Typ mer. veliciny: %s\n", (*typ_veliciny)[i]);
                    // i++;
                    break;
                case 3:
                    printf("Hodnota: %lf\n", (*hodnota)[i]);
                    // i++;
                    break;
                case 4:
                    printf("Cas merania: %s\n", (*cas)[i]);
                    // i++;
                    break;
                case 5:
                    printf("Datum merania: %s\n", (*datum)[i]);
                    // i++;
                    break;
                case 6:
                    printf("\n"); 
                    // i = 0;
                    // j++;
                    break;
            }
        }
    }

    rewind(*dataloger);

    }
}

void n_function(int *n, FILE **dataloger, char ***id, char ***pozicia, char ***typ_veliciny, double **hodnota, char ***cas, char ***datum)
{
    // zisti ci je dataloger otvoreny
    if(*dataloger == NULL)
    {
        printf("Neotvoreny subor\n");
        return;
    }
    // zrata dlzku suboru
    char ch_txt[50];
    int i = 0;
    while (fgets(ch_txt,50,*dataloger) != NULL){
        if(ch_txt[0] == '\n'){
            (*n)++;
            i = 0;
        }
        else{
            i++;
        }
    }
    if(i < 7)
        (*n)++;
    // printf("n = %d\n",(*n));
    rewind(*dataloger);


    // alokuje polia
    *id = alokuj((*n), 5);
    *pozicia = alokuj((*n),15);
    *typ_veliciny = alokuj((*n),3);
    *hodnota = (double *)malloc((*n) * sizeof(double));
    *cas = alokuj((*n),5);
    *datum = alokuj((*n),9);

    // v loope naplni polia
    for (int i = 0; i < *n; i++){
        for (int j = 0; j < 7; j++)
            {
                fgets(ch_txt,50,*dataloger);
                strip(ch_txt);
                switch (j)
                {
                    case 0:
                        strcpy((*id)[i], ch_txt);
                        break;
                    case 1:
                        strcpy((*pozicia)[i], ch_txt);
                        break;
                    case 2:
                        strcpy((*typ_veliciny)[i], ch_txt);                
                        break;
                    case 3:
                        (*hodnota)[i] = atof(ch_txt);// ina syntax lebo pole: double namiesto 2d pola char
                        break;
                    case 4:
                        strcpy((*cas)[i], ch_txt);                
                        break;
                    case 5:
                        strcpy((*datum)[i], ch_txt);                
                        break;
                    case 6:
                        break;
                }
            }
    }
    rewind(*dataloger);
}

void c_function(int *n, FILE **ciachovanie, char ***id, char ***datum) {

    if (*id == NULL || *datum == NULL) {
        printf("Polia nie su vytvorene.\n");
        return;
    }

    *ciachovanie = fopen("ciachovanie.txt", "r");

    if (*ciachovanie == NULL) {
        printf("Subor ciachovanie.txt sa nepodarilo otvorit.\n");
        return;
    }

    int Y, data_su_korektne = 0;
    scanf("%d", &Y);

    // Zrata pocet zaznamov v ciachovanie
    char pocet[100];
    int n_c = 0;
    while (fgets(pocet, sizeof(pocet), *ciachovanie)) {
        n_c++;
    }
    n_c /= 3;
    rewind(*ciachovanie);

    for (int i = 0; i < (*n); i++) {        //for v poli
        int found_in_ciachovanie = 0;

        rewind(*ciachovanie);
        
        int datum_merania = atoi((*datum)[i]);  // z pola na datum do roku a mesiacu
        int year = datum_merania / 10000;
        int month = (datum_merania % 10000) / 100;
        for (int j = 0; j < n_c; j++) {         //for v ciach
            char id_ciachovania[6];
            char scan_datum_ciachovania[9];

            if (fscanf(*ciachovanie, "%5s %8s", id_ciachovania, scan_datum_ciachovania) != 2) {     //scan okrem \n
                break;
            }

            if (strcmp(id_ciachovania, (*id)[i]) == 0) {
                found_in_ciachovanie = 1;
                int datum_ciachovania = atoi(scan_datum_ciachovania);       //scan to 
                int year_c = datum_ciachovania / 10000;
                int month_c = (datum_ciachovania % 10000) / 100;
                int rozdiel = abs(year - year_c)*12 + abs(month - month_c); //rozdiel v mesiacoch

                if (rozdiel >= Y) {
                    printf("ID. mer. modulu [%s] ma %d mesiacov po ciachovani\n", id_ciachovania, rozdiel);
                    data_su_korektne++;
                    // found_in_ciachovanie = 0;
                    break;
                }
            }
        }

        if (found_in_ciachovanie == 0) {
            printf("ID. mer. modulu [%s] nie je ciachovany\n", (*id)[i]);
            data_su_korektne++;
            break;
        }
    }

    if (data_su_korektne == 0) {
        printf("data su korektne\n");
    }

    fclose(*ciachovanie);
}

void s_function(int *n, FILE **vystup_S, char ***id, char ***pozicia, char ***typ_veliciny, double **hodnota, char ***cas, char ***datum)
{
    if (*id == NULL || *pozicia == NULL || *typ_veliciny == NULL || *hodnota == NULL || *cas == NULL || *datum == NULL)
    {
        printf("Polia nie su vytvorene\n");
        return;
    }
    else
    {
        int count = 0;
        char scan_id[6];
        char scan_typ_veliciny[4];
        char **pole_indexov = alokuj((*n), 13);
        scanf("%5s %3s", scan_id, scan_typ_veliciny);

        for (int i = 0; i < *n; i++) //zrata matching zaznamy
        {
            if (strcmp((*typ_veliciny)[i], scan_typ_veliciny) == 0 && strcmp((*id)[i], scan_id) == 0)
            {
                sprintf(pole_indexov[count], "%s%s%d", (*datum)[i], (*cas)[i], i);
                count++;
            }
        }
        qsort(pole_indexov, count, sizeof(char *), compare);          //sort

        *vystup_S = fopen("vystup_S.txt", "w");                                 //open
        if (*vystup_S == NULL)
        {
            printf("Pre  dany  vstup  nie  je  vytvoreny  txt subor\n");
            return;
        }
        if (count == 0)
        {
            printf("Pre  dany  vstup  neexistuju  zaznamy\n");
            return;
        }
        for (int i = 0; i < count; i++)                                         //for in pole_indexov  arrays to array
        {         
            int ii = atoi(&pole_indexov[i][strlen(pole_indexov[i]) - 1]);
            char znamienko_longitude,znamienko_latitude;
            int pozicia_longitude_pred_bodkov, pozicia_latitude_pred_bodkov, pozicia_longitude_po_bodke, pozicia_latitude_po_bodke;                                       
            sscanf((*pozicia)[ii],"%c%2d%4d%c%2d%4d",&znamienko_longitude, &pozicia_longitude_pred_bodkov, &pozicia_longitude_po_bodke, &znamienko_latitude, &pozicia_latitude_pred_bodkov, &pozicia_latitude_po_bodke);
            fprintf(*vystup_S,"%s%s\t%.5lf\t%c%2d.%4d\t%c%2d.%4d\n",(*datum)[ii],(*cas)[ii], (*hodnota)[ii], znamienko_longitude,pozicia_longitude_pred_bodkov,pozicia_longitude_po_bodke,znamienko_latitude,pozicia_latitude_pred_bodkov,pozicia_latitude_po_bodke); // fprintf(*vystup_S,"\t%s",latitude, longitude)
        }
        dealokuj(pole_indexov, count);                             //dealokuj polia pre s
        fclose(*vystup_S);
        }
    }

void h_function(int *n, char ***typ_veliciny, double **hodnota)
{
    if (typ_veliciny != NULL && hodnota != NULL) // zisti ci su polia naplnene
    {
        int i,j;
        double *min = (double*)malloc(2 * sizeof(double)); // def min
        double *max = (double*)malloc(2 * sizeof(double)); // def max
        int *pocetnost = (int*)malloc(2 * sizeof(int));      // pocitadlo pocetnost pre print
        
        for (i = 0; i < 6; i++) // naplni polia 0 - ami
        {
            max[i] = 0;
            min[i] = 0;
            pocetnost[i] = 0;           
        }
 
        char* velicina[] = { "RD", "RM", "RO", "PI", "PE", "PA" };
        // vo for-e prechadza typmy velicini a ak sa z listu rovna najde max
        for (i = 0; i < (*n); i++)
        {
            for (j = 0; j < 6; j++)
            {
                if (strcmp((*typ_veliciny)[i], velicina[j]) == 0)
                {
                    if(min[j] == 0) //hlada min
                    {
                        min[j] = (*hodnota)[i];
                    }
                    if (min[j] >= (*hodnota)[i])
                    {
                        min[j] = (*hodnota)[i];
                    }

                    if(max[j] == 0) // hlada max
                    {
                        max[j] = (*hodnota)[i];
                    }
                    if (max[j] <= (*hodnota)[i])
                    {
                        max[j] = (*hodnota)[i];
                    }

                    pocetnost[j]++; //pridava pocetnost k velicine napr{}

                    break;

                }
            }
        }

        printf("\nTyp mer. vel.\tPocetnost\tMinimum\t    Maximum\n");
        for (int i = 0; i < 6; i++)
        {
            if(pocetnost[i] != 0)
            {
                printf("%s\t\t    %d\t\t%.2lf\t    %.2lf\n", velicina[i], pocetnost[i], min[i], max[i]);           
            }
        }

        free(pocetnost); 
        pocetnost = NULL;
        free(max);
        max = NULL;
        free(min);
        min = NULL;
    }
    else
    {
        printf("Polia nie su vytvorene.\n");
    }
}

void z_function(int *n, char ***id, char ***pozicia, char ***typ_veliciny, double **hodnota, char ***cas, char ***datum)
{
    if (*id == NULL || *pozicia == NULL || *typ_veliciny == NULL || *hodnota == NULL || *cas == NULL || *datum == NULL) 
    {
        printf("Polia nie su vytvorene\n");
        return;
    }
    else // zisti ci su polia plne
    {
        int count = 0;
        char scan_id[5];
        char ch = '\n';
        scanf ("%6s",scan_id);
        
        for (int i = 0; i < (*n); i++) // prechadza polia cyklom
        {
            if (strcmp((*id)[i],scan_id) == 0)
            {
                for(int j = i; j < (*n); j++) // n kratposunie kazdy dalsi prvok pola - zmaze j ty prvok pola
                {
                    (*id)[j] = (*id)[j + 1];
                    (*pozicia)[j] = (*pozicia)[j + 1];
                    (*typ_veliciny)[j] = (*typ_veliciny)[j + 1];
                    (*hodnota)[j] = (*hodnota)[j + 1];
                    (*cas)[j] = (*cas)[j + 1];
                    (*datum)[j] = (*datum)[j + 1];
                }
                count ++;
                i--;
                *id = (char **)realloc(*id, (*n) * sizeof(char *));
                *pozicia = (char **)realloc(*pozicia, (*n) * sizeof(char *));
                *typ_veliciny = (char **)realloc(*typ_veliciny, (*n) * sizeof(char *));
                *hodnota = (double *)realloc(*hodnota, (*n) * sizeof(double));
                *cas = (char **)realloc(*cas, (*n) * sizeof(char *));
                *datum = (char **)realloc(*datum, (*n) * sizeof(char *));
                (*n)--;
            }
        }
        printf("Vymazalo sa : %d zaznamov !\n",count);
    }
}

void vytvor_zoznam(int *n, char ***zoznam_mien,char ***id, char ***pozicia, char ***typ_veliciny, double **hodnota, char ***cas, char ***datum){
    //podmienka
    if (*id == NULL || *pozicia == NULL || *typ_veliciny == NULL || *hodnota == NULL || *cas == NULL || *datum == NULL){
        printf("Polia nie su vytvorene\n");
        return;
    }
    //inicializacia
    *zoznam_mien = alokuj((*n), 15);
    char ch_txt[15];
    char ii[2];
    //filling variables
    for (int i = 0; i < (*n); i++)
    {
        //terminal to variable
        printf("zadaj osobu[%d]: ",i);
        scanf("%s",ch_txt);
        strcpy((*zoznam_mien)[i],ch_txt);
        //control if not already in lsit
        for (int j = 0; j < i; j++)
        {
            if(strcmp(ch_txt,(*zoznam_mien)[j]) == 0)
            {
                printf("Meno uz je v zozname\n");
                i--;
                break;
            }
        }
        
    }
    //add a serial number
    for (int i = 0; i < (*n); i++)
    {
        sprintf(ii,"%d",i);
        strcat((*zoznam_mien)[i],ii);
    }
    
    //sort
    qsort((*zoznam_mien), (*n), sizeof(char *), compare);          //sort
    
    char **new_id = alokuj((*n), 5);
    char **new_pozicia = alokuj((*n), 15);
    char **new_typ_veliciny = alokuj((*n), 3);
    double *new_hodnota = (double * )malloc((*n) * sizeof(double));
    char **new_cas = alokuj((*n), 5);
    char **new_datum = alokuj((*n), 9);

    // Process and copy data
    for (int i = 0; i < (*n); i++) {
        // Extract serial number from zoznam_mien
        int serial_number = (*zoznam_mien)[i][strlen((*zoznam_mien)[i]) - 1] - '0';
            zoznam_mien[strlen((*zoznam_mien)[i])-1] = '\0';
        // Copy data from original arrays to new lists
        strcpy(new_id[serial_number], (*id)[i]);
        strcpy(new_pozicia[serial_number], (*pozicia)[i]);
        strcpy(new_typ_veliciny[serial_number], (*typ_veliciny)[i]);
        new_hodnota[serial_number] = (*hodnota)[i];
        strcpy(new_cas[serial_number], (*cas)[i]);
        strcpy(new_datum[serial_number], (*datum)[i]);
    }

    // Deallocate original arrays
    for (int i = 0; i < (*n); i++) {
        free((*id)[i]);
        free((*pozicia)[i]);
        free((*typ_veliciny)[i]);
    }
    free(*id);
    free(*pozicia);
    free(*typ_veliciny);
    free(*hodnota);
    free(*cas);
    free(*datum);

    //change pointers

    *id = new_id;
    *pozicia = new_pozicia;
    *typ_veliciny = new_typ_veliciny;
    *hodnota = new_hodnota;
    *cas = new_cas;
    *datum = new_datum;
}

void vypis_zoznamu (int *n, char ***zoznam_mien){
    if (*zoznam_mien == NULL){
        printf("Nevytvoreny zoznam\n");
        return;
    }
    for (int i = 0; i < (*n); i++)
    {
        printf("osoba[%d] = ",i);
        for (int j = 0; j < strlen((*zoznam_mien)[i])-1; j++)
        {
            printf("%c",(*zoznam_mien)[i][j]);
        }
        printf("\n");
    }
}

int main() {
    char **zoznam_mien = NULL;

    char **id = NULL; 
    char **pozicia = NULL;
    char **typ_veliciny = NULL;
    double *hodnota = NULL;
    char **cas = NULL;
    char **datum = NULL;
    FILE *dataloger = NULL;
    FILE *ciachovanie = NULL;
    FILE *vystup_S = NULL;
    int n = 0;
    char input;
    
    while ((input= getc(stdin))!= 'k')
    {
        switch (input)
        {
        case 'v':{
            v_function(&n, &dataloger, &id, &pozicia, &typ_veliciny, &hodnota, &cas, &datum);
            break;
        }
        case 'n':{
            n_function(&n, &dataloger, &id, &pozicia, &typ_veliciny, &hodnota, &cas, &datum);
            break;
        }
        case 'c':{
            c_function(&n, &ciachovanie, &id, &datum);
            break;
        }
        case 's':{
            s_function(&n, &vystup_S, &id, &pozicia, &typ_veliciny, &hodnota, &cas, &datum);
                break;
        }   
        case 'h':{
            h_function(&n, &typ_veliciny, &hodnota);
            break;
        }
        case 'z':{
            z_function(&n, &id, &pozicia, &typ_veliciny, &hodnota, &cas, &datum);
            break;
        }
        case 'x':{
            vytvor_zoznam(&n, &zoznam_mien, &id, &pozicia, &typ_veliciny, &hodnota, &cas, &datum);
            break;
        }
        case 'y':{
            vypis_zoznamu(&n, &zoznam_mien);
            break;
        }
        default:
            break;
        }
    } 
    dealokuj(zoznam_mien, 15);
    dealokuj(id, 5);
    dealokuj(pozicia, 14);
    dealokuj(typ_veliciny, 2);
    free(hodnota);
    dealokuj(cas, 4);
    dealokuj(datum, 8);
    if (dataloger !=NULL)
        fclose(dataloger);
    if (ciachovanie !=NULL)
        fclose(ciachovanie);
    if (vystup_S !=NULL)
        fclose(vystup_S);
    return 0;
}