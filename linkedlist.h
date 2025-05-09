#include "Bridges.h"
#include "CircDLelement.h"
#include <string>

using namespace bridges;

int main(int argc, char **argv) {
    // bridges class initialization
    Bridges bridges (2, "tessjtalbot", "1729671476901");


    // create nodes for beggining party/ first monster fight
    // first string is value second is label
    CircDLelement<string>  *node0 = new CircDLelement<string> ("Karen", "Karen");
    CircDLelement<string>  *node1 = new CircDLelement<string> ("Unattended_Child", "Unattended_Child");
    CircDLelement<string>  *node2 = new CircDLelement<string> ("Cop ", "Cop");
    CircDLelement<string>  *node3 = new CircDLelement<string> ("Goth", "Goth");
    CircDLelement<string>  *node4 = new CircDLelement<string> ("Minivan_Mom", "Minivan_Mom");

    // next lets link em up!
    node0->setNext(node1);
    node1->setPrev(node0);

    node1->setNext(node2);
    node2->setPrev(node1);

    node2->setNext(node3);
    node3->setPrev(node2);

    node3->setNext(node4);
    node4->setPrev(node3);

    // complete the 2D sphere #disruptive tech #Move fast and break things
    // just linking up first and last nodes
    node4->setNext(node0);
    node0->setPrev(node4);

    bridges.setDataStructure(node0);
    bridges.visualize();

    // don't want any leaks!
    delete node0;
    delete node1;
    delete node2;
    delete node3;
    delete node4;

    return 0;
}
