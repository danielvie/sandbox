use osqp::{CscMatrix, Problem, Settings};
use quadprog::solve_qp;

fn main() {
    
    // minimize     1/2 x' H x + f' x
    // subject to   A1 x  = b1
    //              A2 x <= b2
    
    // let mut h = [1., -1., -1., 2.];
    // let f = [-2., -6.];
    // let a = [1., 1., -1., 2., 2., 1.];
    // let b = [2., 2., 3.];

    // let sol = solve_qp(&mut h, &f, &a, &b, 0, false).unwrap();
    // assert_eq!(sol.sol, &[-0.6, 0.8]);
    

    // let mut h = [1.,-1.,1., -1.,2.,-2., 1.,-2.,4.];
    // let f = [-7.,-12.,-15.];
    // let a = [1.,1.,1.];
    // let b = [3.];
    // let lb = [0.,0.,0.];

    // let sol = solve_qp(&mut h, &f, &a, &b, 0, false).unwrap();
    
    // println!("{:?}", sol.sol);




    // Define problem data
    let H = &[[4.0, 1.0],
              [1.0, 2.0]];

    let f = &[1.0, 1.0];

    let A = &[[1.0, 1.0],
            [1.0, 0.0],
            [0.0, 1.0]];

    let l = &[1.0, 0.0, 0.0];

    let u = &[1.0, 0.7, 0.7];

    // Extract the upper triangular elements of `P`
    let P = CscMatrix::from(H).into_upper_tri();

    // Disable verbose output
    let settings = Settings::default()
        .verbose(false);

    // Create an OSQP problem
    let mut prob = Problem::new(P, f, A, l, u, &settings).expect("failed to setup problem");

    // Solve problem
    let result = prob.solve();

    // Print the solution
    println!("{:?}", result.x().expect("failed to solve problem"));




}
