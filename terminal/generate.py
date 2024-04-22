import random


# open file and generate lines with temperature
with open('temperature.txt', 'w') as f:
    N = 20
    
    f.write(f'Generated {N} temperature data\n')
    
    # get celcius_or_fahrenheit randomly with normal distribution
    for i in range(N):
        is_celcius = random.choice([True, False])
        if is_celcius:
            # generate celcius between 3 and 30
            temp = random.normalvariate(20, 5)
            temp_str = f'{temp:.2f} C'
        else:
            # generate fahrenheit between 30 and 100
            temp = random.normalvariate(70, 10)
            temp_str = f'{temp:.2f} F'
        
        f.write(temp_str + '\n')
    