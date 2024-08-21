// Include SEB functionality
#include "SEB.hpp"

int main()
{
    // Create world of sub-units
    World w("World");

    // Add a single subunit named "U1" tagged U
    GraphID s = w.Add(new ThinRod(), "U1", "U");

    // Build the chain
    double scale=0.5;
    int N=166*scale;
    for (int u=2; u<=N; u++)
       {
          string myself="U"+to_string(u)+".end1";     // Name for new unit and REF
          string last  ="U"+to_string(u-1)+".end2";   // Last unit and REF
          w.Link(new ThinRod(), myself, last, "U");   // Add and link
       }

    // Wrap unit in a structure named Structure (this will make sense later)
    w.Add(s, "Structure");
    
    // Print out equation for the form factor
    ex F=w.FormFactor("Structure");
    cout << "Form Factor= " << F << "\n"; 
    
    // To evaluate the equation, we need to define value of paramters
    ParameterList params;
    w.setParameter(params,"L_U", 15.40/sqrt(scale));     // Length of "U" rod
    w.setParameter(params,"beta_U",1);       // Scattering length
    
    // Choose q values
    DoubleVector qvec=w.logspace(0.001,100, 1000 );

    // Use Evaluate to save form factor data to a file
    w.Evaluate( F, params, qvec, "formfactor_chain_0_50.q", "Form factor of a chain of rods.");   
}
