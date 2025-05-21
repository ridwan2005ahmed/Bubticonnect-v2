#include<bits/stdc++.h>
using namespace std;

void maP() {int cnt=0;
   
    ifstream file("data/map.txt"); // Replace with your file name
    string keyword ; 
    cout<<"Enter facalty Name or room name"<<endl;
    getline(cin,keyword);
    if (cnt=!0)
 {
    system("cls");
    cout<<"Enter facalty Name or room name"<<endl;
    cout<<keyword<<endl;
    
 }
    transform(keyword.begin(), keyword.end(), keyword.begin(), ::tolower);
    string line;

  bool found = false;
 
 
    while (getline(file, line)) {
        string temp = line;
        transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
        if (temp.find(keyword) != std::string::npos) {

            cout << line << "\n"; found = true;      
        }
        
       

    }
 if(!found){cnt++;
    system("cls");cout<<"Data Not found"<<endl;maP();}
    file.close();

}
