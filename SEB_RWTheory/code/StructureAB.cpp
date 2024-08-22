// Include SEB functionality
#include "SEB.hpp"

int main()
{
    // Create world of sub-units
    World w("World");

    // Add a single rod named "A", tag it "rod"
    GraphID s = w.Add(new ThinRod(), "A", "rod");

    // Add another rod named "B", link B.end1 to the A.end2, tag it "rod"
    w.Link(new ThinRod(), "B.end1", "A.end2", "rod" );

    // Wrap it a structure named Structure
    w.Add(s, "Structure");
    
    // FormFactorGeneric returns the FF of the structure, but
    // without inserting expressions for the sub-units.
    ex F=w.FormFactorGeneric("Structure");
    cout << "Form Factor= " << F << endl << endl; 
}
