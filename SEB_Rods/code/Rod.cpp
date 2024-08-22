// Include SEB functionality
#include "SEB.hpp"

int main()
{
    // Create world of sub-units
    World w("World");

    // Add a single rod-subunit named "A"
    GraphID r = w.Add(new ThinRod(), "A");

    // Wrap unit in a structure named Structure (this will make sense later)
    w.Add(r, "Structure");
    
    // Print out equation for the form factor
    ex F=w.FormFactor("Structure");
    cout << "Form Factor= " << F << "\n"; 
    
    // To evaluate the equation, we need to define value of paramters
    ParameterList params;
    w.setParameter(params,"L_A",sqrt(12));       // Lengths of the "A" rod
    w.setParameter(params,"beta_A",1);    // Scattering length
    
    // Choose q values
    DoubleVector qvec=w.logspace(0.01, 10.0, 1000 );

    // Use Evaluate to save form factor data to a file
    w.Evaluate( F, params, qvec, "formfactor_rod.q", "Form factor of a rod with beta=1 and L=1.");   
}
