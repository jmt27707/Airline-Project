// Jacob Tidwell 12/12/2020 //

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
    
    for (int i = 0; i < n; i++){
        int changer;
        cout << myPlaces[i].pcode << " " << myPlaces[i].pname << " is linked to: " << myPlaces[i].d_link1 << " and " << myPlaces[i].d_link2 << endl;
        cout << "Which links would you like to modify? 1 = change link #1, 2 = change link #2, 3 = change both, 0 = change none of the links." << endl;
        cin >> changer;
        if (changer == 1){
            cout << "What would you like to change link #1 to?" << endl;
            cin >> myPlaces[i].d_link1;
        }
        if (changer == 2){
            cout << "What would you like to change link #2 to?" << endl;
            cin >> myPlaces[i].d_link2;
        }
        if (changer == 3){
            cout << "What would you like to change link #1 to?" << endl;
            cin >> myPlaces[i].d_link1;
            cout << "What would you like to change link #2 to?" << endl;
            cin >> myPlaces[i].d_link2;
        }
        if (changer == 0){
            cout << "The links will remain unchanged." << endl;
        }
        cout << endl;
    }
    cout << endl;
    
    
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
                cout << "The distance is: " << calDist << endl;
                cout << "It took 1 hop." << endl;
            }
            if (ccode2 == myPlaces[i].d_link2){
                cout << "Destination reached!" << endl;
                calDist = myPlaces[i].distLen2;
                cout << "The distance is: " << calDist << endl;
                cout << "It took 1 hop." << endl;
            }
        }
    }
    cout << endl;

    return 0;
}

