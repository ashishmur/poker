//
//  main.cpp
//  Poker Dealer
//
//  Created by Ashish Muralidharan on 30/04/15.
//  Copyright (c) 2015 Ashish Muralidharan. All rights reserved.
//

#include <iostream>
#include <string>

using namespace std;

int main(int argc, const char * argv[]){
    int pl_num;
    int flag=1;
    string name[9];
    int credit[9];
    int game=0;
    int sm_blind;
    int big_blind;
    char option;
    int min_bet=0;
    int fold[8];
    int flag_fold=0;
    int present;
    int opt;
    int rnd_pot[9];
    int chck_pot[9];
    int tot_pot=0;
    int call=0;
    int raise=0;
    int fl=0;
    int chance=5;
    int j;
    int k;
    int check=0;
    int game_flag;
    int bet=0;
    
    while(flag==1){
        cout<<"\n Enter the number of players \n";
        cin>>pl_num;
        if (pl_num>=9) {
            flag=1;
        }
        else flag=0;
    }
    
    for(int i=0;i<pl_num;i++){
        cout<<" Please enter the name of Player:  "<<i+1<<"\n";
        cin>>name[i];
    }
    cout<<"\n Please add credit to the Players: \n";
    for(int i=0;i<pl_num;i++){
        cout<<"Enter Credit for  "<<name[i]<<"\n";
        cin>>credit[i];
    }
    cout<<"  \n Enter the minimum Betting Amount \n";
    cin>>min_bet;
    
    for(int i=0;i<pl_num;i++){
        rnd_pot[i]=0;
    }
    
    
    cout<<"\n  Game Begins!! \n\n\n";
    game_flag=1;
    while(game_flag==1){
        cout<<"Credit for  \n";
        for(int i=0; i<pl_num;i++){
            cout<<name[i]<<"  is"<<credit[i]<<"\n";
        }
        for(int i=0;i<8;i++){
            fold[i]=-1;
        }
        flag_fold=0;
        
        sm_blind=game%pl_num;
        big_blind=game%pl_num+1;
        big_blind=big_blind%pl_num;
        cout<<"\n Small Blind is:  "<<name[sm_blind];
        cout<<"\n Small Blind bets  "<<min_bet;
        credit[sm_blind]=credit[sm_blind]-min_bet;
        tot_pot=tot_pot+min_bet;
        rnd_pot[sm_blind]=rnd_pot[sm_blind]+min_bet;
        chance--;
        cout<<"\n Choose to fold? (Y/N)  \n";
        cin>>option;
        if (option=='Y' || option=='y') {
            fold[flag_fold]=sm_blind;
            flag_fold++;
        }
        
        cout<<"Credit for \n";
        for(int i=0; i<pl_num;i++){
            cout<<name[i]<<"  is"<<credit[i]<<"\n";
        }
        
        
        cout<<"\n Big blind is: "<<name[big_blind];
        cout<<"\n Big blind bets:  "<<(2*min_bet);
        credit[big_blind]=credit[big_blind]-(min_bet*2);
        tot_pot=tot_pot+(2*min_bet);
        rnd_pot[big_blind]=rnd_pot[big_blind]+(2*min_bet);
        chance--;
        cout<<"\n  choose to fold?  (Y/N)  \n" ;
        cin>>option;
        if(option=='Y' || option=='y'){
            fold[flag_fold]=big_blind;
            flag_fold++;
        }
        
        present=(big_blind+1)%pl_num;
        flag=1;
        while (flag==1){
            
            fl=0;
            for(int i=0;i<pl_num;i++){
                if(present==fold[i]){
                    fl=1;
                    chance--;
                    present++;
                    present=present%pl_num;
                }
            }
            if(fl==0){
                
                cout<<"credit for  \n";
                for(int i=0;i<pl_num;i++){
                    cout<<name[i]<<"  is"<<credit[i]<<"\n";
                }
                
                call=*max_element(rnd_pot, rnd_pot+9);
                cout<<"\n Player   "<<name[present];
                cout<<"\n Choose  1.Bet 2. Check  3.Call  4.Raise  5. Fold";
                cin>>opt;
                if(opt==1){
                    cout<<"Please enter the amount to bet: \n";
                    cin>>bet;
                    cout<<"\n Player "<<name[present]<<"  starts bet with "<<bet;
                    credit[present]=credit[present]-bet;
                    tot_pot=tot_pot+bet;
                    rnd_pot[present]=rnd_pot[present]+bet;
                    chance--;
                }
                if(opt==2){
                    cout<<"\n Player Checks \n";
                    chance--;
                }
                if(opt==3){
                    cout<<"\n Player "<<name[present]<<" bets"<<(call-rnd_pot[present])<<"\n";
                    credit[present]=credit[present]-(call-rnd_pot[present]);
                    tot_pot=tot_pot+(call-rnd_pot[present]);
                    rnd_pot[present]=call;
                    chance--;
                }
                if(opt==4){
                    cout<<"Enter the amount to raise the previous bet by:  \n";
                    cin>>raise;
                    cout<<"\n Player bets  "<<(call+raise-rnd_pot[present])<<"\n";
                    tot_pot=tot_pot+(call+raise-rnd_pot[present]);
                    rnd_pot[present]=(call+raise);
                    credit[present]=credit[present]-(call+raise);
                    chance--;
                    
                }
                if(opt==5){
                    cout<<"Player   "<<name[present]<<" folds!!! \n\n";
                    fold[flag_fold]=present;
                    flag_fold++;
                    chance--;
                }
                
                
                present++;
                present=present%pl_num;
                k=0;
            }
            if(chance<=0){
                for(int i=0;i<pl_num;i++){
                    check=0;
                    for(j=0;j<=flag_fold;j++){
                        if(i==fold[j]) check=1;
                    }
                    if(check==0) {
                        chck_pot[k]=rnd_pot[i];
                        k++;
                    }
                }
                if (*max_element(chck_pot,chck_pot+(pl_num-flag_fold))==*min_element(chck_pot,chck_pot+(pl_num-flag_fold))){
                    cout<<"\n \n Please Reveal the next set of cards \n \n";
                    for(int i=0;i<pl_num;i++){
                        rnd_pot[i]=0;
                    }
                    chance=5;
                    cout<<"Has everyone displayed the cards?  (Y/N) \n";
                    cin>>option;
                    if(option=='Y' || option=='y'){
                        flag=0;
                        cout<<"Please choose the winner : \n";
                        for(int i=0;i<pl_num;i++) cout<<i<<"."<<name[i]<<"\n";
                        cin>>opt;
                        credit[opt]=credit[opt]+tot_pot;
                        tot_pot=0;
                        flag=0;
                        
                        
                        cout<<"\n Credit for \n";
                        for(int i=0;i<pl_num;i++) cout<<name[i]<<"   is"<<credit[i]<<"\n";
                        
                        
                    }
                }
                
            }
        }
        cout<<"Continue Playing? (Y/N) \n";
        cin>>option;
        if(option=='Y'||option=='y'){
            game_flag=1;
            game=game+1;
        }
        else game_flag=0;
    }
    return 0;
    
}