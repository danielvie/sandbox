import random

def monte_carlo_pi(num_samples):
    inside_circle = 0

    for _ in range(num_samples):
        x, y = random.uniform(-1, 1), random.uniform(-1, 1)
        distance_to_origin = x*x + y*y
        if distance_to_origin <= 1:
            inside_circle += 1

    return (inside_circle / num_samples) * 4

# Test
num_samples = 100000
estimated_pi = monte_carlo_pi(num_samples)
print(f"Estimated value of π with {num_samples} samples: {estimated_pi}")

'''
Game Rules:

You pay $1 to play.
A fair six-sided die is rolled.
If the die lands on 1 or 2, you win $2. For any other number, you lose your dollar.
We want to know: What's the expected value of playing this game?

Expected value is the mean of all possible values. Using Monte Carlo, we can simulate playing the game many times and then calculate our average earnings to estimate this expected value.

Let's write the simulation and plot the running average winnings over time:
'''
import random
import matplotlib.pyplot as plt

def game_outcome():
    """Simulates a single game and returns the net earnings."""
    roll = random.randint(1, 6)
    return 2 if roll <= 2 else -1

def monte_carlo_simulation(num_samples):
    total_earnings = 0
    running_averages = []

    for _ in range(num_samples):
        total_earnings += game_outcome()
        running_averages.append(total_earnings / ( _ + 1 ))

    return running_averages

# Test
num_samples = 100000
running_averages = monte_carlo_simulation(num_samples)

# Plotting the results
plt.figure(figsize=(10, 6))
plt.plot(running_averages)
plt.axhline(0, color='red', linestyle='dashed')
plt.title(f"Running Average Earnings over {num_samples} Games")
plt.xlabel("Number of Games")
plt.ylabel("Average Earnings per Game")
plt.grid(True)
plt.show()
