// Jacob Tidwell 12/6/2020 //

#include <iostream>
#include <fstream>
#include <cmath>
using namespace std; 

struct place{
int pcode;
string pname;
double plat;
double plng;
double d_link1;
double d_link2;
place* link1;
place* link2;
double distLen1;
double distLen2; 
};

int main(){
    
    fstream newfile("locationlist.txt",ios::in);    
    int n = 0; string tp;        
    while(!newfile.eof()){ 
        getline(newfile, tp);             
        n++;    
    }        
    newfile.close();   
    
    int numPlaces = n / 6;
    
    newfile.open("locationlist.txt",ios::in);    
    
    place myPlaces[numPlaces];  // array of places 
    place* placePtr;
    n = 0;
    
    while(!newfile.eof()){ 
        getline(newfile, tp);        
        myPlaces[n].pcode =stoi(tp);        
        getline(newfile, tp);        
        myPlaces[n].pname = tp;       
        getline(newfile, tp);        
        myPlaces[n].plat =stod(tp);        
        getline(newfile, tp);
        myPlaces[n].plng =stod(tp);
        getline(newfile, tp);
        myPlaces[n].d_link1 =stod(tp);
        getline(newfile, tp);
        myPlaces[n].d_link2 =stod(tp);
        n++;    
        
    }   
    newfile.close();  
    
  
    cout << "These are the places in the database: " << endl;
    
    for(int i = 0; i < numPlaces; i++){ 
        cout << myPlaces[i].pcode << " " << myPlaces[i].pname << " " << myPlaces[i].plat << " " << myPlaces[i].plng << endl;    
    }
    cout << endl << endl;
    
    place* tmp;
    place* placePtrArr[numPlaces];
    
    for (int k = 0; k < numPlaces; k++){
    placePtrArr[k] = &myPlaces[k];
    }
    
    for (int j = 0; j < numPlaces; j++){
        for (int i = 0; i < numPlaces - 1; i++){
            if (placePtrArr[i]->plat < placePtrArr[i + 1]->plat){
                tmp = placePtrArr[i];
                placePtrArr[i] = placePtrArr[i + 1];
                placePtrArr[i + 1] = tmp;
                break;
            }
        }
    }
    
    cout << "The order of the cities from north to south is: " << endl;
    for (int i = 0; i < numPlaces; i++){
        cout << placePtrArr[i]->pname << " " << placePtrArr[i]->plat << "  ";
    }
    cout << endl;
    
    for (int j = 0; j < numPlaces; j++){
        for (int i = 0; i < numPlaces - 1; i++){
            if (placePtrArr[i]->plng > placePtrArr[i + 1]->plng){
                tmp = placePtrArr[i];
                placePtrArr[i] = placePtrArr[i + 1];
                placePtrArr[i + 1] = tmp;
                break;
            }
        }
    }
    cout << endl;
    
    cout << "The order of the cities from east to west is: " << endl;
    for (int i = 0; i < numPlaces; i++){
        cout << placePtrArr[i]->pname << " " << placePtrArr[i]->plng << "  ";
    }
    cout << endl << endl << endl;
    
    double dist = 0;

    
    cout << "The current available flights are: ";
    for (int i = 0; i < n; i++){
        cout << endl;
            for (int k = 0; k < n; k++){
            
            dist = 60 * sqrt(pow((myPlaces[i].plng - myPlaces[k].plng),2)
            + pow((myPlaces[i].plat - myPlaces[k].plat),2));
            
            if (dist != 0 && myPlaces[i].d_link1 == myPlaces[k].pcode){
            cout << myPlaces[i].pcode << " " << myPlaces[i].pname << " to " << myPlaces[k].pcode << " " << myPlaces[k].pname << ": " << dist << " miles" << endl;
            myPlaces[i].distLen1 = dist;
            }
            
            if (dist != 0 && myPlaces[i].d_link2 == myPlaces[k].pcode){
            cout << myPlaces[i].pcode << " " << myPlaces[i].pname << " to " << myPlaces[k].pcode << " " << myPlaces[k].pname << ": " << dist << " miles" << endl;
            myPlaces[i].distLen2 = dist;
            }
        }
    }
    cout << endl;
    
    /*for (int i = 0; i < n; i++){
    cout << myPlaces[i].distLen1 << " " << myPlaces[i].distLen2 << endl;
    }
    cout << endl;*/
    
    int ccode1;
    int ccode2;
    double calDist;
    
    cout << "Enter the City code that you are traveling from: " << endl;
    cin >> ccode1;
    
    cout << "Enter the City code that you want to go to: " << endl;
    cin >> ccode2;
    
    cout << endl;
    for (int i = 0; i < n; i++){
        if (ccode1 == myPlaces[i].pcode){
            if (ccode2 == myPlaces[i].d_link1){
                cout << "Destination reached!" << endl;
                calDist = myPlaces[i].distLen1;
                cout << calDist << endl;
            }
            if (ccode2 == myPlaces[i].d_link2){
                cout << "Destination reached!" << endl;
                calDist = myPlaces[i].distLen2;
                cout << calDist << endl;
            }
        }
    }
    cout << endl;
    cout << "Finished!" << endl;

    return 0;
}

