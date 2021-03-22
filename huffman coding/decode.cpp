#include <bits/stdc++.h>
using namespace std;

int at;
vector<string> sh;
string hs,hhs;
map<string,string> decode;
FILE *fp,*hp,*tp;
char c[50],h;

int bin_to_dec(string s){
	int x=0;
	for(int i=0;i<8;i++){
		x<<=1;
		if(s[i]=='1') x++;
	}
	if(s[0]=='1') return x-256;
	return x;
}

void make_decod(string s){
	if(sh[at]=="0"){
		at++;
		make_decod(s+"0");
		at++;
		make_decod(s+"1");
	}
	else decode[s]=sh[at];
}

int main(){
	setlocale(LC_ALL, "portuguese");    
    hp=fopen("arvhuf.txt","rt");
    fp=fopen("saída.txt","w");
    tp=fopen("texto.hfm","rt");
    for(fscanf(hp," %s", c);!feof(hp);fscanf(hp," %s", c)) sh.push_back(c);
	fclose(hp);
	make_decod("");
	for(fscanf(tp," %c", &h);!feof(tp);fscanf(tp," %c", &h)){
		hs+=h;
		if(decode.find(hs)!=decode.end()){
			if(decode[hs].size()==8) fprintf(fp,"%c", char(bin_to_dec(decode[hs])));
			if(decode[hs].size()==16){
				hhs.clear();
				for(int i=0;i<8;i++) hhs+=decode[hs][i];
				fprintf(fp,"%c", char(bin_to_dec(hhs)));
				hhs.clear();
				for(int i=8;i<16;i++) hhs+=decode[hs][i];
				fprintf(fp,"%c", char(bin_to_dec(hhs)));
			}
			hs.clear();
		}
	}
	fclose(fp);
	fclose(tp);
    return 0;
}
