#include <bits/stdc++.h>
using namespace std;

struct node{
	int freq;
	int pos;
	int f1;
	int f2;
    bool operator<(node other) const{
        return freq > other.freq;
    }
};

node h,h2,h3;
map<string,int> qtd;
map<string,string> cod;
vector<string> ch_bin;
vector<node> t;
priority_queue<node> pq;
FILE *fp,*hp,*tp;
char c;

string dec_to_bin(int x){
	string bin="00000000";
	x=(x+256)%256;
	for(int i=0;i<8;i++){
		if(x&1) bin[7-i]='1';
		x>>=1;
	}
	return bin;
}

void make_cod(string s, int at){
	if(at>=ch_bin.size()){
		make_cod(s+"0",t[at].f1);
		make_cod(s+"1",t[at].f2);
	}
	else{
		cod[ch_bin[at]]=s;
	}
}

void pre(int at){
	if(at>=ch_bin.size()){
		fprintf(hp,"0 ");
		pre(t[at].f1);
		pre(t[at].f2);
	}
	else{
		for(int i=0;i<ch_bin[at].size();i++) fprintf(hp,"%c", ch_bin[at][i]);
		fprintf(hp," ");
	}
}

void sim(int at){
	if(at>=ch_bin.size()){
		sim(t[at].f1);
		fprintf(hp,"0 ");
		sim(t[at].f2);
	}
	else{
		for(int i=0;i<ch_bin[at].size();i++) fprintf(hp,"%c", ch_bin[at][i]);
		fprintf(hp," ");
	}
}

int main(){
	setlocale(LC_ALL, "portuguese");    
    hp=fopen("arvhuf.txt","w");
    fp=fopen("input.txt","rt");
    tp=fopen("texto.hfm","w");
    for(fscanf(fp,"%c", &c);!feof(fp);fscanf(fp,"%c", &c)){
    	if(int(c)<0){
    		char ch;
    		fscanf(fp,"%c", &ch);
    		if(qtd[dec_to_bin(int(c))+dec_to_bin(int(ch))]==0) ch_bin.push_back(dec_to_bin(int(c))+dec_to_bin(int(ch)));
    		qtd[dec_to_bin(int(c))+dec_to_bin(int(ch))]++;
		}
		else{
			if(qtd[dec_to_bin(int(c))]==0) ch_bin.push_back(dec_to_bin(int(c)));
			qtd[dec_to_bin(int(c))]++;	
		}
	}
	fclose(fp);
	h.f1=-1;
	h.f2=-1;
	for(int i=0;i<ch_bin.size();i++){
		h.pos=i;
		h.freq=qtd[ch_bin[i]];
		t.push_back(h);
		pq.push(h);
	}
	while(pq.size()>1){
		h=pq.top();
		pq.pop();
		h2=pq.top();
		pq.pop();
		h3.f1=h.pos;
		h3.f2=h2.pos;
		h3.freq=h.freq+h2.freq;
		h3.pos=t.size();
		t.push_back(h3);
		pq.push(h3);
	}
	make_cod("",t.size()-1);
	pre(t.size()-1);
	fprintf(hp,"\n");
	sim(t.size()-1);
	fp=fopen("input.txt","rt");
	for(fscanf(fp,"%c", &c);!feof(fp);fscanf(fp,"%c", &c)){
    	if(int(c)<0){
    		char ch;
    		fscanf(fp,"%c", &ch);
    		for(int i=0;i<cod[dec_to_bin(int(c))+dec_to_bin(int(ch))].size();i++) fprintf(tp,"%c", cod[dec_to_bin(int(c))+dec_to_bin(int(ch))][i]);
		}
		else{	
			for(int i=0;i<cod[dec_to_bin(int(c))].size();i++) fprintf(tp,"%c", cod[dec_to_bin(int(c))][i]);
		}
	}
	fclose(hp);
    fclose(fp);
    fclose(tp);
    return 0;
}
