import socket
import pickle
class Rede:
    def __init__(self):
        self.cliente = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.servidor = "192.168.0.103"  # Tem q botar o endereco IP da sua maquina
        self.porta = 5555
        self.address = (self.servidor, self.porta)
        self.objeto_socket = self.connect()

    def get_objeto_socket(self):
        return self.objeto_socket

    def connect(self):
        try:
            self.cliente.connect(self.address)
            return pickle.loads(self.cliente.recv(4096))
        except:
            pass

    def send(self, data):
        try:
            self.cliente.send(pickle.dumps(data))  # envia string
            return pickle.loads(self.cliente.recv(4096))  # recebe objeto
        except socket.error as e:
            print(e)