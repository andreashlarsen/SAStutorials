// Include SEB functionality
#include "SEB.hpp"

int main()
{
    // Create world of sub-units
    World w("World");

    // Add a single rod named "A"
    GraphID s = w.Add(new ThinRod(), "A");

    // Add polymer named "B", link B.end1 to the A.end2.
    w.Link(new GaussianPolymer(), "B.end1", "A.end2" );

    // Wrap it a structure named Structure
    w.Add(s, "Structure");
    
    // FormFactorGeneric returns the FF of the structure, but
    // without inserting expressions for the sub-units.
    ex F=w.FormFactor("Structure");
    cout << "Form Factor= " << F << endl << endl; 
    
    ParameterList params;
    w.setParameter(params,"L_A",sqrt(12));    // Lengths of the "A" rod
    w.setParameter(params,"beta_A",0);        // its scattering length   
    w.setParameter(params,"Rg_B", 1.0);       // Radius of gyration for "B" polymer
    w.setParameter(params,"beta_B",1);        // its scattering length

    // Choose q values
    DoubleVector qvec=w.logspace(0.01, 100, 1000 );

    // Use Evaluate to save form factor data to a file
    w.Evaluate( F, params, qvec, "formfactor_rodpolymer_01.q", "Form factor of a polymer with Rg=1 AU and rod L=sqrt(12) AU");
}
