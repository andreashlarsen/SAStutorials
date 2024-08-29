// Include SEB functionality
#include "SEB.hpp"

int main()
{
    // Create world of sub-units
    World w("World");

    // Add a single rod named "A"
    GraphID s = w.Add(new ThinRod(), "A", "rod");

    // Add another rod named "B" and link its end1 to the end2 of A.
    w.Link(new ThinRod(), "B.end1", "A.end2" ,"rod");

    // Add another rod named "C" and link its end1 to the end2 of B.
    w.Link(new ThinRod(), "C.end1", "B.end2" ,"rod");

    // Wrap structure in a structure named Structure
    w.Add(s, "Structure");
    
    // generic equation for the form factor
    ex F=w.FormFactorGeneric("Structure");
    cout << latex << "Form Factor= " << F << endl << endl; 
}
