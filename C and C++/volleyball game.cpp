#include<bits/stdc++.h>
using namespace std;

class Jogador;

class Time{
protected:
	string nome;
	Jogador* jogador[7];
	//0-levantador 1-libero 2,3-meia 4,5-ponta 6-oposto
public:
	Time(){
	}
	Time(string nome, Jogador* levantador, Jogador* libero, Jogador* meia1, Jogador* meia2, Jogador* ponta1, Jogador* ponta2, Jogador* oposto){
		this->nome=nome;
		jogador[0]=levantador;
		jogador[1]=libero;
		jogador[2]=meia1;
		jogador[3]=meia2;
		jogador[4]=ponta1;
		jogador[5]=ponta2;
		jogador[6]=oposto;
	}
	string getNome(){
		return nome;
	}
	void setNome(string novo_nome){
		nome=novo_nome;
	}
	string getJogador_nome(int i);
	float getJogador_ataque(int i);
	float getJogador_passe(int i);
	float getJogador_defesa(int i);
	float getJogador_estatistica(int i);
	void setJogador(int i, string nome, float ataque, float passe, float defesa, float estatistica);
	void mostragem(int i);
	float pegarHabilidadeTotal();
};

class Jogador{
	friend void Time::setJogador(int i, string nome, float ataque, float passe, float defesa, float estatistica);
	string nome;
	float ataque,passe,defesa,estatistica;
	const float peso_ataque,peso_passe,peso_defesa,peso_estatistica;
public:
	Jogador(string nome="Davi", float ataque=0, float passe=0, float defesa=0, float estatistica=0, float peso_ataque=0, float peso_passe=0, float peso_defesa=0, float peso_estatistica=0):
	    nome(nome), ataque(ataque), passe(passe), defesa(defesa), estatistica(estatistica), peso_ataque(peso_ataque), peso_passe(peso_passe), peso_defesa(peso_defesa), peso_estatistica(peso_estatistica){}

	float Habilidade(){
		return (peso_ataque*ataque+peso_passe*passe+peso_defesa*defesa)/(peso_ataque+peso_passe+peso_defesa)+peso_estatistica*estatistica;
	}
	virtual void mostragem_geral(){
		cout<<nome<<", ataque: "<<ataque<<", passe: "<<passe<<", defesa: "<<defesa;
	}
	string getNome(){
		return nome;
	}
	float getAtaque(){
		return ataque;
	}
	float getPasse(){
		return passe;
	}
	float getDefesa(){
		return defesa;
	}
	float getEstatistica(){
		return estatistica;
	}
};

string Time::getJogador_nome(int i){
	return jogador[i]->Jogador::getNome();
}
float Time::getJogador_ataque(int i){
	return jogador[i]->getAtaque();
}
float Time::getJogador_passe(int i){
	return jogador[i]->getPasse();
}
float Time::getJogador_defesa(int i){
	return jogador[i]->getDefesa();
}
float Time::getJogador_estatistica(int i){
	return jogador[i]->getEstatistica();
}
void Time::setJogador(int i, string nome, float ataque, float passe, float defesa, float estatistica){
	jogador[i]->nome=nome;
	jogador[i]->ataque=ataque;
	jogador[i]->passe=passe;
	jogador[i]->defesa=defesa;
	jogador[i]->estatistica=estatistica;
}
void Time::mostragem(int i){
	jogador[i]->mostragem_geral();
}
float Time::pegarHabilidadeTotal(){ //considerando que todo jogador terá habilidade maior que 0 e time invalido seja aquele que não inseriu todos os jogadores ainda
	if(jogador[0]->Habilidade()>0 && jogador[1]->Habilidade()>0 && jogador[2]->Habilidade()>0 && jogador[3]->Habilidade()>0 && jogador[4]->Habilidade()>0 && jogador[5]->Habilidade()>0 && jogador[6]->Habilidade()>0){
		return jogador[0]->Habilidade()+jogador[1]->Habilidade()+jogador[2]->Habilidade()+jogador[3]->Habilidade()+jogador[4]->Habilidade()+jogador[5]->Habilidade()+jogador[6]->Habilidade();
	}
	return -1;
}

class Levantador:public Jogador{
public:
	Levantador(string nome="Davi", float ataque=0, float passe=0, float defesa=0, float estatistica=0):Jogador(nome,ataque,passe,defesa,estatistica,1,6,3,10){}
	void mostragem_geral(){
		cout<<"Levantador: ";
		Jogador::mostragem_geral();
		cout<<", melhor jogador em campo "<<getEstatistica()<<" vezes!"<<endl;
	}
};

class Libero:public Jogador{
public:
	Libero(string nome="Davi", float ataque=0, float passe=0, float defesa=0, float estatistica=0):Jogador(nome,ataque,passe,defesa,estatistica,0,5,5,10){}
	void mostragem_geral(){
		cout<<"Líbero: ";
		Jogador::mostragem_geral();
		cout<<", melhor qualidade de passe em "<<getEstatistica()<<" jogos!"<<endl;
	}
};

