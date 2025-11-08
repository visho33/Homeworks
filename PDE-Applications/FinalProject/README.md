# Optimal Control Problem Project

Together with my teammate Javier Gatica, we worked on an optimal control problem. To be precise, it is described below.

## An Optimal Control Problem
An optimal control problem is an optimization problem constrained by a partial differential equation (PDE). The aim of this project was to study the discretization of a simple optimal control problem, specifically given by the volume control of the Laplace operator. This can be formulated as the following minimization problem:

\[
\min_{u,\mu} \frac{1}{2} \|u - u_\Omega\|_0^2 + \alpha \|\mu\|_0^2
\]
\[
\text{s.t.} \quad -\Delta u = \mu \quad \text{in } \Omega, \quad u = 0 \quad \text{on } \partial\Omega
\]

### The project consisted of:

- Studying the adjoint method
- Establishing the well-posedness of the problem using the Stampacchia theorem
- Formulating an approximation of the problem using the Finite Element Method (FEM), applying both the "optimize-then-discretize" and "discretize-then-optimize" strategies
- Demonstrating that optimization and discretization do not commute in this context
- Showing the convergence rates of the model
- Implementing the problem and numerically validating all the theoretical claims

We chose this project because we thought that, at first glance, an optimization problem might seem quite different from what we had studied in the course. It seemed really interesting and offered the potential to provide new tools that could complement our learning in the course.
