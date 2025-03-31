void copy(int*c,int*p){
    for(int i=0;i<64;i++){
        
        *p=*c;
        p++;
        c++;
    }
}