class Meia:public Jogador{
public:
	Meia(string nome="Davi", float ataque=0, float passe=0, float defesa=0, float estatistica=0):Jogador(nome,ataque,passe,defesa,estatistica,4,1,3,-1){}
	void mostragem_geral(){
		cout<<"Meia: ";
		Jogador::mostragem_geral();
		cout<<", "<<getEstatistica()<<" jogos sem bloqueio :/"<<endl;
	}
};

class Ponta:public Jogador{
public:
	Ponta(string nome="Davi", float ataque=0, float passe=0, float defesa=0, float estatistica=0):Jogador(nome,ataque,passe,defesa,estatistica,4,3,3,0){}
	void mostragem_geral(){
		cout<<"Ponta: ";
		Jogador::mostragem_geral();
		cout<<endl;
	}
};

class Oposto:public Jogador{
public:
	Oposto(string nome="Davi", float ataque=0, float passe=0, float defesa=0, float estatistica=0):Jogador(nome,ataque,passe,defesa,estatistica,6,1,3,20){}
	void mostragem_geral(){
		cout<<"Oposto: ";
		Jogador::mostragem_geral();
		cout<<", marcou mais pontos "<<getEstatistica()<<" vezes!"<<endl;
	}
};

bool fez_ponto(float prob){
	if(rand()%10000<prob*10000) return true;
	return false;
}

int setjogo (int saque, float prob1, float prob2, Time t1, Time t2, int max){
    static int p1=0, p2=0;
    if(saque==1){
        if(fez_ponto(prob1)){
            p1++;
            cout<<"Ponto do time " << t1.getNome()<<"!"<<endl;
        }
        else{
            p2++;
            cout<<"Ponto do time " << t2.getNome()<<"!"<<endl;
            saque=2;
        }
    }
    else{
        if(fez_ponto(prob2)){
            p2++;
            cout<<"Ponto do time "<<t2.getNome()<<"!"<<endl;
        }
        else{
            p1++;
            cout<<"Ponto do time "<<t1.getNome()<<"!"<<endl;
            saque=1;
        }
    }
    cout<<t1.getNome()<<" "<<p1<<" x "<<p2<<" "<<t2.getNome()<<endl<<endl;
    if((p1<max && p2<max) || abs(p2-p1)<2)
        return saque;
    else{
        if(p2>p1){
            p1=p2=0;
            return 4;
        }
        else{
            p1=p2=0;
            return 3;
        }
    }
}

inline void jogo(Time t1, Time t2){
	int cont1=0, cont2=0, saque, aux;
	float prob1, prob2;
	prob1=t1.pegarHabilidadeTotal()/(t1.pegarHabilidadeTotal()+t2.pegarHabilidadeTotal()*1.25);
	prob2=t2.pegarHabilidadeTotal()/(t2.pegarHabilidadeTotal()+t1.pegarHabilidadeTotal()*1.25);
	if(rand()%2) saque=1;
	else saque=2;
	//set 1 e set2
	for(int i=1;i<=2;i++){
		cout<<"Inicio do set "<<i<<"!"<<endl;
		for(aux=setjogo(saque, prob1, prob2, t1, t2, 25); aux<3; aux=setjogo(aux, prob1,prob2,t1,t2,25)){}
		if(aux==3){
	    	cont1++;
	    	cout<<"Fim de set! Ganhador: time " <<t1.getNome()<<endl;
	    	cout<<t1.getNome()<<" "<<cont1<<" x "<<cont2<<" "<<t2.getNome()<<endl<<endl<<endl;
	    }
	    if(aux==4){
            cont2++;
	        cout<<"Fim de set! Ganhador: time " <<t2.getNome()<<endl;
	        cout<<t1.getNome()<<" "<<cont1<<" x "<<cont2<<" "<<t2.getNome()<<endl<<endl<<endl;
	    }
    	if(saque==1) saque=2;
		else saque=1;
	}
	//tie break
	if(cont1==cont2){
		cout<<"TIE BREAK!"<<endl;
        for(aux=setjogo(saque, prob1, prob2, t1, t2, 15); aux<3;aux=setjogo(aux,prob1,prob2,t1,t2,15)){}
        if(aux==3) {
	      cont1++;
	      cout<<"Fim do Tie Break! Ganhador: time " <<t1.getNome()<<endl;
        }
	    if(aux==4){
	      cont2++;
	      cout<<"Fim do Tie Break! Ganhador: time " <<t2.getNome()<<endl;
	    }
	}
	cout<<"Fim de jogo! Parabéns ";
	if(cont1>cont2) cout<<t1.getNome();
	else cout<<t2.getNome();
	cout<<"!"<<endl;
}

