#################### TCP server ####################

from socket import *

serverSock = socket(AF_INET, SOCK_STREAM) # 서버 소켓을 생성한다
serverSock.bind(('', 8080)) # 소켓을 bind 한다.
serverSock.listen(1) # 소켓은 계속 listen 한다.

connectionSock, addr = serverSock.accept() # 연결요청을 accept 한다.
print(str(addr),'에서 접속이 확인되었습니다.')

data = connectionSock.recv(1024) # 데이터를 수신받는다
print('클라이언트로부터 받은 데이터 : ', data.decode('utf-8')) # 수신 받은 데이터 출력

connectionSock.send('20182630.'.encode('utf-8')) # 클라이언트로 데이터를 송신한다
print('메시지를 보냈습니다.')


print('연결을 끊고 종료합니다.')
serverSock.close() # 연결을 끊고 종료한다.

