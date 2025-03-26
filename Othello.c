#include<stdio.h>                   
#include<stdlib.h>

int oth[8][8];                          // 1= Black; 2=White;

int we[8][8]={{100,-25,10,5,5,10,-25,100}
             ,{-25,-40,1,1,1,1,-40,-25}
             ,{10,1,5,2,2,5,1,10}
             ,{5,1,2,1,1,2,1,5}
             ,{5,1,2,1,1,2,1,5}
             ,{10,1,5,2,2,5,1,10}
             ,{-25,-40,1,1,1,1,-40,-25}
             ,{100,-25,10,5,5,10,-25,100}
            };

typedef struct move {
    int i;
    int j;
} bestmove,move,validmove;

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

int valid_move(int oth[8][8],int i,int j, int colour){

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
// 1==computer
int evalution (int duoth[8][8]){
    
    int value=0;

    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            if(duoth[i][j]==1){
                value=value+(we[i][j]);
            }
            if(duoth[i][j]==2){
                value=value-(we[i][j]);
            }
        }
    }

    return value;
}

int computer(){
    
}

//baki che
int best_move(bestmove *b1, int oth[8][8],int depth){

int duoth[8][8];

for(int i=0;i<8;i++){
    for(int j=0;j<8;j++){
        duoth[i][j]=oth[i][j];
    }
}


int max_value=0;
int alpha=-100000;
int beta=100000;
        for(int i=0;i<8;i++){
            for(int j=0;j<8;j++){
                if(valid_move(duoth,i,j,1)){
                    duoth[i][j]=1;
                    int eval=0;
                    eval=minmax(depth-1,alpha,beta,duoth[8][8],0);
                    duoth[i][j]=0;
                    if(eval>max_value){
                        max_value=eval;
                    }
                    if(eval>alpha) alpha=eval;
                    if(beta<=alpha) break;
                    if(eval>max_value){
                        max_value=eval;
                        b1->i=i;
                        b1->j=j;
                    }
                }
            }
        }
        if(max_value==0){
            return 0;
        }
        return 1;
}

// baki che
int maxvalue(int depth,int alpha,int beta,int duoth[8][8]){
        if(depth==0){
            return evalution(duoth[8][8]);
        }
    int max_value=0;
        for(int i=0;i<8;i++){
            for(int j=0;j<8;j++){
                if(valid_move(duoth,i,j,1)){
                    duoth[i][j]=1;
                    int eval=0;
                    eval=minvalue(depth-1,alpha,beta,duoth[8][8]);
                    duoth[i][j]=0;
                    if(eval>max_value){
                        max_value=eval;
                    }
                }
            }
        }

    return max_value;
}

//baki che
int minvalue(int depth,int alpha,int beta,int duoth[8][8]){
    if(depth==0){
        return evalution(duoth[8][8]);
    }
int min_value=0;
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            if(valid_move(duoth,i,j,1)){
                duoth[i][j]=1;
                int eval=0;
                eval=maxvalue(depth-1,alpha,beta,duoth[8][8]);
                duoth[i][j]=0;
                if(eval<min_value){
                    min_value=eval;
                }
            }
        }
    }

return min_value;
}

//main baki che
int minimax(int depth,int alpha,int beta,int duoth[8][8],int maxmin){
    if(depth==0){
        return evalution(duoth[8][8]);
    }
    if(maxmin){
        int max_value=0;
        for(int i=0;i<8;i++){
            for(int j=0;j<8;j++){
                if(valid_move(duoth,i,j,1)){
                    duoth[i][j]=1;
                    int eval=0;
                    eval=minimax(depth-1,alpha,beta,duoth[8][8],0);
                    duoth[i][j]=0;
                    if(eval>max_value){
                        max_value=eval;
                    }
                    if(eval>alpha) alpha=eval;
                    if(beta<=alpha) break;
                }
            }
        }
            if(max_value==0){
                return evalution(duoth[8][8]);
            }
            return max_value;

    }else{
        int min_value=0;
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            if(valid_move(duoth,i,j,1)){
                duoth[i][j]=1;
                int eval=0;
                eval=minimax(depth-1,alpha,beta,duoth[8][8],1);
                duoth[i][j]=0;
                if(eval<min_value){
                    min_value=eval;
                }
                if(eval<beta) beta=eval;
                    if(beta<=alpha) break;
            }
        }
    }
    if(min_value==0){
        return evalution(duoth[8][8]);
    }
        return min_value;
    }
}

// baki che
int main (){
    start(oth);
    
    

    return 0;
}