class Partida{
	Time time1, time2;
public:
	Partida(Time t1, Time t2):time1(t1), time2(t2){}
	bool realizar(){
		if(time1.pegarHabilidadeTotal()==-1 || time2.pegarHabilidadeTotal()==-1) return false;
		jogo(time1,time2);
		return true;
	}
};

int main(){
	srand((unsigned)time(0));
	setlocale(LC_ALL, "portuguese");
	Levantador levantador("Julia",1,6,3,1),levantador_adv("Davi",1,6,3,1);
	Libero libero("Bruninho", 1, 5, 5, 1), libero_adv("Mordomo", 1, 5, 5, 1);
	Meia meia1("Arnon", 4, 1 , 3, 1), meia2("Barbosa", 4, 1, 3, 1),meia1_adv("Ciclope", 4, 1 , 3, 1), meia2_adv("Jota M.", 4, 1, 3, 1);
	Ponta ponta1("Fallen K.", 4, 3, 3, 1), ponta2("Clara M.", 4, 3, 3, 1),ponta1_adv("Lucy", 4, 3, 3, 1), ponta2_adv("Eme P.", 4, 3, 3, 1);
	Oposto oposto("Guima", 6, 1, 3, 1),oposto_adv("Leozinho", 6, 1, 3, 1);
	Time casa("Sadia", &levantador, &libero, &meia1, &meia2, &ponta1, &ponta2, &oposto);
	Time visitante("Netherlands", &levantador_adv, &libero_adv, &meia1_adv, &meia2_adv, &ponta1_adv, &ponta2_adv, &oposto_adv);
	char c='2';
	while(c!='3'){
		c='2';
		while(c!='1'){
			cout<<endl<<endl<<"Time da casa: "<<casa.getNome()<<"!"<<endl;
			for(int i=0;i<7;i++) casa.mostragem(i);
			cout<<endl<<endl<<"Time visitante: "<<visitante.getNome()<<"!"<<endl;
			for(int i=0;i<7;i++) visitante.mostragem(i);
			cout<<endl<<endl<<"(1) Começar jogo"<<endl;
			cout<<"(2) Mexer nos times"<<endl;
			cout<<"(3) Encerrar"<<endl;
			scanf(" %c", &c);
			if(c=='3') return 0;
			if(c=='2'){
				char t, tt, s[50], ind;
				float at, pas, def, est;
				cout<<"(1) "<<casa.getNome()<<endl;
				cout<<"(2) "<<visitante.getNome()<<endl;
				scanf(" %c", &t);
				if(t=='1') cout<<endl<<endl<<"(0) "<<casa.getNome()<<endl;
				else cout<<endl<<endl<<"(0) "<<visitante.getNome()<<endl;
				for(int i=0;i<7;i++){
					cout<<"("<<i+1<<") ";
					if(t=='1') casa.mostragem(i);
					else visitante.mostragem(i);
				}
				scanf(" %c", &tt);
				ind=tt-'0'-1;
				if(tt=='0'){
					if(t=='1'){
						cout<<"Novo nome do time: ";
						scanf(" %s", s);
						casa.setNome(s);
					}
					else{
						cout<<"Novo nome do time: ";
						scanf(" %s", s);
						visitante.setNome(s);
					}
				}
				else{
					if(tt=='1') cout<<"Nome do novo levantador: ";
					else if(tt=='2') cout<<"Nome do novo líbero: ";
					else if(tt=='3' || tt=='4') cout<<"Nome do novo meia: ";
					else if(tt=='5' || tt=='6') cout<<"Nome do novo ponta: ";
					else cout<<"Nome do novo oposto: ";
					scanf(" %s", s);
					cout<<"Ataque: ";
					cin>>at;
					cout<<"Passe: ";
					cin>>pas;
					cout<<"Defesa: ";
					cin>>def;
					if(tt!='5' && tt!='6'){
						if(tt=='1') cout<<"Vezes em que foi o melhor jogador em campo: ";
						else if(tt=='2') cout<<"Vezes em que teve a melhor qualidade de passe: ";
						else if(tt=='3' || tt=='4') cout<<"Jogos sem bloqueio: ";
						else{
							cout<<"Jogos no qual marcou mais pontos: ";
							ind=6;
						}
						cin>>est;
					}
					if(t=='1') casa.setJogador(ind,s,at,pas,def,est);
					else visitante.setJogador(ind,s,at,pas,def,est);
				}
			}
		}
		if(c=='1'){
			Partida partida(casa,visitante);
			if(!partida.realizar()) cout<<"Invalidos"<<endl;
			cout<<"(1) Outro Jogo"<<endl;
			cout<<"(2) Encerrar"<<endl;
			scanf(" %c", &c);
			c++;
		}
	}
	return 0;
}
