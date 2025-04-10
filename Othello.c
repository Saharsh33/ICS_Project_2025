#include<stdio.h>                   
#include<stdlib.h>
#include <limits.h>

int oth[8][8];                          // 1= Black; 2=White;

// int we1[8][8]={{100,1,10,10,10,10,1,100}
//              ,{1,0,2,2,2,2,0,1}
//              ,{10,2,10,5,5,10,2,10}
//              ,{10,2,5,25,25,5,2,10}
//              ,{10,2,5,25,25,5,2,10}
//              ,{10,2,10,5,5,10,2,10}
//              ,{1,0,2,2,2,2,0,1}
//              ,{100,1,10,10,10,10,1,100}
//             };

            int we1[8][8]={{100,-20,10,5,5,10,-20,100}
             ,{-20,-40,-5,-5,-5,-5,-40,-20}
             ,{10,-5,5,1,1,5,-5,10}
             ,{5,-5,1,1,1,1,-5,5}
             ,{5,-5,1,1,1,1,-5,5}
             ,{10,-5,5,1,1,5,-5,10}
             ,{-20,-40,-5,-5,-5,-5,-40,-20}
             ,{100,-20,10,5,5,10,-20,100}
            };

typedef struct move {
    int i;
    int j;
} bestmove,move,validmove;
typedef struct{
    int black;
    int white;
}score;

void print(){        
     // print board
     printf("  ");
    for(int i=0;i<8;i++){
        printf("%c ",'a'+i);
    }
    printf("\n");
    for(int i=0;i<8;i++){
        printf("%d ",i+1);
        for(int j=0;j<8;j++){           // intial all value 0
            if(oth[i][j]==0) printf(". ");
            if(oth[i][j]==1) printf("B ");
            if(oth[i][j]==2) printf("W ");
        }
        printf("\n");
    }

}

void copy(int*c,int*p){
    for(int i=0;i<64;i++){
        
        *p=*c;
        p++;
        c++;
    }
}


int valid_move(int oth1[8][8],int i,int j, int colour){

    if(oth1[i][j]!=0) return 0;
    int oppcol;
    if(colour==1) oppcol=2;
    if(colour==2) oppcol=1;

    if(oth1[i+1][j]==oppcol &&i+1<8 ){                   //horizontal aage   
        for(int k=2+i;k<8;k++){
            if(oth1[k][j]==0)break;                              
            if(oth1[k][j]==colour) return 1;
             
        }
    }
    if(oth1[i-1][j]==oppcol && i-1>=0){ 
        for(int k=-2+i;k>=0;k--){
        if(oth1[k][j]==0)break;         //horizontal  piche
        if(oth1[k][j]==colour)return 1;
        } 
    }
    if(oth1[i][j+1]==oppcol && j+1<8 ){ 
        for(int k=2+j;k<8;k++){
            if(oth1[i][k]==0)break;         // vertical uper
            if(oth1[i][k]==colour)return 1;
        }
    }
    if(oth1[i][j-1]==oppcol && j-1>=0 ){ 
        for(int k=-2+j;k>=0;k--){
            if(oth1[i][k]==0)break;          // vertical niche
            if(oth1[i][k]==colour)return 1;
        }
    }
    if(oth1[i+1][j+1]==oppcol &&i+1<8 &&j+1<8){ 
        for(int k=2;i+k<8 && j+k<8;k++){
            if(oth1[i+k][j+k]==0)break;         // cross age uper
            if(oth1[i+k][j+k]==colour)return 1;
        }
    }
    if(oth1[i-1][j-1]==oppcol && i-1>=0 && j-1>=0){     //cross piche niche
        for(int k=2;i-k>=0 && j-k>=0;k++){
            if(oth1[i-k][j-k]==0)break;
            if(oth1[i-k][j-k]==colour)return 1;
        }
    }
    if(oth1[i+1][j-1]==oppcol &&i+1<8 && j-1>=0){     // cross age niche
        for(int k=2;i+k<8 && j-k>=0;k++){
            if(oth1[i+k][j-k]==0)break;
            if(oth1[i+k][j-k]==colour)return 1;
        }
    }
    if(oth1[i-1][j+1]==oppcol &&j+1<8 && i-1>=0){     // cross piche uper
        for(int k=1;i-k>=0 && j+k<8;k++){
            if(oth1[i-k][j+k]==0)break;
            if(oth1[i-k][j+k]==colour)return 1;
        }
    }

    return 0;
}


