#include <iostream>
#include <string>
#include <vector>
#include <deque>

using namespace std;

class BigDecimal{
	vector<int>integer;
	vector<int>decimal;
	bool negative;
	public:
	BigDecimal(){
		negative=false;
		//integer.push_back(0);
	}
	
	BigDecimal(string s){
		negative=false;
		int splitpoint=-1;
		int displace=0;
		for(int i=0;i<s.size();i++){
			if(s[i]=='.'){
				splitpoint=i;
			}else
			if(s[i]=='-'){
				negative=true;
			}else
			if(splitpoint<0){
				integer.push_back(s[i]-'0');
			}else{
				decimal.push_back(s[i]-'0');
			}
			
		}
	}
	
	void print(){
		if(negative)
			cout<<"-";
		for(int i=0;i<integer.size();i++){
			cout<<integer[i];
		}
		if(decimal.size()>0){
		cout<<".";
		}
		for(int i=0;i<decimal.size();i++){
			cout<<decimal[i];
		}
	}
	
	BigDecimal add(BigDecimal b){
		BigDecimal *longestdec=this;
		BigDecimal *longestint=this;
		BigDecimal *shortdec=&b;
		BigDecimal *shortint=&b;
		
		if(b.decimal.size()>this->decimal.size()){
			longestdec=&b;
			shortdec=this;
		}
		
		if(b.integer.size()>this->integer.size()){
			longestint=&b;
			shortint=this;
		}
		
		//Add Decimal
		deque<int>newdec;
		
		int carry=0;
		
		for(int i=longestdec->decimal.size()-1;i>=0;i--){
			if(i>=shortdec->decimal.size()){
				newdec.push_front(longestdec->decimal[i]);
			}else{
				int sum=longestdec->decimal[i]+shortdec->decimal[i]+carry;
				
				int halfsum=sum%10;
				
				newdec.push_front(halfsum);
				
				carry=sum/10;
			}
		}
		
		deque<int>newint;
		
		for(int i=longestint->integer.size()-1;i>=0;i--){
			//cout<<longestint->integer.size()-shortint->integer.size()-1<<"\n";
			if(i<=longestint->integer.size()-shortint->integer.size()-1 && longestint->integer.size()-shortint->integer.size()!=0){
				int sum=longestint->integer[i]+carry;
				
				int halfsum=sum%10;
				
				newint.push_front(halfsum);
				
				carry=sum/10;
			}else{
				int sum=longestint->integer[i]+shortint->integer[i-longestint->integer.size()+shortint->integer.size()]+carry;
				
				int halfsum=sum%10;
				
				newint.push_front(halfsum);
				
				carry=sum/10;
			}
		}
		
		if(carry!=0){
			newint.push_front(carry);
		}
		
		BigDecimal bd=BigDecimal();
		
		for(int i=0;i<newdec.size();i++){
			bd.decimal.push_back(newdec.at(i));
		}
		
		for(int i=0;i<newint.size();i++){
			bd.integer.push_back(newint.at(i));
		}
		
		return bd;
	}
}bd_t;

int main(){

  string in;
  cout<<"First number\n";
  cin>>in;
  BigDecimal test=BigDecimal(in);
  cout<<"Second number\n";
  cin>>in;
  BigDecimal test2=BigDecimal(in);
  cout<<"Sequence\n";
  BigDecimal test3;
  for(int i=1;i<1000000;i++){
    test3=(test.add(test2));
    cout<<(i+1)<<":";
    test3.print();
    cout<<"\n\n";
    test=test2;
    test2=test3;
  }
  cout<<"Last"<<":";
  test3.print();
  cout<<"\n";
}
