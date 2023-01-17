# Python 3 program to convert decimal IPs to binary
import sys

# determines the type of number by checking the digits for base2 or base10
def check(ip):
	
	temp_ip = ip.replace(" ","")
	temp = set(temp_ip)
	
	if temp == {'0'} or temp == {'1'} or temp == {'0','1'} or temp == {'1','0'}:
		return "binary"
	
	elif len(ip) < 15:
		return "decimal"
	
	else:
		return "error"


# error checking for both modes
def parse(ip, mode):
	
	# check for invalid characters (non numeric, not '.' or ' ')
	for i in ip:
		if i != '.' and i != ' ' and not i.isnumeric(): 
			print("'", i, "'  is not a valid character.")
			sys.exit()

	# if binary, check for correct number of bytes and correct number of bits
	if mode == "binary":
		li = list(ip.split(" "))
		for item in li:
			if len(item) != 8:
				print("Invalid number of digits in this address.")
				sys.exit()

		if len(li) != 4:
			print("Invalid number of digits in this address.")
			sys.exit()

		return li
		

	#if decimal, check for range of 0-255 for each section and that there are four sections
	if mode == "decimal":
		li = list(ip.split("."))

		for item in li:
			if int(item) > 255 or int(item) < 0:
				print("Invalid IP range.")
				sys.exit()

		if len(li) != 4:
			print("Invalid number of digits in this address.")
			sys.exit()

		return li


# convert from binary to decimal
def binaryToDecimal(li):
	i = 0
	converted = []

	for item in li:
		number = 0

		for num in item:
			number = number*2 + int(num)

		converted.append(number)


	print("The IP address in decimal form is:")
	print(*converted, sep = '.')

	return


# helper function for decimalToBinary
def convertToBinary(item, li):

	number = ""
	while item != 0:
		rem = item % 2
		item = item // 2
		number = str(rem) + number
	
	return number



# convert from decimal to binary
def decimalToBinary(li):
	converted = []
	
	for item in li:
		number = convertToBinary(int(item), converted)
		converted.append(number)


	print("The IP address in binary form is:")
	
	for item in converted:
		num = int(item)
		print(f"{num:08d}", end=' ')

	print("\n")
	return


def modeBinary(ip):
	li = parse(ip, "binary")
	binaryToDecimal(li)
	return
	

def modeDecimal(ip):
	li = parse(ip, "decimal")
	decimalToBinary(li)
	return

	

# take an IP, separate into a list, "." delimited. Typecast int
ip = input("Enter an IP address in 32-bit or dotted decimal form: ")

if (check(ip) == "binary"):
	modeBinary(ip)

elif (check(ip) == "decimal"):
	modeDecimal(ip)

else: 
	print("Invalid format.")
	sys.exit()