int gameover (){
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            if(valid_move(oth,i,j,1)==1 && valid_move(oth,i,j,2)==1){
               return 1;
            }
        }
    }
    return 0;
}

int gameover1 (int oth1[8][8],int com){
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            if(valid_move(oth1,i,j,1)==com){
               return 1;
            }
        }
    }
    return 0;
}


void start(){
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){           // intial all value 0
            oth[i][j]=0;
        }
    }

    oth[4-1][4-1]=2;
    oth[5-1][5-1]=2;
    oth[4-1][5-1]=1;                    // initial game
    oth[5-1][4-1]=1;

    print();

}

void swap_move(int oth1[8][8],int i,int j, int colour,int *ptr){
    int oppcol;
    if(colour==1) oppcol=2;
    if(colour==2) oppcol=1;

    *ptr=colour;
    if(oth1[i+1][j]==oppcol && i+1<8){                   //horizontal aage   
        for(int k=2+i;k<8;k++){
            if(oth1[k][j]==0)break;                              
            if(oth1[k][j]==colour){
                int*ptr1=ptr+8;
                while(*ptr1==oppcol ){
                    *ptr1=colour;
                     ptr1+=8;
                }
                break;
            }
        }
    }
    if(oth1[i-1][j]==oppcol && i-1>=0){ 
        for(int k=-2+i;k>=0;k--){
        if(oth1[k][j]==0)break;         //horizontal  piche
        if(oth1[k][j]==colour){
            int*ptr1=ptr-8;
            while(*ptr1==oppcol){
                *ptr1=colour;
                 ptr1-=8;
                }
            break;
            }
        } 
    }
    if(oth1[i][j+1]==oppcol && j+1<8){ 
        for(int k=2+j;k<8;k++){
            if(oth1[i][k]==0)break;         // vertical uper
            if(oth1[i][k]==colour){
                int*ptr1=ptr+1;
                while(*ptr1==oppcol){
                    *ptr1=colour;
                     ptr1+=1;
                }
                break;
            }
        }
    }
    if(oth1[i][j-1]==oppcol && j-1>=0){ 
        for(int k=-2+j;k>=0;k--){
            if(oth1[i][k]==0)break;          // vertical niche
            if(oth1[i][k]==colour){
                int*ptr1=ptr-1;
                while(*ptr1==oppcol){
                    *ptr1=colour;
                     ptr1-=1;
                }
                break;
            }
        }
    }
    if(oth1[i+1][j+1]==oppcol && i+1<8 && j+1<8){ 
        for(int k=2;i+k<8 && j+k<8;k++){
            if(oth1[i+k][j+k]==0)break;         // cross age uper
            if(oth1[i+k][j+k]==colour){
                int*ptr1=ptr+9;
                while(*ptr1==oppcol){
                    *ptr1=colour;
                     ptr1+=9;
                }
                break;
            }
        }
    }
    if(oth1[i-1][j-1]==oppcol && i-1>=0 && j-1>=0){     //cross piche niche
        for(int k=2;i-k>=0 && j-k>=0;k++){
            if(oth1[i-k][j-k]==0)break;
            if(oth1[i-k][j-k]==colour){
                int*ptr1=ptr-9;
                while(*ptr1==oppcol){
                    *ptr1=colour;
                     ptr1-=9;
                }
                break;
            }
        }
    }
    if(oth1[i+1][j-1]==oppcol && j-1>=0 && i+1<8){     // cross age niche
        for(int k=2;i+k<8 && j-k>=0;k++){
            if(oth1[i+k][j-k]==0)break;
            if(oth1[i+k][j-k]==colour){
                int*ptr1=ptr+7;
                while(*ptr1==oppcol){
                    *ptr1=colour;
                     ptr1+=7;
                }
                break;
            }
        }
    }
    if(oth1[i-1][j+1]==oppcol && i-1>=0 && j+1<8){     // cross piche uper
        for(int k=1;i-k>=0 && j+k<8;k++){
            if(oth1[i-k][j+k]==0)break;
            if(oth1[i-k][j+k]==colour){
                int*ptr1=ptr-7;
                while(*ptr1==oppcol){
                    *ptr1=colour;
                     ptr1-=7;
                }
                break;
            }
        }
    }

    return;

}
// 1==computer
int evalution (int duoth[8][8],int ai,int com){
    
    

    int opp;
    if(com==1)opp=2;
    if(com==2)opp=1;
    int value=0;
    if(gameover1(duoth,com)==0){
        return -100000;
    }
    if(gameover1(duoth,opp)==0){
        return +100000;
    }
    if(ai){
        for(int i=0;i<8;i++){
            for(int j=0;j<8;j++){
                if(duoth[i][j]==com){
                    value=value+1;
                }
                if(duoth[i][j]==opp){
                    value=value-1;
                }
            }
        }
        return value;
    }

    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            if(duoth[i][j]==1){
                value=value+(we1[i][j]);
            }
            if(duoth[i][j]==2){
                value=value-(we1[i][j]);
            }
        }
    }
    if(duoth[0][0]==1){
        for(int i=1;i<8;i++){
            int count =0;
            for(int j=0;j<i+1;j++){
                if(oth[i-j][0+j]==2  && oth[i-j][0+j]==0 ){
                    count++;
                    break;
                }
            }
            if(count!=0)break;
            value=value+(i+1)*100;
        }
    }
    if(duoth[0][0]==2){
        for(int i=1;i<8;i++){
            int count =0;
            for(int j=0;j<i+1;j++){
                if(oth[i-j][0+j]==1 && oth[i-j][0+j]==0){
                    count++;
                    break;
                }
            }
            if(count!=0)break;
            value=value-(i+1)*100;
        }
    }
    if(duoth[7][0]==1){
        for(int i=1;i<8;i++){
            int count =0;
            for(int j=0;j<i+1;j++){
                if(oth[7-i+j][0+j]==2 && oth[7-i+j][0+j]==0){
                    count++;
                    break;
                }
            }
            if(count!=0)break;
            value=value+(i+1)*100;
        }
    }
    if(duoth[7][0]==2){
        for(int i=1;i<8;i++){
            int count =0;
            for(int j=0;j<i+1;j++){
                if(oth[7-i+j][0+j]==1 && oth[7-i+j][0+j]==0){
                    count++;
                    break;
                }
            }
            if(count!=0)break;
            value=value-(i+1)*100;
        }
    }
    if(duoth[0][7]==1){
        for(int i=1;i<8;i++){
            int count =0;
            for(int j=0;j<i+1;j++){
                if(oth[0+j][7-i+j]==2 && oth[0+j][7-i+j]==0){
                    count++;
                    break;
                }
            }
            if(count!=0)break;
            value=value+(i+1)*100;
        }
    }
    if(duoth[0][7]==2){
        for(int i=1;i<8;i++){
            int count =0;
            for(int j=0;j<i+1;j++){
                if(oth[0+j][7-i+j]==1 && oth[0+j][7-i+j]==0){
                    count++;
                    break;
                }
            }
            if(count!=0)break;
            value=value-(i+1)*100;
        }
    }
    if(duoth[7][7]==1){
        for(int i=1;i<8;i++){
            int count =0;
            for(int j=0;j<i+1;j++){
                if(oth[7-j][7-i+j]==2 && oth[7-j][7-i+j]==0){
                    count++;
                    break;
                }
            }
            if(count!=0)break;
            value=value+(i+1)*100;
        }
    }
    if(duoth[7][7]==2){
        for(int i=1;i<8;i++){
            int count =0;
            for(int j=0;j<i+1;j++){
                if(oth[7-j][7-i+j]==1 && oth[7-j][7-i+j]==0){
                    count++;
                    break;
                }
            }
            if(count!=0)break;
            value=value-(i+1)*100;
        }
    }

    return value;
}

