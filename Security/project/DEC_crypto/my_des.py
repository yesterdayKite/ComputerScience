
#####################################################
################## utils ############################
#####################################################


######## XOR calc

# return a XOR calc result for list
def XOR(a_list, b_list, calc_len) :

  out = []
  for i in range(calc_len) :
    if (a_list[i] != b_list[i]) :
      out.append('1')
    else :
      out.append('0')
  return out

# return a XOR calc result for character
def XORc(a_char, b_char) :
  if (a_char == b_char) :
    return '0'
  else :
    return '1'


######## s box rule

# exchange by sBox rule
def sBox(s_list) :

  for i in range(len(s_list)) :
    s_list[i] = str(s_list[i])
  s = ''.join(s_list)

  if (s == "0000") : return "1001"
  elif (s == "0001") : return "0100"
  elif (s == "0010") : return "1010"
  elif (s == "0011") : return "1011"
  elif (s == "0100") : return "1101"
  elif (s == "0101") : return "0001"
  elif (s == "0110") : return "1000"
  elif (s == "0111") : return "0101"
  elif (s == "1000") : return "0110"
  elif (s == "1001") : return "0010"
  elif (s == "1010") : return "0000"
  elif (s == "1011") : return "0011"
  elif (s == "1100") : return "1100"
  elif (s == "1101") : return "1110"
  elif (s == "1110") : return "1111"
  elif (s == "1111") : return "0111"
  else :
    print("Sbox error")
    return "0000"


# exchange by sBox invert rule
def sBoxinv(s_list) :

  for i in range(len(s_list)) :
    s_list[i] = str(s_list[i])
  s = ''.join(s_list)

  if (s == "1001") : return "0000"
  elif (s == "0100") : return "0001"
  elif (s == "1010") :return "0010"
  elif (s == "1011") :return "0011"
  elif (s == "1101") :return "0100"
  elif (s == "0001") :return "0101"
  elif (s == "1000") :return "0110"
  elif (s == "0101") :return "0111"
  elif (s == "0110") :return "1000"
  elif (s == "0010") :return "1001"
  elif (s == "0000") :return "1010"
  elif (s == "0011") :return "1011"
  elif (s == "1100") :return "1100"
  elif (s == "1110") :return "1101"
  elif (s == "1111") :return "1110"
  elif (s == "0111") :return "1111"
  else  :
    print("Sbox error")
    return "0000"


######## rearrange rule

# mix columns by S-AES rule
def rearrange_column( top,  bot) :
  out = ['0','0','0','0','0','0','0','0']
  out[0] = XORc(top[0], bot[2])
  out[3] = XORc(top[3], bot[1])
  out[4] = XORc(top[2], bot[0])
  out[7] = XORc(top[1], bot[3])
  out[1] = XORc(out[7], bot[0])
  out[2] = XORc(out[4], bot[1])
  out[5] = XORc(top[0], out[3])
  out[6] = XORc(top[1], out[0])
  return out

# invert calc for mix columns by S-AES rule
def rearrange_column_inv( top,  bot) :
  out = ['0','0','0','0','0','0','0','0']
  out[0] = XORc(top[3], bot[1]) # b3b5
  out[1] = XORc(top[0], bot[2]) # b0b6
  out[4] = XORc(top[1], bot[3]) # b1b7
  out[5] = XORc(top[2], bot[0]) # b2b4
  out[2] = XORc(out[4], bot[0]) # b1b4b7
  out[3] = XORc(out[5], top[3]) # b2b3b4
  out[6] = XORc(out[0], top[0]) # b0b3b5
  out[7] = XORc(out[1], bot[3]) # b0b6b7
  return out


####### key expand util

# return a expanded key from given key
def expandKey(key_str) :

  key = list(key_str)
  out = list(key_str)

  tempA = key[8:12]
  tempB = key[12:16]

  W1 = tempA + tempB
  tempA = list(sBox(tempA))
  tempB = list(sBox(tempB))
  tempB = XOR(tempB, list("1000"), 4)
  tempC = tempB + tempA

  W2 = XOR(key, tempC, 8)
  out = out + W2
  W3 = XOR(W1, W2, 8)
  out = out + W3

  tempA = W3[0:4]
  tempB = W3[4:8]
  tempA = list(sBox(tempA))
  tempB = list(sBox(tempB))

  tempB = XOR(tempB, list("0011"), 4)
  tempC = tempB + tempA

  W4 = XOR(W2, tempC, 8)
  out = out + W4
  tempD = XOR(W4, W3, 8)
  out = out + tempD

  return out



