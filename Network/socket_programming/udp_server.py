#################### UDP server ####################

import socket

serverSock = socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM) # 서버 소켓을 생성한다
serverSock.bind(('127.0.0.1', 8080)) # 소켓을 bind 한다.

while (True) :
	data, addr = serverSock.recvfrom(1024) # 데이터를 1024 byte 수신받는다
	print('클라이언트로부터 받은 데이터 : ', data.decode('utf-8')) # 수신 받은 데이터 출력

	serverSock.sendto(str.encode('20182630'), addr) # 클라이언트로 데이터를 송신한다
	print('메시지를 보냈습니다.')

	if data != "" :
		break

print('연결을 끊고 종료합니다.')
serverSock.close() # 연결을 끊고 종료한다.

