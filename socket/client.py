import time
from rede import Rede

def main():
    run = True
    rede = Rede()
    jogador = int(rede.get_objeto_socket())
    print("Voce e o jogador:", jogador+1)
    try:
        jogo = rede.send("conectar")
    except:
        run = False
        print("Nao foi possivel criar o jogo")
    while run:
        if jogo.ambos_jogaram():
            if (jogo.determina_vencedor() == 1 and jogador == 1) or (
                jogo.determina_vencedor() == 0 and jogador == 0
            ):
                print("Parabens,voce venceu!")
                print(f"Voce jogou {jogo.jogada[jogador][1]} e seu adversario {jogo.jogada[not jogador][1]}\n")
            else:
                print("Voce perdeu!")
                print(f"Voce jogou {jogo.jogada[jogador][1]} e seu adversario {jogo.jogada[not jogador][1]}\n")
            time.sleep(1)
            try:
                jogo = rede.send("zerar")
            except:
                run = False
                print("Nao foi possivel achar o jogo apos ambos jogarem")
                break
        if (jogo.p1jogou==0 and jogador==0) or (jogo.p2jogou==0 and jogador==1):
            print("Escolha par ou impar")
            paridade = str(input())
            paridade=paridade.upper()
            paridade=paridade.replace(" ","")
            if paridade=="PAR":
                paridade=0
            if paridade=="IMPAR":
                paridade=1
            print("Escolha o valor do seu numero")
            valor = int(input())
            dado=[paridade,valor]
            if jogador == 0:
                if not jogo.p1jogou:
                    jogo = rede.send(dado)
            else:
                if not jogo.p2jogou:
                    jogo = rede.send(dado)
        jogo=rede.send("atualizar")

main()