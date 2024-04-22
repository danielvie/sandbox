
# H = [1, -1; -1, 2];
# f = [-2; -6];
# A = [1, 1; -1, 2; 2, 1];
# b = [2; 2; 3];

# [x,fval,exitflag,output,lambda] = quadprog(H,f,A,b);

using JuMP
using HiGHS

model = Model(HiGHS.Optimizer)

@variable(model, x >= 0)
@variable(model, 0 <= y <= 3)
@objective(model, Min, 12x + 20y)
@constraint(model, c1, 6x + 8y >= 100)
@constraint(model, c2, 7x + 12y >= 120)

print(model)

optimize!(model)

println("...............")
println(value(x))
println(value(y))
println(shadow_price(c1))
println(shadow_price(c2))