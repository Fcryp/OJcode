int pow(int x,int n){
    int base=x,res=1;       //初始基是x^0
    while(n!=0){
        if(n&1!=0){
            res*=base;
        }
        base*=base;             //指数每次循环都将基数递增，分别是x^(2^0),x^(2^1),x^(2^2)...以此类推
        n>>1;            
    }
}