#####################################################
############ enc & dec main code ####################
#####################################################


def S_AES_ENCRYT( plain_text,  k) :

  key = expandKey(k)

  # parse expanded key string
  K0 = key[0:16]
  K1 = key[16:32]
  K2 = key[32:48]

  # XOR calc for each part
  cipher_text = XOR(list(plain_text), K0, 16)
  tempA = list(sBox(cipher_text[0:4]))
  tempB = list(sBox(cipher_text[4:8]))
  tempC = list(sBox(cipher_text[8:12]))
  tempD = list(sBox(cipher_text[12:16]))

  # mix columns
  cipher_text = rearrange_column(tempA, tempD) + rearrange_column(tempC, tempB)
  cipher_text = XOR(cipher_text, K1, 16)

  tempA = list(sBox(cipher_text[0:4]))
  tempB = list(sBox(cipher_text[4:8]))
  tempC = list(sBox(cipher_text[8:12]))
  tempD = list(sBox(cipher_text[12:16]))

  # assemble each part
  cipher_text = tempA + tempD + tempC + tempB
  cipher_text = XOR(cipher_text, K2, 16)

  return ''.join(cipher_text)



def S_AES_DECRYT(cipher_text,  k) :

    key = expandKey(k);

    # parse expanded key string
    K0 = key[0:16]
    K1 = key[16:32]
    K2 = key[32:48]

    #generate the round sub-keys
    # add K2
    plain_text = XOR(list(cipher_text), K2, 16)

    tempA = plain_text[0:4]
    tempB = plain_text[4:8]
    tempC = plain_text[8:12]
    tempD = plain_text[12:16]

    tempA = list(sBoxinv(tempA))
    tempB = list(sBoxinv(tempB))
    tempC = list(sBoxinv(tempC))
    tempD = list(sBoxinv(tempD))

    # Inverse Mix Columns
    plain_text = rearrange_column_inv(tempA, tempD) + rearrange_column_inv(tempC, tempB)

    K1 = rearrange_column_inv(K1[0:4], K1[4:8]) + rearrange_column_inv(K1[8:12], K1[12:16])
    plain_text = XOR(plain_text, K1, 16)
    tempA = sBoxinv(plain_text[0:4]);
    tempB = sBoxinv(plain_text[4:8]);
    tempC = sBoxinv(plain_text[8:12]);
    tempD = sBoxinv(plain_text[12:16]);
    plain_text = tempA + tempD + tempC + tempB;
    plain_text = XOR(plain_text, K0, 16);
    return ''.join(plain_text)


#####################################################
################## MAIN #############################
#####################################################


print("\n\n======= my AES calculator==========")
print("------------ for 16 bit ---------------")
print("=======================================\n")

menu_choice = input('input E for encryption, D for decryption => ')
k = input('input a key (16bit)')

if len(k) != 16 : #input error
  print("ERROR! key must be 16bit. try again.")
  exit()
if menu_choice == "e" or menu_choice == "E"  : # ENCRYTION
  plain_text = input("input a plain text (16bit) => ")
  if len(plain_text) != 16 : #input error
    print("ERROR! text must be 16bit. try again.")
    exit()
  else :
    ciphertext_res = S_AES_ENCRYT(plain_text, k)
    print('\n---------encryption succeed------')
    print("encrypted ciper text : " + ciphertext_res) # encryption succeed
elif menu_choice == "d" or  menu_choice == "D":
  cipher_text = input("input a cipher text(16bit) => ")
  if len(cipher_text) != 16 : #input error
    print("ERROR! text must be 16bit. try again.")
    exit()
  else :
    plaintext_res = S_AES_DECRYT(cipher_text, k) # DECRYPTION
    print('\n---------decryption succeed------')
    print("decrypted plain text : " + plaintext_res) # encryption succeed
else : #input error
  print("ERROR!  wrong menu choice. try again.")
  exit()
