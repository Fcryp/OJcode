#include<iostream>
#include<algorithm>
using namespace std;
struct Fraction{
    long long integer;
    long long numerator,denominator;
    bool reduction(){
        long long gcd;
        if(numerator!=0 && denominator!=0){
            gcd=__gcd(numerator,denominator);
            numerator/=gcd;
            denominator/=gcd;
            if(denominator==1){
                integer+=numerator;
                numerator=0;
                denominator=0;
            }
        }
        if(numerator>denominator){
            integer+=numerator/denominator;
            numerator=numerator%denominator;
        }
        return true;
    }
    void construct(const long long x,const long long y){
        this->integer=0;
        this->numerator=x;
        this->denominator=y;
        reduction();
    }
    bool operator==(const Fraction b) const{
        return (this->integer==b.integer)&&(this->numerator==b.numerator)&&(this->denominator==b.denominator);
    }
    Fraction * operator=(const int b){
        this->integer=b;
        this->numerator=0;
        this->denominator=0;
        return this; 
    }
    Fraction * operator=(const Fraction b){
        this->integer=b.integer;
        this->numerator=b.numerator;
        this->denominator=b.denominator;
        return this; 
    }
    Fraction operator+(const int b) const{
        Fraction res;
        res.integer=(this->integer+b);
        res.numerator=this->numerator;
        res.denominator=this->denominator;
        return res;
    }
    Fraction operator+(const Fraction b){
        Fraction res;
        res.integer=this->integer+b.integer;
        if(this->numerator==0&&this->denominator==0){
            res.numerator=b.numerator;
            res.denominator=b.denominator;
        }
        else if(b.numerator!=0&&b.denominator!=0){
            res.denominator=this->denominator*b.denominator;
            res.numerator=this->denominator*b.numerator+this->numerator*b.denominator;
        }
        res.reduction();
        return res;
    }
    bool print() const{
        int length=0,numeratorlength=0,denominatorlength=0,maxlength;
        long long temp=this->numerator,intpart=this->integer;
        while(temp!=0){
            numeratorlength++;
            temp/=10;
        }
        temp=this->denominator;
        while(temp!=0){
            denominatorlength++;
            temp/=10;
        }
        if(numeratorlength>denominatorlength)maxlength=numeratorlength;
        else maxlength=denominatorlength;
        if(this->numerator==0 && this->denominator==0){
            cout<<this->integer<<endl;
        }
        else{
            while(intpart!=0){
                length++;
                intpart/=10;
            }
            for(int i=0;i<length+1;i++){
                cout<<" ";
            }
            cout<<this->numerator<<endl;
            cout<<this->integer<<" ";
            for(int i=0;i<maxlength;i++)cout<<"-";
            cout<<endl;
            for(int i=0;i<length+1;i++){
                    cout<<" ";
            }
            cout<<this->denominator<<endl;
        }
        return true;
    }
};
int main(int argc, char const *argv[])
{
    int n,i;
    Fraction fra,add;
    /*INPUT*/
    while(scanf("%d",&n)!=EOF){
        fra=1;
        for(i=1;i<n;i++){
            add.construct(n,n-i);
            fra=fra+add;
        }
        fra.print();
    }
    return 0;
}
