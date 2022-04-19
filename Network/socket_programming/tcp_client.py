#################### TCP client ####################

from socket import *

clientSock = socket(AF_INET, SOCK_STREAM) # 클라이언트 소켓을 생성한다.
clientSock.connect(('127.0.0.1', 8080)) # 소켓을 해당 포트에 연결시킨다.
print('연결 확인 됐습니다.')


clientSock.send('Ae Je-Yeon'.encode('utf-8')) # 클라이언트가 서버로 영문 메세지 송신
print('메시지를 보냈습니다.')

data = clientSock.recv(1024) # 클라이언트로부터 데이터를 수신받는다.
print('서버로부터 받은 데이터 : ', data.decode('utf-8')) # 수신받은 학번 데이터 출력

print('연결을 끊고 종료합니다.')
clientSock.close() # 연결을 끊고 종료한다.
