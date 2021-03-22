import socket
from _thread import *
import pickle
from jogo import jogo

servidor = "192.168.0.103"
porta = 5555
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
try:
    s.bind((servidor, porta))
except socket.error as e:
    str(e)
s.listen()
print("Esperando por conexoes")
conectados = set()  # ira quardar os IPs dos clientes conectados
conta_id = 0


def cliente_thread(conn, jogador, partida):
    global conta_id
    conn.send(pickle.dumps(jogador))
    resposta = ""
    while True:
        try:
            dados = pickle.loads(conn.recv(4096))
            if not dados:
                print("Desconectado")
                break
            else:
                if dados == "zerar":
                    partida.zerar()
                elif dados != "conectar" and dados!="atualizar":
                    partida.joga(jogador, int(dados[0]), int(dados[1]))
                resposta = partida
                conn.sendall(pickle.dumps(resposta))
                print(f"Recebido: {dados}")
                print(f"Enviando: {resposta}")
        except:
            break
    print("Conexao perdida")
    conta_id -= 1
    conn.close()


while True:
    (
        conn,
        address,
    ) = (
        s.accept()
    )  # conn eh um novo objeto que pode enviar e receber mensagens eh o endereco (Fonte: Documentacao socket)
    print("Conectado a:", address)
    conta_id += 1
    jogador = 0
    if conta_id == 1:
        partida = jogo()
        print("Criando novo jogo")
    else:
        partida.pronto = True
        jogador = 1
    start_new_thread(cliente_thread, (conn, jogador, partida))
