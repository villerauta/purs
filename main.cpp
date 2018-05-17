#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>


using namespace std;

vector<string> lue_hinnasto(string filename){
    string line;
    ifstream hinnasto (filename);
    if (hinnasto.is_open())
    {
        int N = 56;
        int M = 1;
        vector<string> hinnat;

        for(int i = 0; i<N;++i)
        {
            getline(hinnasto,line,';');
        }

        while(getline(hinnasto,line))
        {

                for(int j = 0; j<M;++j)
                {
                    getline(hinnasto,line);
                }

                istringstream ss(line);
                string item;
                vector<string> splittedLine;

                while(getline(ss,item,';'))
                {
                    splittedLine.push_back(item);
                }

                if(splittedLine.size()>0)
                {
                    string out = splittedLine.at(0).substr(0,11);
                    hinnat.push_back(out);
                }

        }

        hinnasto.close();
        return hinnat;
    }

    else
    {
        cout << "Ei voida avata...";
    }

}

vector<string> lue_tyojono(string filename){
    string line;
    ifstream tyot (filename);
    if (tyot.is_open())
    {
        int N = 30;
        int M = 1;

        for(int i = 0; i<N;++i)
        {
            getline(tyot,line,';');
        }

        getline(tyot,line);
        string break_while = "t be display";
        int p = 13;
        vector<string> tyolista;
        while(getline(tyot,line))
        {
            istringstream ss(line);
            string item;
            vector<string> splittedLine;

            while(getline(ss,item,';'))
            {
                splittedLine.push_back(item);
            }

            if (splittedLine.at(3)==break_while)
            {
                break;
            }

            if(std::find(tyolista.begin(),tyolista.end(),splittedLine.at(3)) == tyolista.end())
            {
                tyolista.push_back(splittedLine.at(3));
            }
            ++p;
        }

        tyot.close();
        return tyolista;
    }

    else
    {
        cout << "Ei voida avata...";
    }

}

vector<string> vertaa( vector<string> hinnat, vector<string> tyolista){
    vector<string> puuttuvat;
    for(auto i = tyolista.begin(); i != tyolista.end();++i)
    {
        vector<string>::iterator it;
        it = find (hinnat.begin(),hinnat.end(),*i);
        if(it != hinnat.end()){
            //cout<<"Tyo loytyi: " << *i << endl;
        }
        else{
            //cout<<"Ei loytynyt: " << *i <<endl;
            puuttuvat.push_back(*i);
        }
    }
    return puuttuvat;
}

int main()
{
    vector<string> hinnat = lue_hinnasto("C:\\Users\\Ville\\Documents\\Qt\\logic\\hinnasto_koko.csv");

    vector<string> tyolista = lue_tyojono("C:\\Users\\Ville\\Documents\\Qt\\logic\\tyot_koko.csv");

    vector<string> puuttuvatHinnat = vertaa(hinnat,tyolista);

    sort(puuttuvatHinnat.begin(),puuttuvatHinnat.end());

    while(1){


        for (auto i = puuttuvatHinnat.begin(); i!= puuttuvatHinnat.end();++i){
            cout << *i <<endl;
        }

        string check;
        cout << "Mitä pois: ";
        getline(cin,check);
        size_t checkLenght = check.length();
        size_t k = 3;

        if(checkLenght > k ){
            for(auto it = puuttuvatHinnat.begin(); it!= puuttuvatHinnat.end();++it )
            {
                string nimike = *it;
                string vertaus = nimike.substr(0,checkLenght);
                if(vertaus==check)
                {
                    puuttuvatHinnat.erase(it);
                    --it;
                }

            }
        }

        sort(puuttuvatHinnat.begin(),puuttuvatHinnat.end());

    }

}
/*
 *         for(auto i = puuttuvatHinnat.begin(); i != puuttuvatHinnat.end();++i)
        {
            string nimike = *i;
            string vertaus = nimike.substr(0,checkLenght);

            if(nimike == vertaus){
                puuttuvatHinnat.erase(*i);
            }
            cout << *i << '\n';
        }*/