int minimax(int depth,int alpha,int beta,int duoth[8][8],int maxmin,int ai,int com){
    if(depth==0){
        return evalution(duoth,ai,com);
    }
    int opp;
    if(com==1)opp=2;
    if(com==2)opp=1;
    if(maxmin){
        int max_value=INT_MIN;
        int count=0;
        for(int i=0;i<8;i++){
            for(int j=0;j<8;j++){

                if(valid_move(duoth,i,j,com)){
                    count++;
                    int duoth1[8][8];
                    copy(&duoth[0][0],&duoth1[0][0]);
                    int* ptr=&duoth1[i][j];

                    swap_move(duoth1,i,j,com,ptr);
                    int eval=0;
                    eval=minimax(depth-1,alpha,beta,duoth1,0,ai,com);
                    if(eval>max_value){
                        max_value=eval;
                    }
                    if(eval>alpha) alpha=eval;
                    if(beta<=alpha) {
                        return max_value;
                    }
                }
            }
        }
            if(count==0){
                return minimax(depth - 1, alpha, beta, duoth, 0,ai,com);
            }
            return max_value;

    }else{
        int min_value=INT_MAX;
        int count=0;
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){

            if(valid_move(duoth,i,j,opp)){
                count++;
                int duoth1[8][8];
                    copy(&duoth[0][0],&duoth1[0][0]);
                    int* ptr=&duoth1[i][j];
                    swap_move(duoth1,i,j,opp,ptr);
                int eval=0;
                eval=minimax(depth-1,alpha,beta,duoth1,1,ai,com);
                if(eval<min_value){
                    min_value=eval;
                }
                if(eval<beta) beta=eval;
                if(beta<=alpha) return min_value;
            }
        }
    }
    if(count==0){
        return minimax(depth - 1, alpha, beta, duoth, 1,ai,com);
    }
        return min_value;
    }
}

