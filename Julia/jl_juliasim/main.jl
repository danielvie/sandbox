
using JuliaSim

# define the system dynamics
function mass_spring_damper!(dx, x, params, t)
    m, k, c = params
    dx[1] = x[2]
    dx[2] = (-k * x[1] - c/m * x[2]) / m
end

# define system params
m = 1.0
k = 10.0
c = 0.5

# initial conditions
x0 = [1.0, 0.0]

#devine simulation time span
tspan = (0.0, 10.0)

# define simulation problem
prob = ODEProblem(mass_spring_damper!, x0, tspan, (m, k, c))

# solve the problem
sol = solve(prob, Tsit5)

# plot the solution
using Plots
plot(sol, xlabel="Time", ylabel="Position", label="Mass-Spring-Damper", lw=2)