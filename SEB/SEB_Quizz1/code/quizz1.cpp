// Include SEB functionality
#include "SEB.hpp"

int main()
{
    // Create world of sub-units
    World w("World");

    // Add a single rod subunit named "A"
    GraphID s = w.Add(new ThinRod(), "A");

    // Add a single polymer B, linked B.contour-A.contour
    w.Link(new GaussianPolymer(), "B.contour#p1", "A.contour#p2");

    // Wrap unit in a structure named Structure (this will make sense later)
    w.Add(s, "Structure");
    
    // Print out equation for the form factor
    ex F=w.FormFactor("Structure");
    cout << "Form Factor= " << F << "\n"; 
    
    // To evaluate the equation, we need to define value of paramters
    ParameterList params;
    w.setParameter(params,"L_A", 2);     // Length of "U" rod
    w.setParameter(params,"beta_A",0.5);       // Scattering length
    w.setParameter(params,"Rg_B", 0.5);     // Length of "U" rod
    w.setParameter(params,"beta_B",0.8);       // Scattering length
    
    // Choose q values
    DoubleVector qvec=w.logspace(0.1,100, 1000 );

    // Use Evaluate to save form factor data to a file
    w.Evaluate( F, params, qvec, "formfactor_quizz1.q", "Form factor of mystery.");   
}