int best_move(bestmove *b1,int depth,int ai,int com){

    int count =0;
    int max_value=INT_MIN;
    int alpha=INT_MIN;
    int beta=INT_MAX;
        for(int i=0;i<8;i++){
            for(int j=0;j<8;j++){
                if(valid_move(oth,i,j,com)){
                    int duoth1[8][8];
                    copy(&oth[0][0],&duoth1[0][0]);
                    int* ptr=&duoth1[i][j];
                    swap_move(duoth1,i,j,1,ptr);
                    count++;
                    int eval=0;
                    eval=minimax(depth-1,alpha,beta,duoth1,0,ai,com);
                    if(eval>max_value){
                        max_value=eval;
                        b1->i=i;
                        b1->j=j;
                    }
                    if(eval>alpha) alpha=eval;
                    if(beta<=alpha) {
                       return 1;
                    }
                }
            }
        }
        if(count==0){
            return 0;
        }
        return 1;
}


void Score(score *c1){
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            if(oth[i][j]==1){
                (c1->black)++;
            }
            if(oth[i][j]==2){
                (c1->white)++;
            }
        }
    }
}


// baki che
int main (){
    start();
    char type;
    printf("Want to play with Human or Computer\n If Human type H else type C\n Enter here:");
    type=getchar();
    if(type=='C'){
        int ai;
        printf("for Bot 1 enter 1 and for bot 2 enter 0 (bot 1 slower but accurate and bot 2 faster)\n");
        scanf("%d",&ai);
        int depth;
        printf("Enter the level of Hardness:");
        scanf("%d",&depth);                      //baki che;
        while (gameover){
            // int i,j;
            // char c;
            // scanf("%d,%c",&i,&c);// swaping baki che
            // j=c-'A';
            // i--;
            // if(valid_move(oth,i,j,2)){
            //     swap_move(oth,i,j,2,&oth[i][j]);
            //     print();

            move c1,c2;
            if(best_move(&c1,depth,1,1)){
                printf("%d,%c\n",(c1.i)+1,(c1.j)+'A');
                swap_move(oth,(c1.i),(c1.j),1,&oth[c1.i][c1.j]);
                print();
            }
            if(best_move(&c2,depth,0,2)){
                printf("%d,%c\n",(c2.i)+1,(c2.j)+'A');
                swap_move(oth,(c2.i),(c2.j),2,&oth[c2.i][c2.j]);
                print();
            }
            
            
            }
            // score C;
            // C.white=0;
            // C.black=0;
            // Score(&C);
            // printf("white:%d Black:%d",C.white,C.black);

           
        }
    else{

    }

    return 0;
}
