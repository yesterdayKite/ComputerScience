#################### TCP client ####################

import socket

clientSock = socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM) # 서버 소켓을 생성한다

clientSock.sendto(str.encode('Ae Je-Yeon'), ("127.0.0.1", 8080)) # 클라이언트가 서버로 영문 메세지 송신
print('메시지를 보냈습니다.')

data, addr = clientSock.recvfrom(1024) # 클라이언트로부터 데이터를 1024byte만큼 수신받는다.
print('서버로부터 받은 데이터 : ', data.decode('utf-8')) # 수신받은 학번 데이터 출력

print('연결을 끊고 종료합니다.')
clientSock.close() # 연결을 끊고 종료한다.
