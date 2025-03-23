#include<stdio.h>                   
#include<stdlib.h>

int oth[8][8];                          // 1= Black; 2=White;

void print(int oth[8][8]){        
     // print board
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){           // intial all value 0
            if(oth[i][j]==0) printf(". ");
            if(oth[i][j]==1) printf("B ");
            if(oth[i][j]==2) printf("W ");
        }
        printf("\n");
    }

}

void start(int oth[8][8]){
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){           // intial all value 0
            oth[i][j]=0;
        }
    }

    oth[4-1][4-1]=2;
    oth[5-1][5-1]=2;
    oth[4-1][5-1]=1;                    // initial game
    oth[5-1][4-1]=1;

    print(oth);

}

int validmove(int oth[8][8], int i, int j, int colour){
    
    if(oth[i][j]!=0) return 0;
    int count=0;
    int oppcol;
    if(colour==1) oppcol=2;
    if(colour==2) oppcol=1;


    for(int k=1+i;k<8;k++){
        int count1=0;
        if(oth[k][j]==0)break;
        if(oth[k][j]==colour && count1==0)break;  //horizontal aage
        if(oth[k][j]==oppcol) count1++;
        if(oth[k][j]==colour && count1!=0){
            count++;
            break;
        }
    }
    for(int k=-1+i;k>=0;k--){
        int count1=0;
        if(oth[k][j]==0)break;
        if(oth[k][j]==colour && count1==0)break;  //horizontal  piche
        if(oth[k][j]==oppcol) count1++;
        if(oth[k][j]==colour && count1!=0){
            count++;
            break;
        }
    }
    for(int k=1+j;k<8;k++){
        int count1=0;
        if(oth[i][k]==0)break;
        if(oth[i][k]==colour && count1==0)break;  // vertical uper
        if(oth[i][k]==oppcol) count1++;
        if(oth[i][k]==colour && count1!=0){
            count++;
            break;
        }
    }
    for(int k=-1+j;k>=0;k--){
        int count1=0;
        if(oth[i][k]==0)break;
        if(oth[i][k]==colour && count1==0)break;    // vertical niche
        if(oth[i][k]==oppcol) count1++;
        if(oth[i][k]==colour && count1!=0){
            count++;
            break;
        }
    }
    for(int k=1;i+k<8 && j+k<8;k++){
        int count1=0;
        if(oth[i+k][j+k]==0)break;
        // if(oth[i+k][j+k]==colour && count1==0)break;    // cross age uper
        if(oth[i+k][j+k]==oppcol) count1++;
        if(oth[i+k][j+k]==colour && count1!=0){
            count++;
            break;
        }
    }
    for(int k=1;i-k>=0 && j-k>=0;k++){
        int count1=0;
        if(oth[i-k][j-k]==0)break;
        if(oth[i-k][j-k]==colour && count1==0)break;    //cross piche niche
        if(oth[i-k][j-k]==oppcol) count1++;
        if(oth[i-k][j-k]==colour && count1!=0){
            count++;
            break;
        }
    }
    for(int k=1;i+k<8 && j-k>=0;k++){
        int count1=0;
        if(oth[i+k][j-k]==0)break;
        if(oth[i+k][j-k]==colour && count1==0)break;    // cross age niche
        if(oth[i+k][j-k]==oppcol) count1++;
        if(oth[i+k][j-k]==colour && count1!=0){
            count++;
            break;
        }
    }
    for(int k=1;i-k>=0 && j+k<8;k++){
        int count1=0;
        if(oth[i-k][j+k]==0)break;
        if(oth[i-k][j+k]==colour && count1==0)break;  // cross piche uper
        if(oth[i-k][j+k]==oppcol) count1++;
        if(oth[i-k][j+k]==colour && count1!=0){
            count++;
            break;
        }
    }

    if(count!=0){ return 1;}
    else{ return 0;}
    

}



int main (){
    start(oth);
    
    

    return 0;
}
