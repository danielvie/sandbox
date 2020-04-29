import hello

if __name__ == "__main__":
	
	print(hello.soma(1.,200))
	R  = hello.get_vetor(10)

	RR = [r for r in R]

	print(RR)

	hello.send_vetor([7,2,3,4,5])
