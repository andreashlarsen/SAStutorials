// Include SEB functionality
#include "SEB.hpp"

int main()
{
    // Create world of sub-units
    World w("World");

    // Add a single polymer-subunit named "A"
    GraphID p = w.Add(new GaussianPolymer(), "A");

    // Wrap unit in a structure named Structure (this will make sense later)
    w.Add(p, "Structure");
    
    // Print out equation for the form factor
    ex F=w.FormFactor("Structure");
    cout << "Form Factor= " << F << "\n"; 
    
    double Rg=
    
    // To evaluate the equation, we need to define value of paramters
    ParameterList params;
    w.setParameter(params,"Rg_A",1);          // Radius of gyration for "A" polymer
    w.setParameter(params,"beta_A",1);        // Scattering length
    
    // Choose q values
    DoubleVector qvec=w.logspace(0.01, 10.0, 1000 );

    // Use Evaluate to save form factor data to a file
    w.Evaluate( F, params, qvec, "formfactor_polymer.q", "Form factor of a polymer with beta=1 and Rg=1.");   
}
